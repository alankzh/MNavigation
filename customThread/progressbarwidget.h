#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include "progressreceive.h"

class ProgressBarWidget:public QWidget
{
    Q_OBJECT
public:
    ProgressBarWidget(int xPos,int yPos,QWidget *parent=0);
    void display();
    void setHint(QString text);
public slots:
    void disappear();
    void threadBegin();//override
    void threadDone();//override
    void setProgressValue(int value);//override
signals:
    void complete();

private:
    QProgressBar *proBar;
    QLabel *hint;
};

#endif // PROGRESSBARWIDGET_H
