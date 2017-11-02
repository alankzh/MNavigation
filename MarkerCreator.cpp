#include "MarkerCreator.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkLineSource.h"
#include "vtkProperty.h"

MarkerCreator::MarkerCreator()
{
	LastMarker = nullptr;
	CurrentMarker = nullptr;
}

MarkerCreator::~MarkerCreator()
{
}

vtkProp3D* MarkerCreator::CreateMarker(vtkRenderer* renderer, vtkVector3d worldPosition) {
	auto source = vtkSphereSource::New();
	source->SetRadius(10);
	source->SetThetaResolution(52);
	source->SetPhiResolution(52);
	auto mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(source->GetOutputPort());
	source->Delete();
	auto marker = vtkActor::New();
	marker->SetMapper(mapper);
	marker->SetPosition(worldPosition.GetData());
	vtkActor* actor = dynamic_cast<vtkActor*>(marker);
	actor->GetProperty()->SetColor(0, 1, 0);
	mapper->Delete();
	MarkerSet.insert(marker);
	renderer->AddActor(marker);
	return marker;
}

void MarkerCreator::RemoveMarker(vtkProp3D* marker) {
	if (!isMarker(marker)) {
		return;
	}
	else {
		MarkerSet.erase(marker);
	}
	if (SelectedMarkerSet.find(marker) != SelectedMarkerSet.end()) {
		SelectedMarkerSet.erase(marker);
	}
	if (LastMarker == marker) {
		LastMarker = nullptr;
	}
	if (CurrentMarker == marker) {
		CurrentMarker = nullptr;
	}
}

bool MarkerCreator::isMarker(vtkProp3D* marker) const{
	return !(MarkerSet.find(marker) == MarkerSet.end());
}

void MarkerCreator::SelectMarker(vtkProp3D* marker) {
	if (!isMarker(marker)) {
		return;
	}
	if (SelectedMarkerSet.find(marker) != SelectedMarkerSet.end()) {
		UnSelectMarker(marker);
		return;
	}

	if (CurrentMarker == nullptr) {
		CurrentMarker = marker;
	}
	else {
		LastMarker = CurrentMarker;
		CurrentMarker = marker;
	}
	SelectedMarkerSet.insert(marker);
	vtkActor* actor = dynamic_cast<vtkActor*>(marker);
	actor->GetProperty()->SetColor(1, 0, 0);
}

void MarkerCreator::UnSelectMarker(vtkProp3D* marker) {
	vtkActor* actor = dynamic_cast<vtkActor*>(marker);
	actor->GetProperty()->SetColor(0, 1, 0);
	SelectedMarkerSet.erase(marker);
	if (LastMarker == marker) {
		LastMarker = nullptr;
	}
	if (CurrentMarker == marker) {
		CurrentMarker = nullptr;
	}
	return;
}

void MarkerCreator::CreateLine(vtkRenderer* renderer) {
	if (LastMarker == nullptr || CurrentMarker == nullptr) {
		return;
	}
	Line line1;
	Line line2;
	line1.point1 = LastMarker;
	line1.point2 = CurrentMarker;
	line2.point1 = CurrentMarker;
	line2.point2 = LastMarker;

	//if (LineMap.find(line1) != LineMap.end() || LineMap.find(line2) != LineMap.end()) {
	//	return;
	//}

	auto source = vtkLineSource::New();
	source->SetPoint1(LastMarker->GetPosition());
	source->SetPoint2(CurrentMarker->GetPosition());
	auto mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(source->GetOutputPort());
	source->Delete();
	auto Actor = vtkActor::New();
	Actor->SetMapper(mapper);
	mapper->Delete();
	Actor->GetProperty()->SetColor(0, 0, 1);
	Actor->GetProperty()->SetLineWidth(4);
	renderer->AddActor(Actor);

	//vtkVector3d p1 = vtkVector3d(LastMarker->GetPosition());
	//vtkVector3d p2 = vtkVector3d(CurrentMarker->GetPosition());

	//renderer->WorldToView(p1[0], p1[1], p1[2]);
	//renderer->WorldToView(p2[0], p2[1], p2[2]);

	//int* Size = renderer->GetSize();
	//int X = int(Size[0] * (p1[0] + p2[0]) * 0.5);
	//int Y = int(Size[1] * (p1[1] + p2[1]) * 0.5);

	//auto text = vtkTextActor::New();
	//text->SetTextScaleModeToProp();
	//text->SetDisplayPosition(X, Y);
	//text->SetInput("Hello!");
	//text->GetPosition2Coordinate()->SetCoordinateSystemToNormalizedViewport();
	//text->GetPosition2Coordinate()->SetValue(0.6, 0.1);
	//text->GetTextProperty()->SetFontSize(18);
	//text->GetTextProperty()->SetFontFamilyToArial();
	//renderer->AddViewProp(text);
	//LineInfo info;
	//info.Line = Actor;
	//LineMap.insert(pair<Line,LineInfo>(line1,info));
}
