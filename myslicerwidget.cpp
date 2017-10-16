#include "myslicerwidget.h"

mySlicerWidget::mySlicerWidget(QWidget *parent)
{
    qvtkwidget=new QVTKWidget(parent);
    //    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();

    //设置窗口背景为黑色，否则三个窗口背景会透明
    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer2->SetRenderWindow(qvtkwidget->GetRenderWindow());
    imageViewer2->SetupInteractor(qvtkwidget->GetRenderWindow()->GetInteractor());
    imageViewer2->GetRenderer()->ResetCamera();
    imageViewer2->GetRenderer()->SetBackground(0,0,0);
    updateRender();
}

/**
 *设置几何位置
*/
void mySlicerWidget::setLocation(int x,int y,int width,int height){
    qvtkwidget->setGeometry(x,y,width,height);
}

/**
 *设置imageViewer2中截图截取位置
*/
void mySlicerWidget::setSlicerValue(int shiftValue){
    imageViewer2->SetSlice(shiftValue);
   // imageViewer2->GetRenderer()->ResetCamera();
    updateRender();
}

/**
 * @brief mySlicerWidget::setSlicerData
 * 设置imageViewer2中截面的数据源
 * @param dicomReader
 * 读取体绘制文件夹的数据源
 * @param o
 * 设置截面截取的坐标平面
 * 坐标平面有XY平面、YZ平面、XZ平面
 */
void mySlicerWidget::setSlicerData(vtkSmartPointer<vtkDICOMImageReader> dicomReader,mySlicerWidget::ORIENTATION o=mySlicerWidget::ORIENTATION::defalut){
    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer2->SetInputConnection(dicomReader->GetOutputPort());
    imageViewer2->SetRenderWindow(qvtkwidget->GetRenderWindow());
    imageViewer2->SetupInteractor(qvtkwidget->GetRenderWindow()->GetInteractor());
 //   imageViewer2->GetRenderer()->ResetCamera();

    if(o!=0){
        setOrientation(o);
    }
    updateRender();
}
/**
 * 设置截面截取的坐标平面
 */
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
/**
 * 获取截面截取最大值
 */
int mySlicerWidget::getSlicerMax(){
    return imageViewer2->GetSliceMax();
}
/**
 * 获取截面截取最小值
 */
int mySlicerWidget::getSlicerMin(){
    return imageViewer2->GetSliceMin();
}
/**
 * 获取截面截取值
 */
int mySlicerWidget::getSlicer(){
    return imageViewer2->GetSlice();
}

/**
 * 更新此窗口内的Render使窗口重新渲染
 */
void mySlicerWidget::updateRender(){
    imageViewer2->GetRenderWindow()->Render();
}

/**
 * 获取此窗口内的核心控件QVTKWidget
 * 慎用
 */
QVTKWidget* mySlicerWidget::getQVTKWidget(){
    return qvtkwidget;
}
/**
 * 获取此窗口内的核心控件vtkImageViewer2
 * 慎用
 */
vtkSmartPointer<vtkImageViewer2> mySlicerWidget::getImageViewer2(){
    return imageViewer2;
}
