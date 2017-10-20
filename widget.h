#ifndef WIDGET_H
#define WIDGET_H

#include <strstream>
#include <string>
#include <QWidget>
#include <vtkSmartPointer.h>
#include <QFileDialog>
#include <QDir>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <QVTKWidget.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <QDebug>
#include <vtkDICOMImageReader.h>
#include <vtkImageData.h>
#include <vtkVolume.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorObserver.h>
#include <vtkOutputWindow.h>
#include <vtkImageViewer2.h>
#include <QPixmap>
#include <QBitmap>
#include <QtWidgets>
#include <vtkCamera.h>
#include <QMouseEvent>
#include <QPoint>
#include <vtkEventQtSlotConnect.h>
#include <rendersetting.h>
#include <QKeyEvent>
#include <QPaintEvent>
#include "greenbutton.h"
#include <vtkActor.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <QVTKInteractor.h>


#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include "vtkcustomtransformanimationcue.h"
#include <vtkInteractorStyleTrackballCamera.h>
#include "stlmanager.h"
#include <vtkCirclePackToPolyData.h>
#include <vtkLine.h>
#include <vtkLineSource.h>

class vtkImageViewer2;
class vtkRenderer;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

    RenderSetting *settingDefault;
private slots:

    //响应打开体绘制数据源文件夹的函数
    void onOpenVolumeDir();

    void on_volumeSlider_valueChanged(int value);

    void on_sagitalSlider_valueChanged(int value);

    void on_coronalSlider_valueChanged(int value);

    void on_axialSlider_valueChanged(int value);

    void mouseClick(vtkObject *obj, unsigned long, void*, void*);//vtk主窗口中的鼠标点击事件
    void sagitalClicked(vtkObject *obj, unsigned long, void*, void*);
    void axialClicked(vtkObject *obj, unsigned long, void*, void*);
    void coronalClicked(vtkObject *obj, unsigned long, void*, void*);

    void on_navigationButton_clicked();

    void on_greenButton1_clicked();

    void on_greenButton2_clicked();

    void on_translateButton_clicked();

private:
    Ui::Widget *ui;

    vtkSmartPointer<vtkEventQtSlotConnect> m_vtkQtConnect;

    void init();

    void exit();

    void style();

    void setConnect();

    vtkSmartPointer<vtkImageViewer2> m_pImageViewer;

    vtkSmartPointer<vtkRenderer> m_pRenderer;

    QVTKWidget *volumeWidget;//体绘制窗口

    QVTKWidget *sagitalWidget;//与地面垂直，前后方向的截面

    QVTKWidget *coronalWidget;//与地面垂直，左右方向的截面

    QVTKWidget *axialWidget;//与地面平行的截面

    vtkSmartPointer<vtkImageViewer2> m_sagitalViewer2;//截面窗口

    vtkSmartPointer<vtkImageViewer2> m_coronalViewer2;//截面窗口

    vtkSmartPointer<vtkImageViewer2> m_axialViewer2;//截面窗口

    vtkSmartPointer<vtkVolume> volume;//体绘制数据

    int lastposition;

    bool isOpenDir;

    bool canPaintSphere;

    //返回绘制球体的actor指针
    vtkSmartPointer<vtkActor> getSphereActor(double x,double y,double z);
    vtkSmartPointer<vtkActor> getLineActorXY(double x,double y,double x1,double y1);
    vtkSmartPointer<vtkActor> getLineActorXZ(double x,double z,double x1,double z1);
    vtkSmartPointer<vtkActor> getLineActorYZ(double y,double z,double y1,double z1);


    void setQVTKEventConnection(QMouseEvent* event);

    int clickTimes=0;

    vtkSmartPointer<vtkActor> actor;//圆球指针

    //当前操作的stl名
    QString operationStlName;

    StlManager *stlM;
    double proportionZ;
    double proportionY;
    double proportionX;
    bool operationCliked=false;
    vtkSmartPointer<vtkActor> operationActor;
    bool canTarger=false;
protected:
    virtual void keyPressEvent(QKeyEvent *event);

    virtual void paintEvent(QPaintEvent* event);

    //   myGreenButton *greenButton1;
};

#endif  // WIDGET_H
