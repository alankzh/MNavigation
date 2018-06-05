#ifndef OPERATIONPLANWIDGET_H
#define OPERATIONPLANWIDGET_H
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <tools/constant.h>
#include "customWidgets/mylistview.h"
#include <QIcon>

//手术方案显示控件
class OperationPlanWidget:public QWidget
{
    Q_OBJECT
public:
    OperationPlanWidget(QWidget *parent=0);
public slots:
    void playClicked();
    void creatClicked();
    void deleteClicked();
private:
    QLabel *title;

    MyListView *listView;

    QPushButton *playButton;
    QPushButton *creatButton;
    QPushButton *deleteButton;

    QStringList planStrList={};

    QPixmap backgroundPix;
};

#endif // OPERATIONPLANWIDGET_H
