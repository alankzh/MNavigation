#include "mydialog.h"

MyDialog::MyDialog(QWidget *parent):QDialog(parent)
{
    vLayout=new QVBoxLayout();

    myGrid=new MyGridLayout();
    hint=new QLabel(QString::fromLocal8Bit("请选择导入的.stl模型"));
    hint->setAlignment(Qt::AlignTop);
    vLayout->addWidget(hint);
    vLayout->addLayout(myGrid);

    QPushButton *closeButton=new QPushButton(QString::fromLocal8Bit("取消"));
    vLayout->addWidget(closeButton);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(activeQuit()));
    setWindowFlags(Qt::CustomizeWindowHint);
    setLayout(vLayout);

    setMaximumHeight(200);
    setMaximumWidth(200);
    //设置为如果不处理，则其他窗口的事件无法触发(按钮无法点击等)
    setModal(true);
}

/**
 * @brief MyDialog::mouseReleaseEvent
 * 点击gridLayout布局内的按钮会发送事件onItemClicked
 * @param event
 */
void MyDialog::mouseReleaseEvent(QMouseEvent *event){
    int x=event->pos().x()-myGrid->getXPos();
    int y=event->pos().y()-myGrid->getYPos();
    int width=myGrid->getWidth();
    int height=myGrid->getHeight();
    int columnCount=myGrid->getColumnCount();
    int rowCount=myGrid->getRowCount();

    //如果0行无数据的情况下
    if(rowCount==0){
        return ;
    }
    //事件发生是否在gridLayout布局内
    if(x >= 0 && x <= width && y >= 0 && y <= height){
        //所在列,0开头
        int column=x/(width/columnCount);
        //所在行，0开头
        int row=y/(height/rowCount);

        //判断是否点击的是按钮，若最后一行只有一个按钮，则最后一行的留白处被点击不会发送点击信号
        QString buttonName=myGrid->getItemName(row,column);
        if(buttonName!=NULL){
            //发送点击信号
            qDebug()<<"emit!!!"<<"  buttonName:"<<buttonName<<"  row:"<<row<<"  column"<<column;
            int index=row*columnCount+column;
            emit this->onItemClicked(buttonName,index);
            this->close();
        }
    }
    update();
}

/**
 * @brief MyDialog::showEvent
 * 当showEvent事件被触发时，控件的正确尺寸终于得到计算
 * @param event
 */
void MyDialog::showEvent(QShowEvent *event){
    myGrid->updateGeometry();
}

/**
 * @brief MyDialog::setGridTexts
 * 设置网格按钮的名字
 * @param list
 */
void MyDialog::setGridTexts(QList<QString> list){
  //  myGrid->setTexts(list);
    myGrid->setTexts(list);
}

/**
 * @brief MyDialog::setLocation
 * setGeometry方法可以设置MyDialog的坐标，这里封装一层，以备后续可能的操作
 * TODO 考察这个方法是否需要删掉
 * @param x
 * @param y
 * @param w
 * @param h
 */
void MyDialog::setLocation(int x, int y, int w, int h){
    setGeometry(x,y,w,h);
}

void MyDialog::setHint(QString str){
    hint->setText(str);
}

void MyDialog::activeQuit(){
    this->close();
}
