#ifndef CONSTANT_H
#define CONSTANT_H

// never use it
//#define PROPERTY_PATH (((QDir::currentPath())+("/myPath")))

class Constant
{
public:
    Constant();
    //默认主窗口宽度
    static const int NORMAL_WIDTH=1600;
    //默认主窗口高度
    static const int NORMAL_HEIGHT=880;
    //鼠标移动到窗口边缘，开启拖动变换。DRAG_SPACE定义了窗口的“边缘”有多大
    static const int DRAG_SPACE=10;
};

#endif // CONSTANT_H
