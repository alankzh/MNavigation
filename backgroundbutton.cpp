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

/**
 * @brief BackgroundButton::setBackground
 * 设置背景图片
 * @param fileName
 * 背景图片所在位置
 * @param flag
 * 背景图片格式
 */
void BackgroundButton::setBackground(const char* fileName,const char* flag){
    backgroundPix=QPixmap(fileName,flag);
    width=backgroundPix.size().width();
    height=backgroundPix.size().height();
 //   qDebug()<<"width:"<<width<<"height:"<<height;
    resize(backgroundPix.size());
    setFixedSize( width, height);
    setGeometry(xPos,yPos,width,height);
    setMask(backgroundPix.createHeuristicMask());
 //   this->raise();
    update();
}

/**
 * @brief BackgroundButton::paintEvent
 * 绘制触发事件，当按钮被点击时会绘制一层clickColor在按钮之上
 * 用来表达点击效果
 */
void BackgroundButton::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
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
/**
 * 左键点击事件
 */
void BackgroundButton::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
    isClicked=true;
    update();
}
/**
 * 左键点击后释放事件
 */
void BackgroundButton::mouseReleaseEvent(QMouseEvent *event){
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
void BackgroundButton::mouseMoveEvent(QMouseEvent *event){
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
bool BackgroundButton::setPos(int x,int y){
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
int BackgroundButton::getXpos(){
    return this->xPos;
}
/**
 * @brief BackgroundButton::getYpos
 * 获取基于父控件的y坐标
 * @return
 * 返回int类型
 */
int BackgroundButton::getYpos(){
    return this->yPos;
}
/**
 * @brief BackgroundButton::setClickedColor
 * 设置表达点击效果的颜色值
 * @param color
 * QColor颜色值，点击时将被绘制在按钮最上层
 */
void BackgroundButton::setClickedColor(QColor color){
    clickColor=color;
}
