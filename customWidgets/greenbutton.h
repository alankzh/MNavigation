#ifndef GREENBUTTON_H
#define GREENBUTTON_H

#include <QtWidgets>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

/**
 * @brief The GreenButton class
 * 这里是主窗口右上方两个绿色按钮的封装类
 */
class  GreenButton : public QWidget
{
    Q_OBJECT
public:
    GreenButton(QWidget *parent);

    bool setPos(int x,int y);
    int getXpos();
    int getYpos();
    bool setWidth(int w);
    int getWidth();
    bool setHeight(int h);
    int getHeight();

signals:
    void clicked();

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
