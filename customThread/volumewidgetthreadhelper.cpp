#include "volumewidgetthreadhelper.h"

volumeWidgetThreadHelper::volumeWidgetThreadHelper(QObject *r,QObject *p,QObject *obj):QObject(obj)
{
    progressListener=p;
    runner=r;
}

volumeWidgetThreadHelper::~volumeWidgetThreadHelper(){
}

void volumeWidgetThreadHelper::startThread(){
    qDebug()<<"ThreadHelperObj::startThread";
    thread=new QThread();
    this->moveToThread(thread);
    connect(thread,&QThread::finished,thread,&QObject::deleteLater);
    connect(thread,&QThread::finished,this,&QObject::deleteLater);
    connect(this,SIGNAL(beginThread()),progressListener,SLOT(threadBegin()));
    connect(this,SIGNAL(beginThread()),this,SLOT(doWork()));
    connect(runner,SIGNAL(done()),this,SLOT(stopThread()));
    connect(runner,SIGNAL(interrupt()),this,SLOT(stopThread()));
    connect(this,SIGNAL(endThread()),thread,SLOT(quit()));
    connect(this,SIGNAL(endThread()),progressListener,SLOT(threadDone()));
    connect(this,SIGNAL(endThread()),runner,SLOT(onThreadDone()));
    connect(runner,SIGNAL(setProgress(int)),progressListener,SLOT(setProgressValue(int)));

    thread->start();
    emit beginThread();
}

void volumeWidgetThreadHelper::stopThread(){
    qDebug()<<"ThreadHelperObj::stopThread";
    if(thread){
        emit endThread();
    }
}

//beginThread�źŷ��ͺ�doWork����
//����ʱThreadHelperObj��Ϊ�Ѿ�moveToThread�ˣ������еĵ��ö������߳���
void volumeWidgetThreadHelper::doWork(){
    qDebug()<<"ThreadHelperObj::doWork";
    qDebug()<<"subThreadID��"<<QThread::currentThreadId();
    if(runner!=NULL){
        mLock.lock();
        static_cast<myVolumeWidget*>(runner)->doInThread();
        mLock.unlock();
    }
}
