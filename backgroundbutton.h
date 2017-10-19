#ifndef BACKGROUNDBUTTON_H
#define BACKGROUNDBUTTON_H
#include <QtWidgets>


class BackgroundButton: public QWidget
{
     Q_OBJECT
public:
    BackgroundButton(QWidget *parent);

    bool setPos(int x,int y);
    int getXpos();
    int getYpos();

    void setBackground(const char* fileName,char* flag);
    void setClickedColor(QColor color);

protected :
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);


signals:
    void clicked();

private:
    bool isClicked=false;
    bool hasBackground=false;
    //Constructs a rectangle with (x, y) as its top-left corner.
    int xPos;
    //Constructs a rectangle with (x, y) as its top-left corner.
    int yPos;

    int width;

    int height;

    QPixmap backgroundPix;

    QColor clickColor;
};

#endif // BACKGROUNDBUTTON_H
