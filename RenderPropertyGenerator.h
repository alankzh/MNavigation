#pragma once
#include <map>
#include <vector>
#include "vtkVolumeProperty.h"

class RenderPropertyGenerator
{

public:

	struct volumePropertyArgs {
		std::vector<double> gradient_opacity_points;
		std::vector<double> color_points;
		std::vector<double> scalar_opacity_points;
		bool is_shade_on;
		double specular_power;
		double specular;
		double ambient;
		double diffuse;
		int interpolationType;
	};
	
	enum ErrorCode
	{	
		kNoError,
		kPresetFileNotExist,
		kPresetFileParseError,
	};

	static void ApplyVolumeProperty(std::string property_name, vtkVolumeProperty* const volume_property);

	static volumePropertyArgs GetPropertyArgs(vtkVolumeProperty* const volume_property);

	//first try to read user configurations, if failed, read the default presets file.
	static ErrorCode LoadPresets();

	static void AddPropertyPreset(std::string property_name, vtkVolumeProperty* const volume_property);

	static void SavePresetsToLocal();

	static void ShiftRenderFunction(double shift, vtkVolumeProperty* const volume_property);

	static std::vector<std::string> GetAllAvaiblePresetsName();

private:

	static std::map<std::string, volumePropertyArgs> volume_property_library_;

	static std::string presets_file_path_;

	static std::string user_presets_path_;

	static void InitFilePath();

};

