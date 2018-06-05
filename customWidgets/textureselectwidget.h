#ifndef TEXTURESELECTWIDGET_H
#define TEXTURESELECTWIDGET_H
#include <QWidget>
#include <QLabel>
#include "backgroundbutton.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "tools/constant.h"

class TextureSelectWidget:public QWidget
{
    Q_OBJECT
public:
    TextureSelectWidget(QWidget *parent=0);
public slots:
    void putIntoClicked();
    void saveClicked();
    void deleteClicked();
private:
    //标题
    QLabel *title;
    //应用材质
    QPushButton *putIntoButton;
    //保存当前材质
    QPushButton *saveButton;
    //删除某材质
    QPushButton *deleteButton;
};

#endif // TEXTURESELECTWIDGET_H
