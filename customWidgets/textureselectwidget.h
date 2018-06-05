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
    //����
    QLabel *title;
    //Ӧ�ò���
    QPushButton *putIntoButton;
    //���浱ǰ����
    QPushButton *saveButton;
    //ɾ��ĳ����
    QPushButton *deleteButton;
};

#endif // TEXTURESELECTWIDGET_H
