#ifndef GREENBUTTON_H
#define GREENBUTTON_H

#include <QtWidgets>
#include <QPaintEvent>
#include <QPainter>

class GreenButton : public QWidget
{
    Q_OBJECT

public:

    GreenButton(QWidget *parent);

    GreenButton(QWidget *parent,int width,int height);

    GreenButton(QWidget *parent,int xPos,int yPos,int width,int height);
    bool setXpos(int x);
    bool setYpos(int y);
    int getXpos();
    int getYpos();
    bool setWidth(int w);
    int getWidth();
    bool setHeight(int h);
    int getHeight();

protected :
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);



private:
    int width;
    int height;
    bool isClicked;
    //Constructs a rectangle with (x, y) as its top-left corner.
    int xPos;
    //Constructs a rectangle with (x, y) as its top-left corner.
    int yPos;
};

#endif // GREENBUTTON_H
