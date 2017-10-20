#ifndef MYQVTKWIDGET_H
#define MYQVTKWIDGET_H

#include <QtWidgets>
#include <QWidget>
#include <QVTKWidget.h>
#include "vtks.h"
#include "rendersetting.h"
/**
 * @brief The myQVTKWidget class
 * 这个类封装了QVTKWidget控件，让vtk风格代码能专一的存在于这个类中
 * 构造方法传递进来的QWidget是QVTKWdiget控件的包含类(父)
 */
class myVolumeWidget : public QVTKWidget
{	
	Q_OBJECT
public:
    myVolumeWidget(QWidget *parent);

    bool setVolumeData(const char *dirPath);

    //设置几何位置
    void setLocation(int x,int y,int width,int height);

    vtkSmartPointer<vtkVolume> getVolume();

    void renderValueChange(double shiftValue);

    void updateRender();

    //读取到的体绘制数据
    vtkSmartPointer<vtkDICOMImageReader> dicomReader;
    //绘制的体绘制数据
    vtkSmartPointer<vtkVolume> volume;

    RenderSetting *settingDefault;

    bool hasVolumeData();

    vtkSmartPointer<vtkRenderer> getRenderer();

	vtkVector<double, 6> GetVolumeBounds() const;

private:

    vtkSmartPointer<vtkRenderer> m_pRenderer;

	vtkVector<double, 6> VolumeBounds;

    //是否有体绘制数据
    bool hasVolume=false;

	vtkSmartPointer<vtkEventQtSlotConnect> vtkConnections;

	//监听内部标记事件
	void ListenMarkClick();

signals:
	void OnMarkClick(vtkVector3d ModelPosition);

public slots:

	void MarkReact(vtkVector3d ModelPosition);

	void Mark(vtkObject* obj, unsigned long, void*, void*);
};

#endif // MYQVTKWIDGET_H
