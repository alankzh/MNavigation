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

//这个窗口盛放一个单一的QVTKWidget，并且带有标签和与之相关联的滑动条
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
    //所盛放的qvtk容器
    QVTKWidget *qvtkContentWidget=NULL;
    //说明滑动条意义
    QLabel *sliderMean;
    //滑动条
    QSlider *slider;
    //滑动条滑动到的数值
    QLabel *sliderNum;
    //标签
    QString tag;

    int min;
    int max;
};

#endif // SINGLERENDERWIDGET_H
