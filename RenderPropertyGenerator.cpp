#include "RenderPropertyGenerator.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "qstandardpaths.h"
#include "qdir.h"

#include "rapidjson\document.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\prettywriter.h"

#include "JsonUtils.h"

typedef RenderPropertyGenerator::ErrorCode ErrorCode;

std::map<std::string, RenderPropertyGenerator::volumePropertyArgs> RenderPropertyGenerator::volume_property_library_;

std::string RenderPropertyGenerator::presets_file_path_;

std::string RenderPropertyGenerator::user_presets_path_;

// helper functions for this implementation. Not accessible for other .cpp .h files
namespace {

	const std::string kPropertyTitle = "PropertyName";

	const std::string kArgTitle = "PropertyArgs";

	const double shiftGap = 10;

	rapidjson::Value ArgsToValue(const RenderPropertyGenerator::volumePropertyArgs& args, rapidjson::Document::AllocatorType& allocator) {
		rapidjson::Value d;
		d.SetObject();
		rapidjson::Value& color_points = JsonUtils::DoubleVectorToValue(args.color_points, allocator);
		rapidjson::Value& scalar_points = JsonUtils::DoubleVectorToValue(args.scalar_opacity_points, allocator);
		rapidjson::Value& gradient_points = JsonUtils::DoubleVectorToValue(args.gradient_opacity_points, allocator);
		d.AddMember("color", color_points, allocator);
		d.AddMember("scalar", scalar_points, allocator);
		d.AddMember("gradient", gradient_points, allocator);
		d.AddMember("ambient", args.ambient, allocator);
		d.AddMember("diffuse", args.diffuse, allocator);
		d.AddMember("specular", args.specular, allocator);
		d.AddMember("specularpower", args.specular_power, allocator);
		d.AddMember("interpolation", args.interpolationType, allocator);
		d.AddMember("isShadeOn", args.is_shade_on, allocator);
		return d;
	}

	rapidjson::Value ArgsToNamedValue(const RenderPropertyGenerator::volumePropertyArgs& args, rapidjson::Document::AllocatorType& allocator, std::string name) {
		rapidjson::Value& v = ArgsToValue(args, allocator);
		rapidjson::Value result;
		result.SetObject();
		result.AddMember(JsonUtils::CreateStringValue(kPropertyTitle, allocator), JsonUtils::CreateStringValue(name,allocator), allocator);
		result.AddMember(JsonUtils::CreateStringValue(kArgTitle, allocator), v, allocator);
		return result;
	}

	bool ParseValueToNamedArg(const rapidjson::Value& value, std::string& name, RenderPropertyGenerator::volumePropertyArgs& args) {

		if (!value.HasMember(kPropertyTitle.c_str()) || !value.HasMember(kArgTitle.c_str())) {
			return false;
		}
		name = value[kPropertyTitle.c_str()].GetString();
		auto v = value[kArgTitle.c_str()].GetObject();
		if (v.HasMember("color") &&
			v.HasMember("scalar") &&
			v.HasMember("gradient") &&
			v.HasMember("ambient") &&
			v.HasMember("diffuse") &&
			v.HasMember("specular") &&
			v.HasMember("specularpower") &&
			v.HasMember("interpolation") &&
			v.HasMember("isShadeOn")) {
			
			if (!JsonUtils::ValueToDoubleVector(v["color"], args.color_points)||
				!JsonUtils::ValueToDoubleVector(v["scalar"],args.scalar_opacity_points)||
				!JsonUtils::ValueToDoubleVector(v["gradient"],args.gradient_opacity_points)) {
				return false;
			}
			if (!v["ambient"].IsDouble() ||
				!v["diffuse"].IsDouble() ||
				!v["specular"].IsDouble() ||
				!v["specularpower"].IsDouble() ||
				!v["interpolation"].IsInt() ||
				!v["isShadeOn"].IsBool()) {
				return false;
			}

			args.ambient = v["ambient"].GetDouble();
			args.diffuse = v["diffuse"].GetDouble();
			args.specular = v["specular"].GetDouble();
			args.specular_power = v["specular"].GetDouble();
			args.interpolationType = v["interpolation"].GetInt();
			args.is_shade_on = v["isShadeOn"].GetBool();
			
			return true;
		}
		else {
			return false;
		}
	}

	void PushValue(const RenderPropertyGenerator::volumePropertyArgs& args, rapidjson::Document& document, std::string name) {
		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
		document.PushBack(ArgsToNamedValue(args, allocator, name), allocator);
	}

