#pragma once
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
class Scene
{	
	typedef vtkSmartPointer<vtkRenderer> RenderType;
	typedef vtkSmartPointer<vtkRenderWindow> WindowType;
	typedef vtkSmartPointer<vtkRenderWindowInteractor> InteractorType;
public:
	Scene();
	~Scene();

	RenderType GetRenderer() const;
	WindowType GetWindow() const;
	InteractorType GetInteractor() const;

private:
	RenderType renderer_;
	WindowType window_;
	InteractorType interator_;

};

