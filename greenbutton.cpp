#include "greenbutton.h"

GreenButton::GreenButton(QWidget *parent):QWidget(parent)
{

    this->isClicked=false;
    this->xPos=this->x();
    this->yPos=this->y();
    this->width=63;
    this->height=60;
    resize(QSize( width,height));
    setFixedSize( width, height);
}

void GreenButton::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    if(isClicked){
        QPen pen(QColor(0,227,64));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(QColor(0,255,45));
    }else{
        QPen pen(QColor(0,227,64));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(QColor(0,227,60));
    }
    //几何基于父控件坐标
    this->setGeometry(xPos,yPos,width,height);
    //绘制则是基于角色坐标
    QRectF rect(0,0,width,height);
    painter.drawRoundedRect(rect,10,10);
    painter.end();
}

void GreenButton::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=true;
    update();
}

void GreenButton::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=false;
    //发送点击信号
    int x=event->pos().x();
    int y=event->pos().y();
    if(x >= 0 &&x <= width &&
               y >= 0 && y <= height){
        qDebug()<<"emit!!!!!!!!!!";
        emit this->clicked();
    }
    update();
}

void GreenButton::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

bool GreenButton::setPos(int x,int y){
    this->xPos=x;
    this->yPos=y;
    this->repaint();
    return true;
}

int GreenButton::getXpos(){
    return this->xPos;
}

int GreenButton::getYpos(){
    return this->yPos;
}

bool GreenButton::setWidth(int w){
    this->width=w;
    this->repaint();
    return true;
}

bool GreenButton::setHeight(int h){
    this->height=h;
    this->repaint();
    return true;
}

int GreenButton::getWidth(){
    return this->width;
}

int GreenButton::getHeight(){
    return this->height;
}

