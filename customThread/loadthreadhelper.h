#ifndef LOADTHREADHELPER2222_H
#define LOADTHREADHELPER2222_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "DicomLoader.h"
#include <string>
#include "progressobserver.h"
#include "progressbarwidget.h"
#include <QString>

class LoadThreadHelper:public QObject
{
    Q_OBJECT
public:
    LoadThreadHelper(DicomLoader::ErrorCode (*r)(std::string path,ProgressObserver::Pointer observer),QString dirPath,ProgressObserver::Pointer ob,QObject *p,QObject *renderWidget,QObject *obj=0);
    ~LoadThreadHelper();
    //Ïß³ÌÆô¶¯
    void startThread();
public slots:
    void stopThread();
    void doWork();
signals:
    void beginThread();
    void endThread();
    void interrupt();
private:
    bool needRun;
    QThread *thread;
    QObject *progressListener;
    QObject *renderWidget;
    QString dirPath;
    ProgressObserver::Pointer observer;
    DicomLoader::ErrorCode (*readerFuncPointer)(std::string ,ProgressObserver::Pointer observer);

};

#endif // VOLUMEWIDGETTHREADHELPER_H
