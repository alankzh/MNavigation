#ifndef SINGLERENDERWIDGET_H
#define SINGLERENDERWIDGET_H
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QVTKWidget.h>
#include <QSlider>
#include "trapzoidtag.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "customWidgets/backgroundbutton.h"
#include "tools/constant.h"
#include <QSizePolicy>
#include "myvolumewidget.h"
#include "myslicerwidget.h"

//�������ʢ��һ����һ��QVTKWidget�����Ҵ��б�ǩ����֮������Ļ�����
class SingleRenderWidget:public QWidget
{
    Q_OBJECT
public:
    SingleRenderWidget(QString tag,QWidget *parent=0);
    ~SingleRenderWidget();
    QVTKWidget* getContentWidget();
    void loadData();
public slots:
    void setSliderRange(int min,int max);
    void setSliderValue(int value);
    void setSliderValueInit();
    void onSliderValueChanged(int value);
signals:
    void sliderValueChanged(int value);
private:
    //��ʢ�ŵ�qvtk����
    QVTKWidget *qvtkContentWidget=NULL;
    //˵������������
    QLabel *sliderMean;
    //������
    QSlider *slider;
    //����������������ֵ
    QLabel *sliderNum;
    //��ǩ
    QString tag;

    int min;
    int max;
};

#endif // SINGLERENDERWIDGET_H
