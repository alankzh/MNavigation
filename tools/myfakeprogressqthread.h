#ifndef MYFAKEPROGRESSQTHREAD_H
#define MYFAKEPROGRESSQTHREAD_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include "customWidgets/progressbarwidget.h"
#include <limits>
#include <QElapsedTimer>
#include <QDebug>

/**
 * @brief The MyFakeProgressQThread class
 * ����һ��������ƭ���̣߳��߳���ֻ��һ��ProgressBar��ÿ��ʱ������һ��ֵ��ֱ�����ӵ�99%
 * ��ʱ������Ȼ���������߳��У������߳��к�ʱ��������ʱ��������stopFake()��������ֹͣ����������ʾ
 * ��Ҫʹ�ü̳е�start()����������ʹ��startFake()����
 */
class MyFakeProgressQThread:public QObject
{
    Q_OBJECT
public:
    MyFakeProgressQThread(QWidget *progressBarParent,QObject *obj=0);
    ~MyFakeProgressQThread();
    void setHint(QString text);
    void startFake();
    void stopFake();
    //���غ�����ֻ����������Լ�����ĵ��������������߳�֮�е�
    void doWork();
signals:
    void setProgress(int value);
private:
    ProgressBarWidget *progressBar;
    QThread *qThread;
    QMutex myLock;
    bool needRun;
};

#endif // MYFAKEPROGRESSQTHREAD_H
