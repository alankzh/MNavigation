#include "mygridlayout.h"

MyGridLayout::MyGridLayout(QWidget *parent):QGridLayout(parent)
{
    //将内部间距设置为0，简化了无数事件坐标运算
    setHorizontalSpacing(0);
    setVerticalSpacing(0);
    setMargin(0);

}

/**
 * @brief MyGridLayout::setTexts
 * 设置gridLayout内部按钮text
 * @param list
 * QList<QString> 类型顺序存放了按钮的文字
 */
void MyGridLayout::setTexts(QList<QString> list){
    if(!itemNames.isEmpty()){
        itemNames.clear();
        clearLayout();
    }
    itemNames=list;
    //总行数
    rowCount=ceil((itemNames.size()+0.0)/columnCount);
    //设置填充的按钮
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    sizePolicy.setWidthForHeight(1);
    for(int i=0;i<itemNames.size();i++){
        MyPushButton *button=new MyPushButton(itemNames[i]);
        button->setSizePolicy(sizePolicy);
        addWidget(button,i/columnCount,i - ((i/columnCount)*columnCount));
    }
}

//清理里面存在的PushButton
void MyGridLayout::clearLayout(){
    QLayoutItem *item;
    int deleteCount=0;
    while((item=this->takeAt(0))!=NULL){
        deleteCount++;
        if(item->widget()){
         //   item->widget()->setParent(0);
            delete item->widget();
        }
    }
}

void MyGridLayout::setColumnCount(int count){
    columnCount=count;
    //总行数
    rowCount=ceil((itemNames.size()+0.0)/columnCount);
}

int MyGridLayout::getWidth(){
    return width;
}

int MyGridLayout::getHeight(){
    return height;
}

int MyGridLayout::getColumnCount(){
    return columnCount;
}

int MyGridLayout::getRowCount(){
    return rowCount;
}

int MyGridLayout::getXPos(){
    return xPos;
}

int MyGridLayout::getYPos(){
    return yPos;
}

QString MyGridLayout::getItemName(int row, int column){
    if(itemNames.size()>row*columnCount+column){
        QString buttonName=itemNames[row*columnCount+column];
        return buttonName;
    }
    return NULL;
}

/**
 * @brief MyGridLayout::updateGeometry
 * ->setLayout(MyGridLayout)后父控件会自动给予MyGridLayout几何位置
 * 而这个正确的几何位置只会在父控件的showEvent事件被触发后才能得到
 */
void MyGridLayout::updateGeometry(){
    width=this->geometry().width();
    height=this->geometry().height();
    xPos=this->geometry().x();
    yPos=this->geometry().y();
     qDebug()<<"width:"<<width<<" height:"<<height;
    if(height>131){
        QRect rect(xPos,yPos,width,131);
        this->setGeometry(rect);
        height=131;
    }
    qDebug()<<"width:"<<width<<" height:"<<height;
    //设置最小列宽，即按钮完全填充列
    for(int i=0;i<columnCount;i++){
        this->setColumnMinimumWidth(i, width/columnCount);
    }
    //设置最小行高，即按钮完全填充行
    for(int i=0;i<rowCount;i++){
        setRowMinimumHeight(i,height/rowCount);
    }
}


/**
 * @brief MyGridLayout::mouseReleaseEvent
 * Layout类型捕捉不到事件，但是这部分函数的内容有必要在父控件内复制黏贴
 * @param event
 */
//void MyGridLayout::mouseReleaseEvent(QMouseEvent *event){
//    //发送点击信号
//    qDebug()<<" MyMenu::mouseReleaseEvent";
//  //  event->ignore();
//    int x=event->pos().x();
//    int y=event->pos().y();

    //事件发生是否在控件内
//    if(x >= 0 && x <= width &&
//            y >= 0 && y <= height){

//        //所在列,0开头
//        int column=x/(width/columnCount);
//        //所在行，0开头
//        int row=y/(height/rowCount);

//        //判断是否点击的是按钮，若最后一行只有一个按钮，则最后一行的留白处被点击不会发送点击信号
//        if(itemNames.size()>row*columnCount+column){
//            QString buttonName=itemNames[row*columnCount+column];
//            //发送点击信号
//            qDebug()<<"emit!!!!!!!!!!";
//            emit this->onItemClicked(buttonName,row,column);
//        }

//    }
//    update();
//}


/**
  *GridLayout的几何位置将由父控件自动给出
  */
//void MyGridLayout::setLocation(int x,int y,int width,int height){
//    QRect *rect=new QRect(x,y,width,height);
//    this->width=width;
//    this->height=height;
//    this->setGeometry(*rect);
//    //设置最小列宽，即按钮完全填充列
//    for(int i=0;i<columnCount;i++){
//        setColumnMinimumWidth(i, width/columnCount);
//    }
//    //设置最小行高，即按钮完全填充行
//    for(int i=0;i<rowCount;i++){
//        setRowMinimumHeight(i,height/rowCount);
//    }
//}


