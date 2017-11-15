#ifndef PROGRESSRECEIVE_H
#define PROGRESSRECEIVE_H
#include <QObject>

/**
 * @brief The ProgressReceive class
 * ����ฺ�������߳���ת�����ȸ����߳�
 * �����������߳���
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
