#ifndef SELECTPROPERTYWIDGET_H
#define SELECTPROPERTYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QGroupBox>
#include "RenderPropertyGenerator.h"
#include <vector>
#include <string>
#include "emitbutton.h"
#include <QDebug>
#include <QLayoutItem>
#include <QPoint>



class SelectPropertyWidget:public QWidget
{
    Q_OBJECT
public:
    SelectPropertyWidget(QWidget *parent=0);
    void disPlay();
public slots:
    void disPlaySlot();
    void disAppear();
    void setPro(QString proName);
signals:
    void sendProName(std::string proName);
private:
    void loadProperty();
    void removeWidget();
    QGroupBox *groupBox;
    QVBoxLayout *boxLayout=NULL;
    QWidget *parent;
};

#endif // SELECTPROPERTYWIDGET_H
