#include "loadthreadhelper.h"

LoadThreadHelper::LoadThreadHelper(DicomLoader::ErrorCode (*r)(std::string path,ProgressObserver::Pointer observer),QString dirPath,ProgressObserver::Pointer ob,QObject *p,QObject *render,QObject *obj):QObject(obj)
{
    progressListener=p;
    readerFuncPointer=r;
    renderWidget=render;
    this->dirPath=dirPath;
    observer=ob;
}

LoadThreadHelper::~LoadThreadHelper(){
    qDebug()<<"VolumeWidgetThreadHelper::~VolumeWidgetThreadHelper";
}

void LoadThreadHelper::startThread(){
    qDebug()<<"ThreadHelperObj::startThread";
    thread=new QThread();
    this->moveToThread(thread);
    connect(thread,&QThread::finished,thread,&QObject::deleteLater);
    connect(thread,&QThread::finished,this,&QObject::deleteLater);

    connect(this,SIGNAL(beginThread()),progressListener,SLOT(threadBegin()));
    connect(this,SIGNAL(beginThread()),this,SLOT(doWork()));

    connect(this,SIGNAL(endThread()),thread,SLOT(quit()));
    connect(this,SIGNAL(endThread()),progressListener,SLOT(threadDone()));
    connect(this,SIGNAL(endThread()),renderWidget,SLOT(onDataLoadingDone()));

    connect(this,SIGNAL(interrupt()),thread,SLOT(quit()));
    connect(this,SIGNAL(interrupt()),progressListener,SLOT(threadDone()));

    connect(observer->getProgressReceiver(),SIGNAL(emitProgress(int)),progressListener,SLOT(setProgressValue(int)));

    thread->start();
    emit beginThread();
}

void LoadThreadHelper::stopThread(){
    qDebug()<<"ThreadHelperObj::stopThread";
    if(thread!=NULL){
        emit endThread();
    }
}

//beginThread信号发送后，doWork运行
//而此时ThreadHelperObj因为已经moveToThread了，故所有的调用都在子线程中
void LoadThreadHelper::doWork(){
    DicomLoader::ErrorCode error=readerFuncPointer(dirPath.toLocal8Bit().toStdString(),observer);
    if(error==DicomLoader::kDicom){
        stopThread();
    }else{
        emit interrupt();
    }
}
