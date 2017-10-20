#ifndef MYDIALOG_H
#define MYDIALOG_H

#include "qts.h"
#include "mygridlayout.h"
class MyDialog :public QDialog
{
    Q_OBJECT
public:
    MyDialog(QWidget *parent=Q_NULLPTR);
    void setGridTexts(QList<QString> list);
    void setLocation(int x,int y,int w,int h);
    void setHint(QString);
signals:
     //信号函数，发送被点击的按钮名字
     void onItemClicked(QString itemName,int index);
protected slots:
     void activeQuit();
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void showEvent(QShowEvent *event);
private:
    MyGridLayout *myGrid;
    QVBoxLayout *vLayout;
    QLabel *hint;
};

#endif // MYDIALOG_H
