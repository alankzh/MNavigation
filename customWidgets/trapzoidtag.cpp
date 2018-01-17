#include "trapzoidtag.h"


TrapzoidTag::TrapzoidTag(QString tag,QWidget *parent):QWidget(parent)
{
    this->tag=tag;
    trapzoidPix=QPixmap(":/resources/trapezoidTag.png","png");
    width=trapzoidPix.size().width();
    height=trapzoidPix.size().height();
    resize(trapzoidPix.size());
    setFixedSize( width, height);
    setMask(trapzoidPix.createHeuristicMask());
    update();
}

void TrapzoidTag::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(event->rect(), trapzoidPix, event->rect());
    painter.setFont(Constant::get12FontSize());
    painter.setPen(QColor(104,104,104));
    painter.drawText(13,17,tag);
}
