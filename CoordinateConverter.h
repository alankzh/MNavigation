#pragma once
#include "vtks.h"
#include "myslicerwidget.h"
class CoordinateConverter
{
public:

	static vtkVector2d EventToView(vtkRenderer* renderer, int EventPointX, int EventPointY);

	static vtkVector3d EventToModel(vtkImageViewer2* viewer, int EventPointX, int EventPointY);

	static int ModelToSlice(vtkImageViewer2* viewer, vtkVector3d ModelPosition);

	static double GetSliceRatio(vtkImageViewer2* viewer);

	static vtkVector3d ModelToWorld(vtkProp3D* prop, vtkVector3d ModelPosition);

	static vtkVector3d WorldToModel(vtkProp3D* prop, vtkVector3d WorldPosition);
};

