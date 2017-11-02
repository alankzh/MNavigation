#include "myfakeprogressqthread.h"

MyFakeProgressQThread::MyFakeProgressQThread(QWidget *progressParent,QObject *obj):QObject(obj)
{
    qThread=new QThread();
    needRun=false;
    progressBar=new ProgressBarWidget(ScreenTools::getComputerScreenWidth()/2,ScreenTools::getComputerScreenHeight()/2,progressParent);
}

MyFakeProgressQThread::~MyFakeProgressQThread(){
    qDebug()<<"MyFakeProgressQThread::~MyFakeProgressQThread()";
    if(qThread){
        qThread->quit();
    }
    qThread->wait();
}

void MyFakeProgressQThread::startFake(){
    qDebug()<<"MyFakeProgressQThread::startFake()";
    this->moveToThread(qThread);
    needRun=true;
    connect(qThread,&QThread::finished,qThread,&QObject::deleteLater,Qt::AutoConnection);
    connect(qThread,&QThread::finished,this,&QObject::deleteLater,Qt::AutoConnection);
    connect(qThread,&QThread::finished,progressBar,&ProgressBarWidget::disappear,Qt::AutoConnection);
    connect(this,&MyFakeProgressQThread::setProgress,progressBar,&ProgressBarWidget::setProgressValue,Qt::AutoConnection);
    qThread->start();
    doWork();
}

void MyFakeProgressQThread::stopFake(){
    QMutexLocker locker(&myLock);
    needRun=false;
}

void MyFakeProgressQThread::setHint(QString text){
    if(!progressBar){
        progressBar->setHint(text);
    }
}

void MyFakeProgressQThread::doWork(){
    qDebug()<<"MyFakeProgressQThread::doWork";
    progressBar->display();
    int value=0;
    QElapsedTimer timer;
    timer.start();
    while(1){
        value++;
        qDebug()<<"sleep start time："<<timer.elapsed();
        //sleep(2);//睡眠两毫秒
        // qDebug()<<"sleep end time："<<timer.elapsed();
        emit setProgress(value);
        if(value==std::numeric_limits<int>::max()){
            break;
        }
        QMutexLocker locker(&myLock);
        if(!needRun){
            //线程结束标记标记为线程结束，退出run函数
            return;
        }
        timer.restart();
    }//while end
}
