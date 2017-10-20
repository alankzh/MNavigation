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

/**
 * @brief BackgroundButton::setBackground
 * 设置背景图片
 * @param fileName
 * 背景图片所在位置
 * @param flag
 * 背景图片格式
 */
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
/**
 * 左键点击事件
 */
void GreenButton::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=true;
    update();
}
/**
 * 左键点击后释放事件
 */
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
/**
 * 鼠标移动事件
 * 但是此移动事件只在鼠标左键或右键的点击被触发之后触发
 */
void GreenButton::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

/**
 * @brief BackgroundButton::setPos
 * 设置几何位置，坐标原点在父控件的左上角
 * @param x
 * 位于父控件的x坐标
 * @param y
 * 位于父控件的y坐标
 * @return
 * 返回为true表示坐标没有问题
 * TODO 返回为false表示与其他控件位置冲突
 */
bool GreenButton::setPos(int x,int y){
    this->xPos=x;
    this->yPos=y;
    this->repaint();
    return true;
}
/**
 * @brief BackgroundButton::getXpos
 * 获取基于父控件的x坐标
 * @return
 * 返回int类型
 */
int GreenButton::getXpos(){
    return this->xPos;
}
/**
 * @brief BackgroundButton::getYpos
 * 获取基于父控件的y坐标
 * @return
 * 返回int类型
 */
int GreenButton::getYpos(){
    return this->yPos;
}
/**
 * @brief GreenButton::setWidth
 * 设置控件宽度
 * @param w
 * 控件宽度
 * @return
 * 返回true表示成功
 * TODO 返回false表示与其他控件冲突
 */
bool GreenButton::setWidth(int w){
    this->width=w;
    this->repaint();
    return true;
}
/**
 * @brief GreenButton::setHeight
 * 设置控件高度
 * @param h
 * 控件高度
 * @return
 * 返回true表示成功
 * TODO 返回false表示与其他控件冲突
 */
bool GreenButton::setHeight(int h){
    this->height=h;
    this->repaint();
    return true;
}
/**
 * @brief GreenButton::getWidth
 * 获取控件宽度
 * @return
 * 返回int类型
 */
int GreenButton::getWidth(){
    return this->width;
}
/**
 * @brief GreenButton::getHeight
 * 获取控件高度
 * @return
 * 返回int类型
 */
int GreenButton::getHeight(){
    return this->height;
}

