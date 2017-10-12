#ifndef MYSLICERWIDGET_H
#define MYSLICERWIDGET_H

#include "vtks.h"
#include "qts.h"

class mySlicerWidget
{
public:
    mySlicerWidget(QWidget *parent);

    enum ORIENTATION{
        defalut=0,
        XY=1,
        YZ=2,
        XZ=3
    };

    //设置切片数据
    void setSlicerData(vtkSmartPointer<vtkDICOMImageReader> dicomReader,mySlicerWidget::ORIENTATION o);

    //设置几何位置
    void setLocation(int x,int y,int width,int height);

    void setSlicerValue(int shiftValue);

    void updateRender();

    int getSlicerMax();
    int getSlicerMin();
    int getSlicer();

    QVTKWidget* getQVTKWidget();
    vtkSmartPointer<vtkImageViewer2> getImageViewer2();

protected:
    void setOrientation(ORIENTATION o);
private:
    //封装的控件
    QVTKWidget *qvtkwidget;

    //截面窗口,封装了自己的vtk管线
    vtkSmartPointer<vtkImageViewer2> imageViewer2;
};

#endif // MYSLICERWIDGET_H
