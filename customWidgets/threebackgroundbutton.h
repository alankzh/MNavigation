#ifndef THREEBACKGROUNDBUTTON_H
#define THREEBACKGROUNDBUTTON_H
#include "qts.h"


class ThreeBackgroundButton:public QWidget
{
    Q_OBJECT
public:
    ThreeBackgroundButton(QWidget *parent=0);

    bool setPos(int x,int y);
    int getXpos();
    int getYpos();

    void setBackgroundFront(const char* fileName,const char* flag);
    void setBackgroundReverse(const char* fileName,const char* flag);
    void setBackgroundHover(const char* fileName,const char* flag);

    void setClickStatus(bool clicked);
protected :
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual bool eventFilter(QObject *watched, QEvent *event);

signals:
    void clicked();

private:
    bool isClicked=false;
    bool isHover=false;
    //Constructs a rectangle with (x, y) as its top-left corner.
    int xPos;
    //Constructs a rectangle with (x, y) as its top-left corner.
    int yPos;

    int width;

    int height;

    QPixmap backgroundFrontPix;
    QPixmap backgroundReversePix;
    QPixmap backgroundHoverPix;
};

#endif // THREEBACKGROUNDBUTTON_H
