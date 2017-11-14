#include "DicomLoader.h"
#include "JsonUtils.h"

#define TESTLOG(X) std::cout << #X  << ": " << X << std::endl

bool DicomLoader::has_resource_(false);

itk::GDCMSeriesFileNames::Pointer DicomLoader::file_parser_(itk::GDCMSeriesFileNames::New());

DicomLoader::ReaderType::Pointer DicomLoader::reader_(ReaderType::New());

itk::GDCMImageIO::Pointer DicomLoader::medicalinfo_parser_(itk::GDCMImageIO::New());

itk::ImageToVTKImageFilter<DicomLoader::ImageType>::Pointer DicomLoader::filter_(itk::ImageToVTKImageFilter<ImageType>::New());

DicomLoader::Resource DicomLoader::resource_;

DicomLoader::DicomLoader()
{
}

DicomLoader::~DicomLoader()
{
	ReleaseData();
}

DicomLoader::ErrorCode DicomLoader::ReadDicomData(std::string path) {

	file_parser_->SetInputDirectory(path);
	auto file_names = file_parser_->GetInputFileNames();
	if (file_names.size() == 0) {
		return kNoFilesFound;
	}
	reader_->SetFileNames(file_names);
	reader_->SetImageIO(medicalinfo_parser_);
	reader_->Update();

	medicalinfo_parser_->GetValueFromTag("0010|0010", resource_.info.patient_name);
	medicalinfo_parser_->GetValueFromTag("0010|0020", resource_.info.patient_ID);
	medicalinfo_parser_->GetValueFromTag("0010|0030", resource_.info.patient_DOB);
	medicalinfo_parser_->GetValueFromTag("0010|0040", resource_.info.patient_sex);
	medicalinfo_parser_->GetValueFromTag("0010|1010", resource_.info.patient_age);
	medicalinfo_parser_->GetValueFromTag("0020|0010", resource_.info.study_ID);
	medicalinfo_parser_->GetValueFromTag("0008|0020", resource_.info.study_date);
	medicalinfo_parser_->GetValueFromTag("0008|1030", resource_.info.study_description);
	medicalinfo_parser_->GetValueFromTag("0008|0060", resource_.info.modality);
	medicalinfo_parser_->GetValueFromTag("0008|0070", resource_.info.manufacturer);
	medicalinfo_parser_->GetValueFromTag("0020|000E", resource_.info.series_instance_UID);
	medicalinfo_parser_->GetValueFromTag("0008|103E", resource_.info.series_description);
	medicalinfo_parser_->GetValueFromTag("0008|0080", resource_.info.institution_name);
	medicalinfo_parser_->GetValueFromTag("0020|0032", resource_.info.image_position);
	medicalinfo_parser_->GetValueFromTag("0018|0050", resource_.info.slice_thickness);
	medicalinfo_parser_->GetValueFromTag("0018|0088", resource_.info.spacing_between_slices);

	TESTLOG(resource_.info.patient_name);
	TESTLOG(resource_.info.patient_ID);
	TESTLOG(resource_.info.patient_DOB);
	TESTLOG(resource_.info.patient_sex);
	TESTLOG(resource_.info.patient_age);
	TESTLOG(resource_.info.study_ID);
	TESTLOG(resource_.info.study_date);
	TESTLOG(resource_.info.study_description);
	TESTLOG(resource_.info.modality);
	TESTLOG(resource_.info.manufacturer);
	TESTLOG(resource_.info.series_instance_UID);
	TESTLOG(resource_.info.series_description);
	TESTLOG(resource_.info.institution_name);
	TESTLOG(resource_.info.image_position);
	TESTLOG(resource_.info.slice_thickness);
	TESTLOG(resource_.info.spacing_between_slices);

	filter_->SetInput(reader_->GetOutput());
	filter_->Update();

	has_resource_ = true;
	resource_.data = filter_->GetOutput();
	


	int image_numbers = resource_.data->GetDimensions()[2];
	if (image_numbers > 20) {
		return kDicom;
	}
	else {
		return kImage;
	}
}

void DicomLoader::ReleaseData() {

	file_parser_ = itk::GDCMSeriesFileNames::New();
	reader_ = ReaderType::New();
	medicalinfo_parser_ = itk::GDCMImageIO::New();
	filter_ = itk::ImageToVTKImageFilter<ImageType>::New();
	has_resource_ = false;
}

vtkImageData* DicomLoader::GetData() {
	if (HasData()) {
		return resource_.data;
	}
	else {
		return nullptr;
	}
}

const DicomLoader::ResourceInfo* DicomLoader::GetDataInfo() {
	if (HasData()) {
		return &resource_.info;
	}
	else {
		return nullptr;
	}
}

bool DicomLoader::HasData() {
	return has_resource_;
}

