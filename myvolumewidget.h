#ifndef MYVOLUMEWIDGET_H
#define MYVOLUMEWIDGET_H

#include "customThread/progressobserver.h"
#include "customThread/progressreceive.h"
#include <QtWidgets>
#include <QWidget>
#include <QVTKWidget.h>
#include "vtks.h"
#include "MarkerCreator.h"
#include <QString>
#include "DicomLoader.h"


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

    void loadData(vtkImageData *data);

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

	void TextUIAdapt();


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

	vtkSmartPointer<vtkTextActor> volume_info;

	vtkSmartPointer<vtkTextActor> property_info;

	vtkSmartPointer<vtkTextActor> mouse_info;

	std::string property_name_;

	void SetPropertyName(std::string name);

    QString dirPath;

    ProgressObserver *observer;
signals:
	void OnMarkClick(vtkVector3d ModelPosition);
    void propertyChanged();

    void payBackFocus();
public slots:

    void SetRenderPropertySlot(std::string property_name);

	void MarkReact(vtkVector3d ModelPosition);

	void vtkInteractorEventDispatch(vtkObject* obj, unsigned long, void*, void*);

};

#endif // MYVOLUMEWIDGET_H
