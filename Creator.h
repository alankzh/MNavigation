#pragma once
#include "vtkAlgorithmOutput.h"
#include "vtkActor.h"
#include "vtkImageActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkImageMapper3D.h"
#include "vtkVolume.h"
#include "vtkSmartPointer.h"

#include "vtkImageProperty.h"


namespace Creator {

	template<typename T>
	static vtkSmartPointer<vtkActor> CreatePolyModel() {
		auto source = T::New();
		auto mapper = vtkPolyDataMapper::New();
		mapper->SetInputConnection(source->GetOutputPort());
		auto actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		source->Delete();
		mapper->Delete();
		return actor;
	}
	
	static vtkSmartPointer<vtkVolume> CreateVolume(vtkAlgorithmOutput* input) {
		auto mapper = vtkSmartVolumeMapper::New();
		mapper->SetInputConnection(input);
		mapper->SetBlendModeToComposite();
		auto volume = vtkSmartPointer<vtkVolume>::New();
		volume->SetMapper(mapper);
		mapper->Delete();
		return volume;
	}
	
	static vtkSmartPointer<vtkVolume> CreateVolume(vtkImageData* data) {
		auto mapper = vtkSmartVolumeMapper::New();
		mapper->SetInputData(data);
		mapper->SetBlendModeToComposite();
		auto volume = vtkSmartPointer<vtkVolume>::New();
		volume->SetMapper(mapper);
		mapper->Delete();
		return volume;
	}

	static vtkSmartPointer<vtkImageActor> CreateImage(vtkImageData* data) {
		auto actor = vtkSmartPointer<vtkImageActor>::New();
		actor->SetInputData(data);
		return actor;
	}

}