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
    //����
    QLabel *title;
    //������
    QLabel *patientName;
    //�����Ա�
    QLabel *patientSex;
    //���˳�������
    QLabel *patientBirthday;
    //�ļ���·��
    QLabel *dirPath;
    //�������
    QLabel *studyDescription;
    //��������
    QLabel *seriesDescription;
    //���id
    QLabel *studyID;
    //�������
    QLabel *studyDate;

    QLabel* getPartingLine();
    QLabel* getPreDescription(QString info);
    void setElidedText(QLabel *label);

};

#endif // DICOMINFOWIDGET_H
