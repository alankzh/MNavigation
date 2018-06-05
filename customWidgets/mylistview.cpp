#include "mylistview.h"

MyListView::MyListView(QWidget *parent):QListView(parent)
{
    this->verticalScrollBar()->setStyleSheet(QSCROLLBAR_COMMON_STYLE);
}

MyListView::~MyListView(){

}

//设置listview的数据
void MyListView::loadHistoryDir(QStringList dirList){
    this->dirList=dirList;
    model=new QStringListModel(this);
    model->setStringList(dirList);
    this->setModel(model);
}

//当用户编辑listview的数据的回调方法
void MyListView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles){
    emit changeItemName(bottomRight.data().toString());
}

//传入序号，设置当前选中哪一行
void MyListView::selectOn(int i){
    QModelIndex index=model->index(i);
    this->setCurrentIndex(index);
}
