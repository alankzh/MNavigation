#include "threebackgroundbutton.h"

ThreeBackgroundButton::ThreeBackgroundButton(QWidget *parent):QWidget(parent)
{
    xPos=this->x();
    yPos=this->y();
    this->installEventFilter(this);
}

void ThreeBackgroundButton::setBackgroundFront(const char* fileName,const char* flag){
    backgroundFrontPix=QPixmap(fileName,flag);
    width=backgroundFrontPix.size().width();
    height=backgroundFrontPix.size().height();
    resize(backgroundFrontPix.size());
    setFixedSize( width, height);
    setGeometry(xPos,yPos,width,height);
    setMask(backgroundFrontPix.createHeuristicMask());
    update();
}

void ThreeBackgroundButton::setBackgroundReverse(const char* fileName,const char* flag){
    backgroundReversePix=QPixmap(fileName,flag);
}

void ThreeBackgroundButton::setBackgroundHover(const char *fileName, const char *flag){
    backgroundHoverPix=QPixmap(fileName,flag);
}

void ThreeBackgroundButton::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    if(isClicked&&!backgroundReversePix.isNull()){
        painter.drawPixmap(event->rect(), backgroundReversePix, event->rect());
    }else if(isHover&&!backgroundHoverPix.isNull()){
        painter.drawPixmap(event->rect(), backgroundHoverPix, event->rect());
    }else{
         painter.drawPixmap(event->rect(), backgroundFrontPix, event->rect());
    }
}

void ThreeBackgroundButton::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=true;
    update();
}

void ThreeBackgroundButton::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=false;
    //发送点击信号
    int x=event->pos().x();
    int y=event->pos().y();
    if(x >= 0 &&x <= width &&
               y >= 0 && y <= height){
        emit this->clicked();
    }
    update();
}

void ThreeBackgroundButton::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

bool ThreeBackgroundButton::eventFilter(QObject *watched, QEvent *event){
    Q_UNUSED(event);
    Q_UNUSED(watched);
    //鼠标移入事件
    if(event->type()==QEvent::Enter){
        isHover=true;
        this->setCursor(Qt::PointingHandCursor);
        update();
    //鼠标离开事件
    }else if( event->type()==QEvent::Leave){
        isHover=false;
        this->setCursor(Qt::ArrowCursor);
        update();
    }
    return false;
}

bool ThreeBackgroundButton::setPos(int x,int y){
    this->xPos=x;
    this->yPos=y;
    repaint();
    return true;
}

int ThreeBackgroundButton::getXpos(){
    return this->xPos;
}

int ThreeBackgroundButton::getYpos(){
    return this->yPos;
}

