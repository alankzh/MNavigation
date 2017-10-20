#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent):QPushButton(parent)
{    
}

MyPushButton::MyPushButton(const QString &text,QWidget *parent):QPushButton(parent)
{
    this->setText(text);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event){
    //忽略事件，让父控件捕捉,layout布局不叫父控件
    event->ignore();
}
