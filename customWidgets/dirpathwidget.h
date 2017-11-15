#ifndef DIRPATHWIDGET_H
#define DIRPATHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QObject>
#include <QEvent>

/**
 * @brief The DirPathWidget class
 * ѡ���ļ�·���Ĵ��ڣ������ļ�·��ӳ����
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
