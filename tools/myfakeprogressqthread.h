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
 * 这是一个用于欺骗的线程，线程里只有一个ProgressBar，每段时间增加一个值，直到增加到99%
 * 耗时操作仍然存在于主线程中，当主线程中耗时操作结束时主动调用stopFake()函数可以停止进度条的显示
 * 不要使用继承的start()方法启动，使用startFake()启动
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
    //重载函数，只有这个函数以及里面的调用是是跑在子线程之中的
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
