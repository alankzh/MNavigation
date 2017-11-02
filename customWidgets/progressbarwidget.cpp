#include "progressbarwidget.h"

ProgressBarWidget::ProgressBarWidget(int xPos,int yPos,QWidget *parent):QWidget(parent)
{
    //窗口样式，没有标题栏，最小化，最大化和关闭按钮，纯粹的一个控件
    this->setWindowFlags(Qt::SplashScreen);
    QVBoxLayout *layout=new QVBoxLayout();
    hint=new QLabel();
    hint->setText(QString::fromLocal8Bit("读取数据中……                     "));
    hint->setAlignment(Qt::AlignCenter);
    layout->addWidget(hint);
    proBar=new QProgressBar();
    proBar->setOrientation(Qt::Horizontal);
    proBar->setMinimum(0);
    proBar->setMaximum(100);
    layout->addWidget(proBar);
    this->setLayout(layout);
    this->setGeometry(xPos-(this->width()/2)-50,yPos-(this->height()/2)-50,this->width(),this->height());
    //屏蔽其他窗口交互
    setWindowModality(Qt::WindowModal);
}

void ProgressBarWidget::setProgressValue(int value){
    if(value<=(proBar->maximum()-1)){
         proBar->setValue(value);
         repaint();
    }else{
    }
}

void ProgressBarWidget::display(){
    qDebug()<<"ProgressBarWidget::display()";
    this->show();
    proBar->show();
}

void ProgressBarWidget::disappear(){
    qDebug()<<"ProgressBarWidget::disappear()";
    proBar->close();
    this->close();
    emit complete();
}

void ProgressBarWidget::setHint(QString text){
    hint->setText(text);
    update();
}
