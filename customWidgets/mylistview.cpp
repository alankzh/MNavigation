#include "mylistview.h"

MyListView::MyListView(QWidget *parent):QListView(parent)
{
    this->verticalScrollBar()->setStyleSheet(QSCROLLBAR_COMMON_STYLE);
}

MyListView::~MyListView(){

}

//����listview������
void MyListView::loadHistoryDir(QStringList dirList){
    this->dirList=dirList;
    model=new QStringListModel(this);
    model->setStringList(dirList);
    this->setModel(model);
}

//���û��༭listview�����ݵĻص�����
void MyListView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles){
    emit changeItemName(bottomRight.data().toString());
}

//������ţ����õ�ǰѡ����һ��
void MyListView::selectOn(int i){
    QModelIndex index=model->index(i);
    this->setCurrentIndex(index);
}
