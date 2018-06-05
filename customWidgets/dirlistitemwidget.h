#ifndef DIRLISTITEMWIDGET_H
#define DIRLISTITEMWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QHBoxLayout>
#include "tools/constant.h"
#include "customModel/dirbean.h"
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QDebug>
#include <QShowEvent>
#include <QSizePolicy>
#include <QGridLayout>

//�ļ��б���һ�еĲ���,��26����
class DirListItemWidget:public QWidget
{
    Q_OBJECT
public:
    DirListItemWidget(int index,QWidget *parent=0);
    void loadData(DirBean dirBean);
    void setIsPressed(bool isPressed);
    bool getIsPressed();
    void setIndex(int index);
    int getIndex();
public slots:
    void setTagStr(QString name);
signals:
    //�����źű����Լ���˫��
    void itemDoubleClicked(int id);
    //�����źű����Լ���ѡ��
    void fatherImBePressed(int id);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent  *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void showEvent(QShowEvent *event);
private:
    //item index �����Լ��ǵڼ���
    int index;
    QLabel *patientName;
    QLabel *dirSubPath;
    //�Ƿ񱻰���
    bool isPressed=false;
    void setElidedText(QLabel *label);
};

#endif // DIRLISTITEMWIDGET_H
