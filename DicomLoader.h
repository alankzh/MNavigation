#pragma once
#include <map>
#include <set>

#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkKernelImageFilter.h"
#include "itkImageToVTKImageFilter.h"
#include "vtkImageData.h"
#include "JsonUtils.h"
#include "customThread/progressobserver.h"

class DicomLoader
{
public:

	struct ResourceInfo {
		std::string patient_name;
		std::string patient_ID;
		std::string patient_sex;
		std::string patient_age;
		std::string patient_DOB; // patient date of birth
		std::string series_instance_UID; // unique identifier for the series
		std::string series_description;
		std::string study_ID;
		std::string study_description;
		std::string study_date;
		std::string modality;  // MRI/CT/CR/DR
		std::string manufacturer;
		std::string institution_name;
		std::string image_position; // the x,y,z coordinates of the upper left hand corner of the image,in mm
		std::string slice_thickness; // nominal slice thickness, in mm
		std::string spacing_between_slices; // in mm
	};

	struct Resource {
		ResourceInfo info;
		vtkImageData* data;
	};

	enum ErrorCode {
		kDicom,
		kImage,
		kNoFilesFound,
	};

	// read data. overwrite the previous one
    static ErrorCode ReadDicomData(std::string path,ProgressObserver::Pointer observer=NULL);

	//DO NOT call this if you are still using the data from it.
	static void ReleaseData();

	//return nullptr if has no data
	static vtkImageData* GetData();

	//return nullptr if has no data
	static const ResourceInfo* GetDataInfo();

	static bool HasData();

private:

	DicomLoader();

	~DicomLoader();

	static bool has_resource_;

	static Resource resource_;

	static itk::GDCMSeriesFileNames::Pointer file_parser_;

	typedef itk::Image<signed short, 3> ImageType;
	typedef itk::ImageSeriesReader<ImageType> ReaderType;

	static ReaderType::Pointer reader_;

	static itk::GDCMImageIO::Pointer medicalinfo_parser_;

	static itk::ImageToVTKImageFilter<ImageType>::Pointer filter_;

};

