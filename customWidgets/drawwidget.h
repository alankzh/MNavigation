#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QString>
#include "tools/constant.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "backgroundbutton.h"
#include "threebackgroundbutton.h"
#include "singlerenderwidget.h"
#include "myvolumewidget.h"
#include "myslicerwidget.h"
#include "DicomLoader.h"


//�ĸ���Ⱦ���ڵĲ���
class DrawWidget:public QWidget
{
    Q_OBJECT
public:
    DrawWidget(QWidget *parent=0);
    void setInfo();
public slots:
    void normalClicked();
    void blowClicked();

    void loadDataToFourWidget();
signals:
    void sizeChanged(bool blowSize);
private:
    void changeSize(bool setBlowSize);
    //������
    QLabel *title;
    //���ID ��ʾ�ڲ�����ǰ����д����
    QLabel *studyID;
    //������
    QLabel *patientName;
    //TODO�������û������ĵ����滻�����ʾ�� ��������Ŷ�
    QLabel *volumeScale;
    //TODO�������û������ĵ����滻�����ʾ�� �������ת��
    QLabel *volumeRotation;
    //����ƴ���������С��ʶ
    ThreeBackgroundButton *normalSizeButton;
    //����ƴ������
    ThreeBackgroundButton *blowSizeButton;
    //����ƴ�������󻯵���
    bool sizeIsBlow=false;

    SingleRenderWidget *volumeWidgetRendow=NULL;
    SingleRenderWidget *sagitalWidgetRendow=NULL;
    SingleRenderWidget *coronalWidgetRendow=NULL;
    SingleRenderWidget *axialWidgetRendow=NULL;
};

#endif // DRAWWIDGET_H
