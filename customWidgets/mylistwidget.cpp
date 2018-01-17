#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent):QListWidget(parent)
{
    this->verticalScrollBar()->setStyleSheet(QSCROLLBAR_COMMON_STYLE);
}

//装载数据
void MyListWidget::loadData(QList<DirBean> list){
    for(int i=0;i<list.size();i++){
        DirBean bean=list[i];

        QListWidgetItem *oneItem=new QListWidgetItem(this);
        itemList.append(oneItem);

        this->addItem(oneItem);

        DirListItemWidget *itemWidget=new DirListItemWidget(i);
        itemWidget->loadData(bean);
        itemWidgetList.append(itemWidget);

        this->setItemWidget(oneItem,itemWidget);
        connect(itemWidget,SIGNAL(itemDoubleClicked(int)),this,SLOT(itemSonDoubleClicked(int)));
        connect(itemWidget,SIGNAL(fatherImBePressed(int)),this,SLOT(itemSonNeedPressed(int)));
    }
}

//去除全部
void MyListWidget::removeAllItems(){
    this->clear();
    itemList.clear();
    itemWidgetList.clear();
}

//列表栏内item需要被选中
void MyListWidget::itemSonNeedPressed(int index){
    qDebug()<<"MyListWidget::itemSonNeedPressed";
    qDebug()<<index;
    //遍历列表，让选中的被选中，不被选中的不被选中
    for(int i=0;i<itemWidgetList.size();i++){
        if(i==index){
            itemWidgetList[i]->setIsPressed(true);
        }else{
            itemWidgetList[i]->setIsPressed(false);
        }
        itemWidgetList[i]->update();
    }
    emit mySonItemBePressed(index);
}

//列表栏内item双击
void MyListWidget::itemSonDoubleClicked(int index){
    emit mySonItemBeDoubleClick(index);
}
