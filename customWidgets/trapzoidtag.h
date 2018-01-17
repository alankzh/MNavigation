#ifndef TRAPZOIDTAG_H
#define TRAPZOIDTAG_H
#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include "tools/constant.h"
#include <QRect>
#include <QBitmap>

//Ã›–Œ±Í«©
class TrapzoidTag:public QWidget
{
    Q_OBJECT
public:
    TrapzoidTag(QString tag,QWidget *parent=0);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    QPixmap trapzoidPix;
    QString tag;
    int width;
    int height;
};

#endif // TRAPZOIDTAG_H