	enum FinalResult {
		kSuccess,
		kFailToReadFile,
		kDataError
	};

	FinalResult ParsePresetFile(std::string file_path, std::vector<std::pair<std::string, RenderPropertyGenerator::volumePropertyArgs>> &output) {
		output.clear();
		rapidjson::Document document;
		JsonUtils::ResultCode result = JsonUtils::ParseFile(file_path, document);
		if (result == JsonUtils::kFailToOpenFile) {
			return kFailToReadFile;
		}
		if (result == JsonUtils::kParseError) {
			return kDataError;
		}
		if (!document.IsArray()) {
			return kDataError;
		}
		for (rapidjson::SizeType i = 0; i < document.Size(); i++) {
			std::string arg_name;
			RenderPropertyGenerator::volumePropertyArgs args;
			if (ParseValueToNamedArg(document[i], arg_name, args)) {
				output.push_back(std::pair<std::string, RenderPropertyGenerator::volumePropertyArgs>(arg_name, args));
			}
		}
		if (output.size() > 0) {
			return kSuccess;
		}
		else {
			return kDataError;
		}
	}

	void ShiftColorFunction(vtkColorTransferFunction* color_fun, double shift) {
		int n = color_fun->GetSize();
		if (n <= 2) {
			return;
		}
		double* data = color_fun->GetDataPointer();
		double min = data[0];
		double max = data[4 * (n - 1)];
		double Range = max - min;
		double minShift = min + shiftGap - data[4];
		double maxShift = max - shiftGap - data[4 * (n - 2)];
		double offset = Range * shift;
		if (offset < minShift) {
			offset = minShift;
		}
		if (offset > maxShift) {
			offset = maxShift;
		}
		for (int i = 1; i < n - 1; i++) {
			data[4 * i] += offset;
		}
		color_fun->FillFromDataPointer(n, data);
	}

	void ShiftPieceWiseFunction(vtkPiecewiseFunction* opacity_func, double shift) {
		int n = opacity_func->GetSize();
		if (n <= 2) {
			return;
		}
		double* data = opacity_func->GetDataPointer();
		double min = data[0];
		double max = data[2 * (n - 1)];
		double Range = max - min;
		double minShift = min + shiftGap - data[2];
		double maxShift = max - shiftGap - data[2 * (n - 2)];
		double offset = Range * shift;
		if (offset < minShift) {
			offset = minShift;
		}
		if (offset > maxShift) {
			offset = maxShift;
		}
		for (int i = 1; i < n - 1; i++) {
			data[2 * i] += offset;
		}
		opacity_func->FillFromDataPointer(n, data);
	}

}

void RenderPropertyGenerator::ApplyVolumeProperty(std::string property_name, vtkVolumeProperty* const volume_property) {

	if (volume_property_library_.find(property_name) == volume_property_library_.end()) {
		return;
	}
	RenderPropertyGenerator::volumePropertyArgs args = volume_property_library_[property_name];

	vtkColorTransferFunction* color_func = volume_property->GetRGBTransferFunction();
	vtkPiecewiseFunction* scalar_opacity_func = volume_property->GetScalarOpacity();
	vtkPiecewiseFunction* gradient_opacity_func = volume_property->GetGradientOpacity();

	color_func->RemoveAllPoints();
	scalar_opacity_func->RemoveAllPoints();
	gradient_opacity_func->RemoveAllPoints();

	gradient_opacity_func->FillFromDataPointer(args.gradient_opacity_points.size() / 2, args.gradient_opacity_points.data());
	color_func->FillFromDataPointer(args.color_points.size() / 4, args.color_points.data());
	scalar_opacity_func->FillFromDataPointer(args.scalar_opacity_points.size() / 2, args.scalar_opacity_points.data());

	if (args.is_shade_on) {
		volume_property->ShadeOn();
		volume_property->SetSpecularPower(args.specular_power);
		volume_property->SetSpecular(args.specular);
		volume_property->SetAmbient(args.ambient);
		volume_property->SetDiffuse(args.diffuse);
	}
	else {
		volume_property->ShadeOff();
	}
	if (args.interpolationType == VTK_NEAREST_INTERPOLATION || args.interpolationType == VTK_LINEAR_INTERPOLATION) {
		volume_property->SetInterpolationType(args.interpolationType);
	}
}

