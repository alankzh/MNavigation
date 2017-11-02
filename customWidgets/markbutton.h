#ifndef MARKBUTTON_H
#define MARKBUTTON_H
#include "QtWidgets"


class MarkButton:public QWidget
{
    Q_OBJECT
public:
    MarkButton(QWidget *parent=Q_NULLPTR);
    bool getMarkStatus();
    bool setPos(int x,int y);
    int getXpos();
    int getYpos();
    void setBackgroundNormal(const char* fileName,const char* flag);
    void setBackgroundMarked(const char* fileName,const char* flag);
signals:
    void marked(bool isMarked);
    void clicked();
protected :
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    bool isMarked;
    bool isClicked;

    //Constructs a rectangle with (x, y) as its top-left corner.
    int xPos;
    //Constructs a rectangle with (x, y) as its top-left corner.
    int yPos;

    int width;

    int height;

    QPixmap backgroundNormalPix;
    QPixmap backgroundMarkedPix;
};

#endif // MARKBUTTON_H
