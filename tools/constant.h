#ifndef CONSTANT_H
#define CONSTANT_H

/**
  *
  *����ౣ�������еĳ���
  *
  */

#include <QString>
#include <QDir>
#include <QColor>
#include <QFont>
#include <QPalette>
#include <QSize>
#include <QSizePolicy>

// never use it
//#define PROPERTY_PATH (((QDir::currentPath())+("/myPath")))
//#d9d9d9
#define GRAY (QColor(217,217,217))
//#f5f5f5
#define LIGHT_GRAY (QColor(245,245,245))
//#f0f0f0
#define WHITE (QColor(240,240,240))
//#5a5a5a
#define BORD_COLOR (QColor(90,90,90))
//#595959
#define SLIDER_BACKGROUND (QColor(89,89,89))
//#686868
#define FONT_COLOR (QColor(104,104,104))
//#a1a1a1
#define FONT_LITTLE_COLOR (QColor(161,161,161))
//#3f3f3f
#define FONT_DEEP_COLOR (QColor(63,63,63))
//#e7e7e7
#define LIST_PRESS_COLOR (QColor(231,231,231))
//#0888ff
#define BLUE (QColor(8,136,255))
//#bcb9b9
#define SLIDER_GROOVE (QColor(188,185,185))
//����ƴ�����С��С
#define RENDER_WINDOW_MIN_SIZE (QSize(480,320))
//����ť��С
#define QPUSHBUTTON_LONG_SIZE (QSize(140,28))
//�̰�ť��С
#define QPUSHBUTTON_SHORT_SIZE (QSize(32,28))
//��icon��ť��С
#define QPUSHBUTTON_ICON_PRE_SIZE (QSize(70,28))
//������չ�Լ�������Ӧ
#define QSIZEPOLICY_EXPANDING_ALL (QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding))


//��ͨ��ť��ʽ
#define QPUSHBUTTON_COMMON_BUTTON_STYLE ("QPushButton"\
    "{"\
    "background-color:#f0f0f0;"\
    "border-radius: 3px;"\
    "border-width: 1px ;"\
    "border-color:#a9a9a9;"\
    "border-style: solid;"\
    "}"\
    "QPushButton:hover"\
    "{"\
    "background-color:#e7e7e7;"\
    "}"\
    "QPushButton:pressed"\
    "{"\
    "background-color:#d9d9d9;"\
    "border-style: solid;"\
    "}")

//��ͨС������ʽ
#define QLABEL_LITTLE_TITLE_STYLE ("QLabel"\
    "{"\
    "background-color:#d9d9d9;"\
    "padding-left:5px;"\
    "}")

#define QLABEL_JUST_PADDING_LEFT_5PX  ("QLabel"\
    "{"\
    "padding-left:5px;"\
    "}")

#define QLABEL_JUST_PADDING_RIGHT_5PX ("QLabel"\
    "{"\
    "padding-left:5px"\
    "}")

#define QLABEL_PADDING_LEFT_AND_RIGHT_5PX ("QLabel"\
    "{"\
    "padding-left:5px;"\
    "padding-right:5px;"\
    "}")
//��ֱ������·��
#define QSCROLLBAR_COMMON_STYLE ("QScrollBar:vertical"\
    "{"\
    "width:5px;"\
    "background:rgba(238,238,238,0%);"\
    "margin:0px,0px,0px,0px;"\
    "padding-top:1px;"\
    "padding-bottom:1px;"\
    "}"\
    "QScrollBar::handle:vertical"\
    "{"\
    "width:5px;"\
    "background:rgba(0,0,0,25%);"\
    " border-radius:2px;"\
    "min-height:7;"\
    "}"\
    "QScrollBar::handle:vertical:hover"\
    "{"\
    "width:5px;"\
    "background:rgba(0,0,0,50%);"\
    " border-radius:2px;"\
    "min-height:7;"\
    "}"\
    "QScrollBar::add-line:vertical"\
    "{"\
    "height:0px;width:8px;"\
    "subcontrol-position:bottom;"\
    "}"\
    "QScrollBar::sub-line:vertical"\
    "{"\
    "height:0px;width:8px;"\
    "subcontrol-position:top;"\
    "}"\
    "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"\
    "{"\
    "background:rgba(0,0,0,10%);"\
    "border-radius:4px;"\
    "}")


//��ʷ���ļ��еı���·��
#define DIRPATH_RESOURCE (QDir::currentPath()+QString::fromLocal8Bit("/userSets/loadHistory.txt"))

class Constant
{
public:
    Constant();
    //Ĭ�������ڿ��
    static const int NORMAL_WIDTH=1600;
    //Ĭ�������ڸ߶�
    static const int NORMAL_HEIGHT=880;
    //����ƶ������ڱ�Ե�������϶��任��DRAG_SPACE�����˴��ڵġ���Ե���ж��
    static const int DRAG_SPACE=10;
    //������С�߶�
    static const int TITLE_MIN_HIGHT=26;

    static QFont get12FontSize(){
        QFont font12;
        //��������Ϊ΢���ź�
        font12.setFamily(QString::fromLocal8Bit("Microsoft YaHei UI"));
        font12.setPixelSize(12);
        return font12;
    }

    static QFont get18FontSize(){
        QFont font18;
        //��������Ϊ΢���ź�
        font18.setFamily(QString::fromLocal8Bit("Microsoft YaHei UI"));
        font18.setPixelSize(18);
        return font18;
    }

    static QFont get30FontSize(){
        QFont font30;
        //��������Ϊ΢���ź�
        font30.setFamily(QString::fromLocal8Bit("Microsoft YaHei UI"));
        font30.setPixelSize(30);
        return font30;
    }

    static QPalette getCommanFontColor(){
        QPalette palette;
        palette.setColor(QPalette::WindowText,FONT_COLOR);
        return palette;
    }

    static QPalette getLittleFontColor(){
        QPalette palette;
        palette.setColor(QPalette::WindowText,FONT_LITTLE_COLOR);
        return palette;
    }

    static QPalette getDeepFontColor(){
        QPalette palette;
        palette.setColor(QPalette::WindowText,FONT_DEEP_COLOR);
        return palette;
    }
};

#endif // CONSTANT_H
