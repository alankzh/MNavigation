#ifndef EMITBUTTON_H
#define EMITBUTTON_H
#include <QPushButton>
#include <QString>
#include <QRadioButton>
#include <QDebug>

/**
 * @brief The emitButton class
 * 这个按钮能够将它的Text发射出去
 */
class EmitButton:public QRadioButton
{
    Q_OBJECT
public:
    EmitButton(QString text,QWidget *parent=0);
public slots:
    void onSelfClicked(bool c);
signals:
    void sendText(QString buttonName);
};

#endif // EMITBUTTON_H
