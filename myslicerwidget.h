#ifndef MYSLICERWIDGET_H
#define MYSLICERWIDGET_H

#include "vtks.h"
#include "qts.h"
#include <QWidget>


class mySlicerWidget : public QVTKWidget
{	
	Q_OBJECT
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

	ORIENTATION GetOrientation() const;

    //设置几何位置
    void setLocation(int x,int y,int width,int height);

    void setSlicerValue(int shiftValue);

	void setSlicerValue(double ratio);

    void updateRender();

    int getSlicerMax();

    int getSlicerMin();

    int getSlicer();

    vtkSmartPointer<vtkImageViewer2> getImageViewer2();

protected:
    void setOrientation(ORIENTATION o);

private:
    //截面窗口,封装了自己的vtk管线
    vtkSmartPointer<vtkImageViewer2> imageViewer2;

	vtkSmartPointer<vtkEventQtSlotConnect> vtkConnections;

	void ListenMarkClick();

	void DrawMarker(vtkVector3d ModelPosition, vtkActor* marker);

signals:
	void OnMarkClick(vtkVector3d ModelPosition);

public slots:

	void MarkReact(vtkVector3d ModelPosition);
	
	void Mark(vtkObject* obj, unsigned long, void*, void*);
	
};

#endif // MYSLICERWIDGET_H
