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


//四个渲染窗口的布局
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
    //标题栏
    QLabel *title;
    //检查ID 显示在病人名前，大写粗体
    QLabel *studyID;
    //病人名
    QLabel *patientName;
    //TODO用其他用户更关心的量替换这个显示量 体绘制缩放度
    QLabel *volumeScale;
    //TODO用其他用户更关心的量替换这个显示量 体绘制旋转量
    QLabel *volumeRotation;
    //体绘制窗口正常大小标识
    ThreeBackgroundButton *normalSizeButton;
    //体绘制窗口最大化
    ThreeBackgroundButton *blowSizeButton;
    //体绘制窗口是最大化的吗？
    bool sizeIsBlow=false;

    SingleRenderWidget *volumeWidgetRendow=NULL;
    SingleRenderWidget *sagitalWidgetRendow=NULL;
    SingleRenderWidget *coronalWidgetRendow=NULL;
    SingleRenderWidget *axialWidgetRendow=NULL;
};

#endif // DRAWWIDGET_H
