#include "volumewidgetthreadhelper.h"

VolumeWidgetThreadHelper::VolumeWidgetThreadHelper(QObject *r,QObject *p,QObject *render,QObject *obj):QObject(obj)
{
    progressListener=p;
    runner=r;
    renderWidget=render;
}

VolumeWidgetThreadHelper::~VolumeWidgetThreadHelper(){
    qDebug()<<"VolumeWidgetThreadHelper::~VolumeWidgetThreadHelper";
}

void VolumeWidgetThreadHelper::startThread(){
    qDebug()<<"ThreadHelperObj::startThread";
    thread=new QThread();
    this->moveToThread(thread);
    connect(thread,&QThread::finished,thread,&QObject::deleteLater);
    connect(thread,&QThread::finished,this,&QObject::deleteLater);
    connect(this,SIGNAL(beginThread()),progressListener,SLOT(threadBegin()));
    connect(this,SIGNAL(beginThread()),this,SLOT(doWork()));
    connect(runner,SIGNAL(done()),this,SLOT(stopThread()));
    connect(runner,SIGNAL(interrupt()),thread,SLOT(quit()));
    connect(this,SIGNAL(endThread()),thread,SLOT(quit()));
    connect(this,SIGNAL(endThread()),progressListener,SLOT(threadDone()));
    connect(this,SIGNAL(endThread()),runner,SLOT(onThreadDone()));
    connect(this,SIGNAL(endThread()),renderWidget,SLOT(onDataLoadingDone()));
    connect(runner,SIGNAL(setProgress(int)),progressListener,SLOT(setProgressValue(int)));

    thread->start();
    emit beginThread();
}

void VolumeWidgetThreadHelper::stopThread(){
    qDebug()<<"ThreadHelperObj::stopThread";
    if(thread!=NULL){
        emit endThread();
    }
}

//beginThread�źŷ��ͺ�doWork����
//����ʱThreadHelperObj��Ϊ�Ѿ�moveToThread�ˣ������еĵ��ö������߳���
void VolumeWidgetThreadHelper::doWork(){
    qDebug()<<"ThreadHelperObj::doWork";
    qDebug()<<"subThreadID��"<<QThread::currentThreadId();
    if(runner!=NULL){
        static_cast<myVolumeWidget*>(runner)->doInThread();
    }
}
