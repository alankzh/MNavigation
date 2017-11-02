#include "markbutton.h"

MarkButton::MarkButton(QWidget *parent):QWidget(parent)
{
    isMarked=false;
    isClicked=false;
    xPos=this->x();
    yPos=this->y();
}

void MarkButton::setBackgroundNormal(const char* fileName,const char* flag){
    backgroundNormalPix=QPixmap(fileName,flag);
    width=backgroundNormalPix.size().width();
    height=backgroundNormalPix.size().height();
    resize(backgroundNormalPix.size());
    setFixedSize( width, height);
    setGeometry(xPos,yPos,width,height);
    setMask(backgroundNormalPix.createHeuristicMask());
    update();
}

void MarkButton::setBackgroundMarked(const char* fileName,const char* flag){
    backgroundMarkedPix=QPixmap(fileName,flag);
}

void MarkButton::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    if(isMarked&&!backgroundMarkedPix.isNull()){
        painter.drawPixmap(event->rect(), backgroundMarkedPix, event->rect());
    }else if(!backgroundNormalPix.isNull()){
        painter.drawPixmap(event->rect(), backgroundNormalPix, event->rect());
    }
}

void MarkButton::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=true;
}

void MarkButton::mouseReleaseEvent(QMouseEvent *event){
    isClicked=false;
    int x=event->pos().x();
    int y=event->pos().y();
    if(x >= 0 &&x <= width &&
            y >= 0 && y <= height){
        if(isMarked){
            isMarked=false;
        }else{
            isMarked=true;
        }
        emit this->clicked();
        emit this->marked(isMarked);
    }
    update();
    Q_UNUSED(event);
}

void MarkButton::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

bool MarkButton::getMarkStatus(){
    return isMarked;
}

bool MarkButton::setPos(int x,int y){
    this->xPos=x;
    this->yPos=y;
    this->repaint();
    return true;
}

int MarkButton::getXpos(){
    return this->xPos;
}

int MarkButton::getYpos(){
    return this->yPos;
}

