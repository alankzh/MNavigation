#ifndef DIRBEAN_H
#define DIRBEAN_H
#include <QString>

/**
 * @brief The DirBean class
 * �û������򿪵���ʷ�ļ��ᱣ����json��
 * name Ĭ�ϱ���CT������
 * realPath������ʵ�ļ�·��
 * studyDate ����CT�������
 * studyTime ����CT���ʱ��
 */
class DirBean
{
public:
    DirBean();
    DirBean(QString name,QString realPath,QString studyDate,QString studyTime);

    QString getName();
    void setName(QString name);

    QString getRealPath();
    void setRealPath(QString realPath);

    QString getStudyDate();
    void setStudyDate(QString studyDate);

    QString getStudyTime();
    void setStudyTime(QString studyTime);
private:
    QString name;
    QString realPath;
    QString studyDate;
    QString studyTime;
};

#endif // DIRLISTMODEL_H
