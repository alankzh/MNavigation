#include "dirpathwidget.h"

DirPathWidget::DirPathWidget(QWidget *parent):QWidget(parent)
{

}

void DirPathWidget::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

void DirPathWidget::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

void DirPathWidget::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
}

bool DirPathWidget::eventFilter(QObject *watched, QEvent *event){
    Q_UNUSED(event);
    Q_UNUSED(watched);
    return false;
}

