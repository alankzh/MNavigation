#include "greenbutton.h"

GreenButton::GreenButton(QWidget *parent):QWidget(parent)
{
    //默认高宽为60
    GreenButton(parent,60,60);
}

GreenButton::GreenButton(QWidget *parent, int width, int height):QWidget(parent){
   //默认
   GreenButton(parent,1531,55,width,height);
}

GreenButton::GreenButton(QWidget *parent,int xPos,int yPos,int width,int height):QWidget(parent){
    isClicked=false;
}

void GreenButton::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    if(isClicked){
        QPen pen(QColor(0,227,57));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(QColor(0,255,64));
    }else{
        QPen pen(QColor(0,227,57));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(QColor(0,227,57));
    }
    QRectF rect(xPos,yPos,width,height);
    painter.drawRoundedRect(rect,5,5);
    painter.end();
}

void GreenButton::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

void GreenButton::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

void GreenButton::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
    if(event->buttons()&Qt::LeftButton){
        isClicked=true;
        this->repaint();
    }else if(isClicked){
        isClicked=false;
        this->repaint();
    }
}

bool GreenButton::setXpos(int x){
    this->xPos=x;
    this->repaint();
    return true;
}

bool GreenButton::setYpos(int y){
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
