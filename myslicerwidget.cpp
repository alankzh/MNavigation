#include "myslicerwidget.h"

mySlicerWidget::mySlicerWidget(QWidget *parent)
{
    qvtkwidget=new QVTKWidget(parent);
    //    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();

    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer2->SetRenderWindow(qvtkwidget->GetRenderWindow());
    imageViewer2->SetupInteractor(qvtkwidget->GetRenderWindow()->GetInteractor());
    imageViewer2->GetRenderer()->ResetCamera();
    imageViewer2->GetRenderer()->SetBackground(0,0,0);
    updateRender();
}

//设置几何位置
void mySlicerWidget::setLocation(int x,int y,int width,int height){
    qvtkwidget->setGeometry(x,y,width,height);
}

void mySlicerWidget::setSlicerValue(int shiftValue){
    imageViewer2->SetSlice(shiftValue);
    imageViewer2->GetRenderer()->ResetCamera();
    updateRender();
}


void mySlicerWidget::setSlicerData(vtkSmartPointer<vtkDICOMImageReader> dicomReader,mySlicerWidget::ORIENTATION o=mySlicerWidget::ORIENTATION::defalut){
    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer2->SetInputConnection(dicomReader->GetOutputPort());
    imageViewer2->SetRenderWindow(qvtkwidget->GetRenderWindow());
    imageViewer2->SetupInteractor(qvtkwidget->GetRenderWindow()->GetInteractor());
    imageViewer2->GetRenderer()->ResetCamera();

    if(o!=0){
        setOrientation(o);
    }
    updateRender();
}

void mySlicerWidget::setOrientation(mySlicerWidget::ORIENTATION o){
    switch(o){
    case XY:
        imageViewer2->SetSliceOrientationToXY();
        break;
    case YZ:
        imageViewer2->SetSliceOrientationToYZ();
        break;
    case XZ:
        imageViewer2->SetSliceOrientationToXZ();
        break;
    }
}

int mySlicerWidget::getSlicerMax(){
    return imageViewer2->GetSliceMax();
}
int mySlicerWidget::getSlicerMin(){
    return imageViewer2->GetSliceMin();
}
int mySlicerWidget::getSlicer(){
    return imageViewer2->GetSlice();
}


void mySlicerWidget::updateRender(){
    imageViewer2->GetRenderWindow()->Render();
}

QVTKWidget* mySlicerWidget::getQVTKWidget(){
    return qvtkwidget;
}
vtkSmartPointer<vtkImageViewer2> mySlicerWidget::getImageViewer2(){
    return imageViewer2;
}
