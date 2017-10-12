#ifndef MYQVTKWIDGET_H
#define MYQVTKWIDGET_H

#include <QtWidgets>
#include <QVTKWidget.h>
#include "vtks.h"
#include "rendersetting.h"

/**
 * @brief The myQVTKWidget class
 * 这个类封装了QVTKWidget控件，让vtk风格代码能专一的存在于这个类中
 * 构造方法传递进来的QWidget是QVTKWdiget控件的包含类(父)
 */
class myVolumeWidget
{
public:
    myVolumeWidget(QWidget *parent);

    bool setVolumeData(const char *dirPath);

    //设置几何位置
    void setLocation(int x,int y,int width,int height);



    void renderValueChange(double shiftValue);

    void updateRender();

    //读取到的体绘制数据
    vtkSmartPointer<vtkDICOMImageReader> dicomReader;

    RenderSetting *settingDefault;

    bool renderVolume=false;

    QVTKWidget* getQVTKWidget();

    vtkSmartPointer<vtkRenderer> getRenderer();
private:
    //封装的控件
    QVTKWidget *qvtkwidget;

    vtkSmartPointer<vtkRenderer> m_pRenderer;
};

#endif // MYQVTKWIDGET_H
