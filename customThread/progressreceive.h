#ifndef PROGRESSRECEIVE_H
#define PROGRESSRECEIVE_H
#include <QObject>

/**
 * @brief The ProgressReceive class
 * 这个类负责在子线程中转发进度给主线程
 * 它本身处于子线程中
 */
class ProgressReceive:public QObject
{
    Q_OBJECT
public:
    void updateProgress(int progress){
        emit emitProgress(progress);
    }
signals:
    void emitProgress(int progress);
};

#endif // PROGRESSEMITER_H
