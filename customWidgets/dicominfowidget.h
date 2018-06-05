#ifndef DICOMINFOWIDGET_H
#define DICOMINFOWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "tools/constant.h"
#include "customWidgets/backgroundbutton.h"
#include <QSizePolicy>
#include "DicomLoader.h"

class DicomInfoWidget:public QWidget
{
    Q_OBJECT
public:
    DicomInfoWidget(QWidget *parent=0);
    void setInfo(QString dirPath);
private:
    //标题
    QLabel *title;
    //病人名
    QLabel *patientName;
    //病人性别
    QLabel *patientSex;
    //病人出生日期
    QLabel *patientBirthday;
    //文件夹路径
    QLabel *dirPath;
    //检查描述
    QLabel *studyDescription;
    //序列描述
    QLabel *seriesDescription;
    //检查id
    QLabel *studyID;
    //检查日期
    QLabel *studyDate;

    QLabel* getPartingLine();
    QLabel* getPreDescription(QString info);
    void setElidedText(QLabel *label);

};

#endif // DICOMINFOWIDGET_H
