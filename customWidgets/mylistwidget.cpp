#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent):QListWidget(parent)
{
    this->verticalScrollBar()->setStyleSheet(QSCROLLBAR_COMMON_STYLE);
}

//װ������
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

//ȥ��ȫ��
void MyListWidget::removeAllItems(){
    this->clear();
    itemList.clear();
    itemWidgetList.clear();
}

//�б�����item��Ҫ��ѡ��
void MyListWidget::itemSonNeedPressed(int index){
    qDebug()<<"MyListWidget::itemSonNeedPressed";
    qDebug()<<index;
    //�����б���ѡ�еı�ѡ�У�����ѡ�еĲ���ѡ��
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

//�б�����item˫��
void MyListWidget::itemSonDoubleClicked(int index){
    emit mySonItemBeDoubleClick(index);
}