RenderPropertyGenerator::volumePropertyArgs RenderPropertyGenerator::GetPropertyArgs(vtkVolumeProperty* const volume_property) {

	RenderPropertyGenerator::volumePropertyArgs args;
	auto color_func = volume_property->GetRGBTransferFunction();
	auto scalar_opacity_func = volume_property->GetScalarOpacity();
	auto gradient_opacity_func = volume_property->GetGradientOpacity();

	std::vector<double> scalar_opacity_points(scalar_opacity_func->GetDataPointer(), scalar_opacity_func->GetDataPointer() + scalar_opacity_func->GetSize() * 2);
	args.scalar_opacity_points = scalar_opacity_points;

	std::vector<double> color_points(color_func->GetDataPointer(), color_func->GetDataPointer() + color_func->GetSize() * 4);
	args.color_points = color_points;

	std::vector<double> gradient_opacity_points(gradient_opacity_func->GetDataPointer(), gradient_opacity_func->GetDataPointer() + gradient_opacity_func->GetSize() * 2);
	args.gradient_opacity_points = gradient_opacity_points;

	args.is_shade_on = (bool)volume_property->GetShade();
	args.ambient = volume_property->GetAmbient();
	args.diffuse = volume_property->GetDiffuse();
	args.specular = volume_property->GetSpecular();
	args.specular_power = volume_property->GetSpecularPower();
	args.interpolationType = volume_property->GetInterpolationType();

	return args;
}

ErrorCode RenderPropertyGenerator::LoadPresets() {
	InitFilePath();
	std::vector<std::pair<std::string, RenderPropertyGenerator::volumePropertyArgs>> presets;
	FinalResult user_file_parse_result = ParsePresetFile(user_presets_path_, presets);
	std::cout << "user presets size: " << presets.size() << std::endl;
	if (user_file_parse_result == FinalResult::kSuccess) {
		for (size_t i = 0; i < presets.size(); i++) {
			volume_property_library_.insert(presets[i]);
		}
		return kNoError;
	}
	else {
		FinalResult default_file_parse_result = ParsePresetFile(presets_file_path_, presets);
		std::cout << "presets size: " << presets.size() << std::endl;
		if (default_file_parse_result == FinalResult::kSuccess) {
			std::cout << "success!" << std::endl;
			for (size_t i = 0; i < presets.size(); i++) {
				volume_property_library_.insert(presets[i]);
			}
			return kNoError;
		}
		else {
			if (default_file_parse_result == FinalResult::kFailToReadFile) {
				return kPresetFileNotExist;
			}
			else {
				std::cout << "parse error " << std::endl;
				return kPresetFileParseError;
			}
		}
	}
}

void RenderPropertyGenerator::AddPropertyPreset(std::string property_name, vtkVolumeProperty* const volume_property) {
	volume_property_library_.insert(std::pair<std::string, volumePropertyArgs>(property_name, GetPropertyArgs(volume_property)));
}

void RenderPropertyGenerator::SavePresetsToLocal() {
	rapidjson::Document document;
	document.SetArray();
	std::cout << "presets to be saved number: " << volume_property_library_.size() << std::endl;
	for (auto i = volume_property_library_.begin(); i != volume_property_library_.end(); i++) {
		PushValue(i->second, document, i->first);
	}
	auto content = JsonUtils::StringfyDocument(document);
	std::cout << "save user configurations. " << std::endl;
	JsonUtils::WriteStringToFile(user_presets_path_, content);
}

void RenderPropertyGenerator::ShiftRenderFunction(double shift, vtkVolumeProperty* const volume_property) {
	ShiftColorFunction(volume_property->GetRGBTransferFunction(), shift);
	ShiftPieceWiseFunction(volume_property->GetScalarOpacity(), shift);
	ShiftPieceWiseFunction(volume_property->GetGradientOpacity(), shift);
}

std::vector<std::string> RenderPropertyGenerator::GetAllAvaiblePresetsName() {
	std::vector<std::string> names;
	for (auto i = volume_property_library_.begin(); i != volume_property_library_.end(); i++) {
		names.push_back(i->first);
	}
}

void RenderPropertyGenerator::InitFilePath() {
	presets_file_path_ = QDir::currentPath().toStdString() + "\\Presets\\presets.txt";
	//user_presets_path_ = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString() + "\\userpresets.txt";
	user_presets_path_ = QDir::currentPath().toStdString() + "\\Presets\\userpresets.txt";
	std::cout << "presets path: " << presets_file_path_ << std::endl;
	std::cout << "user_presets_path_: " << user_presets_path_ << std::endl;
}