#ifndef MYMENU_H
#define MYMENU_H

#include "qts.h"
#include <math.h>
#include "mypushbutton.h"
#include <qsizepolicy.h>
/**
 * @brief The MyMenu class
 * 默认为两列
 */
class MyGridLayout : public QGridLayout
{
    Q_OBJECT
public:
    MyGridLayout(QWidget *parent = Q_NULLPTR);
    ~MyGridLayout();
    void setTexts(QList<QString> list);
    void setColumnCount(int count);
    // void setLocation(int x,int y,int width,int height);
    int getWidth();
    int getHeight();
    int getColumnCount();
    int getRowCount();
    int getXPos();
    int getYPos();
    void updateGeometry();
    QString getItemName(int row,int column);

private:
    int columnCount=2;
    int rowCount=0;
    int width=0;
    int height=0;
    int xPos;
    int yPos;
    QList<QString> itemNames;
    void clearLayout();
    MyPushButton *button0;
    MyPushButton *button1;
    MyPushButton *button2;
    MyPushButton *button3;
    MyPushButton *button4;
    MyPushButton *button5;
    MyPushButton *button6;
};

#endif // MYMENU_H
