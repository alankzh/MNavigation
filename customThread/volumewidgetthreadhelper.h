#ifndef VOLUMEWIDGETTHREADHELPER_H
#define VOLUMEWIDGETTHREADHELPER_H
#include <QObject>
#include <QMutex>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkCommand.h>
#include <QDebug>
#include <QThread>
#include "mainwindow.h"
#include "progressbarwidget.h"
#include <typeinfo>
#include "myvolumewidget.h"

class volumeWidgetThreadHelper:public QObject
{
    Q_OBJECT
public:
    volumeWidgetThreadHelper(QObject *r,QObject *p,QObject *obj=0);
    ~volumeWidgetThreadHelper();
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
};

#endif // VOLUMEWIDGETTHREADHELPER_H
