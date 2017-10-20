#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include "qts.h"
/**
 * @brief The MyPushButton class
 * 这个PushButton不能处理自己的mouseReleaseEvent，而是抛给了父控件
 */
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = Q_NULLPTR);
    explicit MyPushButton(const QString &text, QWidget *parent = Q_NULLPTR);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MYPUSHBUTTON_H
