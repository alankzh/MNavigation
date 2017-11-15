#ifndef DIRPATHWIDGET_H
#define DIRPATHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QObject>
#include <QEvent>

/**
 * @brief The DirPathWidget class
 * 选择文件路径的窗口，更改文件路径映射名
 */
class DirPathWidget:public QWidget
{
    Q_OBJECT
public:
    DirPathWidget(QWidget *parent);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
private:

};

#endif // DIRPATHWIDGET_H
