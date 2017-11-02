#pragma once
#include <set>
#include <map>
#include "vtkProp3D.h"
#include "vtkRenderer.h"
#include "vtkVector.h"

class MarkerCreator
{	

	struct Line {
		vtkProp3D* point1;
		vtkProp3D* point2;
	};

	struct LineInfo {
		vtkProp3D* Line;
	};

public:

	MarkerCreator();
	
	vtkProp3D* CreateMarker(vtkRenderer* renderer,vtkVector3d worldPosition);

	void RemoveMarker(vtkProp3D* marker);

	bool isMarker(vtkProp3D* target) const;

	void CreateLine(vtkRenderer* renderer);

	void SelectMarker(vtkProp3D* target);

	virtual ~MarkerCreator();

private:

	void UnSelectMarker(vtkProp3D* target);

	vtkProp3D* LastMarker;

	vtkProp3D* CurrentMarker;

	std::set<vtkProp3D*> MarkerSet;

	std::set<vtkProp3D*> SelectedMarkerSet;

	std::map<Line, LineInfo> LineMap;

};

