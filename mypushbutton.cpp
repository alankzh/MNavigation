#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent):QPushButton(parent)
{    
}

MyPushButton::MyPushButton(const QString &text,QWidget *parent):QPushButton(parent)
{
    this->setText(text);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event){
    //�����¼����ø��ؼ���׽,layout���ֲ��и��ؼ�
    event->ignore();
}
