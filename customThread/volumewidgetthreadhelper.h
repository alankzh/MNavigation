#ifndef VOLUMEWIDGETTHREADHELPER2222_H
#define VOLUMEWIDGETTHREADHELPER2222_H

#include <QObject>
#include <QMutex>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkCommand.h>
#include <QDebug>
#include <QThread>
#include "progressbarwidget.h"
#include <typeinfo>
#include "myvolumewidget.h"

class VolumeWidgetThreadHelper:public QObject
{
    Q_OBJECT
public:
    VolumeWidgetThreadHelper(QObject *r,QObject *p,QObject *renderWidget,QObject *obj=0);
    ~VolumeWidgetThreadHelper();
    //Ïß³ÌÆô¶¯
    void startThread();
public slots:
    void stopThread();
    void doWork();
signals:
    void beginThread();
    void endThread();
private:
    QMutex mLock;
    bool needRun;
    QThread *thread;
    QObject *progressListener;
    QObject *runner;
    QObject *renderWidget;
};

#endif // VOLUMEWIDGETTHREADHELPER_H
