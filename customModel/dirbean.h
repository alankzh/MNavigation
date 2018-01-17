#ifndef DIRBEAN_H
#define DIRBEAN_H
#include <QString>

/**
 * @brief The DirBean class
 * 用户以往打开的历史文件会保存在json中
 * name 默认保存CT病人名
 * realPath保存真实文件路径
 * studyDate 保存CT检查日期
 * studyTime 保存CT检查时间
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
