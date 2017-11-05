#pragma once
#ifndef TEXTANNOTATAION_H
#define	TEXTANNOTATAION_H


#include "vtkSmartPointer.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkVector.h"
namespace Text {

	static vtkSmartPointer<vtkTextActor> CreateAnnotation(std::string input, vtkVector3d color) {
		auto text = vtkSmartPointer<vtkTextActor>::New();
		text->SetInput(input.c_str());
		text->SetTextScaleModeToViewport();
		text->GetTextProperty()->SetColor(color.GetData());
		text->GetTextProperty()->SetFontSize(10);
		return text;
	}

}
#endif // !TEXTANNOTATAION_H