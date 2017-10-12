#include "backgroundbutton.h"

BackgroundButton::BackgroundButton(QWidget *parent):QWidget(parent)
{
    clickColor=QColor(170,128,38,150);
    xPos=this->x();
    yPos=this->y();
    width=60;
    height=60;
    resize(QSize( width,height));
    setFixedSize( width, height);
}

void BackgroundButton::setBackground( char* fileName, char* flag){
    backgroundPix=QPixmap(fileName,flag);
    width=backgroundPix.size().width();
    height=backgroundPix.size().height();
    qDebug()<<"width:"<<width<<" height:"<<height;
    resize(backgroundPix.size());
    setFixedSize( width, height);
    setGeometry(xPos,yPos,width,height);
    setMask(backgroundPix.createHeuristicMask());
 //   this->raise();
    update();
}

void BackgroundButton::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    qDebug()<<"BackgroundButton::paintEvent";
    QPainter painter(this);
    painter.drawPixmap(event->rect(), backgroundPix, event->rect());
    if(isClicked){
       QBrush brush;
       brush.setColor(clickColor);
       brush.setStyle(Qt::SolidPattern);
       painter.setBrush(brush);
       painter.setPen(Qt::NoPen);
       painter.drawRect(QRect(0,0,width,height));
    }
}

void BackgroundButton::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=true;
    update();
}

void BackgroundButton::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=false;
    //发送点击信号
    qDebug()<<"emit!!!!!!!!!!";
    emit this->clicked();
    update();
}

void BackgroundButton::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

bool BackgroundButton::setPos(int x,int y){
    this->xPos=x;
    this->yPos=y;
    this->repaint();
    return true;
}

int BackgroundButton::getXpos(){
    return this->xPos;
}

int BackgroundButton::getYpos(){
    return this->yPos;
}

void BackgroundButton::setClickedColor(QColor color){
    clickColor=color;
}
