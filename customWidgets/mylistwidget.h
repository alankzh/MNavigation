#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H
#include <QListWidget>
#include <QWidget>
#include "dirlistitemwidget.h"
#include <QList>
#include <QListWidgetItem>
#include <QScrollBar>
#include "tools/constant.h"

/**
 * @brief The MyListWidget class
 * 装载文件列表的listview
 */
class MyListWidget:public QListWidget
{
    Q_OBJECT
public:
    MyListWidget(QWidget *parent=0);
    void loadData(QList<DirBean> list);
    void removeAllItems();
public slots:
    void itemSonNeedPressed(int index);
    void itemSonDoubleClicked(int index);
signals:
    void mySonItemBeDoubleClick(int index);
    void mySonItemBePressed(int index);
private:
    QList<DirListItemWidget*> itemWidgetList={};
    QList<QListWidgetItem*> itemList={};
};

#endif // MYLISTWIDGET_H
