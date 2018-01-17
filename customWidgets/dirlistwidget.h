#ifndef DIRLISTWIDGET_H
#define DIRLISTWIDGET_H

#include <QtWidgets>
#include <QStringList>
#include "mylistview.h"
#include <QList>
#include "customModel/dirbean.h"
#include "DicomLoader.h"
#include "tools/constant.h"
#include "JsonUtils.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "customWidgets/backgroundbutton.h"
#include <QPalette>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include "mylistwidget.h"

/**
 * @brief The DirListWidget class
 * 文件列表布局控件
 */
class DirListWidget:public QWidget
{
    Q_OBJECT
public:
    DirListWidget(QWidget *parent=0);
    ~DirListWidget();
    void saveDirBean(QString name,QString realPath,QString studyDate,QString studyTime);
    void loadPath();
protected:
    virtual void paintEvent(QPaintEvent *event);
public slots:
    void saveItemChange(QString newName);
    void loadButtonClicked();
    void iconButtonClicked();
    void listItemPressed(int index);
    void listItemDoubleClicked(int index);
    void popDirPath(QString path);
signals:
    void loadThisPathData(QString name,QString path);
    void showLoadDialog();
    void showEditDialog(DirBean dirbean);
private:
    void renewal();
    void saveDirList2JSON();
    QVBoxLayout *mainLayout;
    QLabel *title;


    MyListWidget *listWidget;

    QList<DirBean> dirList={};

    QPushButton *loadButton;
    QPushButton *iconButton;

    int index=-1;
    bool strChanged=false;
};

#endif // DIRLISTWIDGET_H
