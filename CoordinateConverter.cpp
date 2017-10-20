#include "CoordinateConverter.h"

vtkVector2d CoordinateConverter::EventToView(vtkRenderer* renderer, int EventPointX, int EventPointY) {
	int* Size = renderer->GetSize();
	double ViewEventPointX = (double)EventPointX * 2 / Size[0] - 1;
	double ViewEventPointY = (double)EventPointY * 2 / Size[1] - 1;
	return vtkVector2d(ViewEventPointX, ViewEventPointY);
}

inline double delta(const double matrix[3][3]) {
	return	matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
			matrix[1][0] * (matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) +
			matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
}

vtkVector3d CoordinateConverter::EventToModel(vtkImageViewer2* viewer, int EventPointX, int EventPointY) {
	vtkImageActor* Actor = viewer->GetImageActor();
	vtkRenderer* Renderer = viewer->GetRenderer();
	vtkVector2d EventViewPoint = EventToView(Renderer, EventPointX, EventPointY);
	int orientation = viewer->GetSliceOrientation();
	double* boundary = Actor->GetMapper()->GetBounds();
	double x = boundary[1];
	double y = boundary[3];
	double z = boundary[5];
	double ratio = GetSliceRatio(viewer);
	double* worldPositions;
	switch (orientation)
	{
	case vtkImageViewer2::SLICE_ORIENTATION_XY:
		z = (boundary[5] - boundary[4]) * ratio + boundary[4];
		worldPositions = new double[12]{ 0, 0, z, 1, 
										 x, 0, z, 1, 
										 0, y, z, 1 };
		break;
	case vtkImageViewer2::SLICE_ORIENTATION_YZ:
		x = (boundary[1] - boundary[0]) * ratio + boundary[0];
		worldPositions = new double[12]{ x, 0, 0, 1, 
										 x, y, 0, 1, 
										 x, 0, z, 1 };
		break;
	case vtkImageViewer2::SLICE_ORIENTATION_XZ:
		y = (boundary[3] - boundary[2]) * ratio + boundary[2];
		worldPositions = new double[12]{ 0, y, 0, 1,
										 x, y, 0, 1,
										 0, y, z, 1 };
		break;
	default:
		break;
	}
	double worldMatrix[3][4];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			worldMatrix[i][j] = worldPositions[4 * i + j];
		}
	}
	Actor->ComputeMatrix();
	vtkMatrix4x4* matrix = Actor->GetMatrix();
	for (int i = 0; i < 3; i++) {
		matrix->MultiplyPoint(worldMatrix[i], worldMatrix[i]);
		for (int j = 0; j < 3; j++) {
			worldMatrix[i][j] = worldMatrix[i][j] / worldMatrix[i][3];
		}
	}
	double viewPositions[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			viewPositions[i][j] = worldMatrix[i][j];
		}
	}
	//note:: after this, every rows' last position stores the viewDepth, which we dont care now
	for (int i = 0; i < 3; i++) {
		Renderer->WorldToView(viewPositions[i][0], viewPositions[i][1], viewPositions[i][2]);
	}
	//now we've got 3 points' wolrd positions and view positions.
	//given 3 points X,Y,Z's viewPosition(we treat them as vector2) and a specific point M.
	//we here to determin the solution of this equation: aX + bY + cZ = M, where a + b + c = 1

	for (int i = 0; i < 3; i++) {
		viewPositions[i][2] = 1;
	}
	double aMat[3][3];
	double bMat[3][3];
	double cMat[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			aMat[i][j] = viewPositions[i][j];
			bMat[i][j] = viewPositions[i][j];
			cMat[i][j] = viewPositions[i][j];
		}
	}
	aMat[0][0] = EventViewPoint[0];
	aMat[0][1] = EventViewPoint[1];
	aMat[0][2] = 1;
	bMat[1][0] = EventViewPoint[0];
	bMat[1][1] = EventViewPoint[1];
	bMat[1][2] = 1;
	cMat[2][0] = EventViewPoint[0];
	cMat[2][1] = EventViewPoint[1];
	cMat[2][2] = 1;

	double Main = delta(viewPositions);
	double a = delta(aMat) / Main;
	double b = delta(bMat) / Main;
	double c = delta(cMat) / Main;


	vtkVector3d modelPosition = vtkVector3d();
	for (int i = 0; i < 3; i++) {
		modelPosition[i] = a * worldPositions[i] + b * worldPositions[4 + i] + c * worldPositions[8 + i];
	}
	delete[] worldPositions;
	return modelPosition;
}

double CoordinateConverter::GetSliceRatio(vtkImageViewer2* viewer) {
	int slice = viewer->GetSlice();
	int min = viewer->GetSliceMin();
	int max = viewer->GetSliceMax();
	return (double)(slice - min) / (max - min);
}

vtkVector3d CoordinateConverter::ModelToWorld(vtkProp3D* prop, vtkVector3d modelPosition) {
	prop->ComputeMatrix();
	vtkMatrix4x4* matrix = prop->GetMatrix();
	return vtkVector3d(matrix->MultiplyDoublePoint(modelPosition.GetData()));
}

int CoordinateConverter::ModelToSlice(vtkImageViewer2* viewer, vtkVector3d ModelPosition) {
	int orientation = viewer->GetSliceOrientation();
	double* bounds = viewer->GetImageActor()->GetMapper()->GetBounds();
	double ratio = (ModelPosition[orientation] - bounds[2 * orientation]) / (bounds[2 * orientation + 1] - bounds[2 * orientation]);
	int max = viewer->GetSliceMax();
	int min = viewer->GetSliceMin();
	return (int)(ratio * (max - min) + min);
}