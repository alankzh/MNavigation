#ifndef MYQVTKWIDGET_H
#define MYQVTKWIDGET_H

#include <QtWidgets>
#include <QWidget>
#include <QVTKWidget.h>
#include "vtks.h"
#include "MarkerCreator.h"
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

    void setLocation(int x,int y,int width,int height);

    vtkSmartPointer<vtkVolume> getVolume();

    void updateRender();

    vtkSmartPointer<vtkDICOMImageReader> dicomReader;

    vtkSmartPointer<vtkVolume> volume;

    bool hasVolumeData();

    vtkSmartPointer<vtkRenderer> getRenderer();

	vtkVector<double, 6> GetVolumeBounds() const;

	void ShiftRenderFunction(double shift);

	void SetRenderPropertyType(std::string property_name);

private:

    vtkSmartPointer<vtkRenderer> m_pRenderer;

	vtkVector<double, 6> VolumeBounds;

    bool hasVolume=false;

	vtkSmartPointer<vtkEventQtSlotConnect> vtkConnections;

	void ListenVTKInteractorEvent();

	MarkerCreator mc;

	void Mark(vtkRenderWindowInteractor* iren);

	void SelectMark(vtkRenderWindowInteractor* iren);

	void DrawLine();

signals:
	void OnMarkClick(vtkVector3d ModelPosition);

public slots:

	void MarkReact(vtkVector3d ModelPosition);

	void vtkInteractorEventDispatch(vtkObject* obj, unsigned long, void*, void*);
};

#endif // MYQVTKWIDGET_H
