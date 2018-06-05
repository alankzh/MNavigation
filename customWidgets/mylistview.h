#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H
#include <QtWidgets>
#include <tools/constant.h>

class MyListView:public QListView
{
    Q_OBJECT
public:
    MyListView(QWidget *parent=0);
    ~MyListView();
    void loadHistoryDir(QStringList dirList);
    void selectOn(int i);
protected:
    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
signals:
    void changeItemName(QString newName);
private:
    QStringList dirList;
    QStringListModel *model=NULL;
    int index=0;
    QString userEdit;
};

#endif // MYLISTVIEW_H
