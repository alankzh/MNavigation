#ifndef CONSTANT_H
#define CONSTANT_H

// never use it
//#define PROPERTY_PATH (((QDir::currentPath())+("/myPath")))

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
};

#endif // CONSTANT_H
