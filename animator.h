#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "vtks.h"
/**
 * @brief The Animator class
 * supply base motion for vtkActor
 */
class Animator
{
public:
    Animator();
private:
    void linearMotion(vtkSmartPointer<vtkProp3D> prop3d,double x,double y,double z);
    void scaleMotion(vtkSmartPointer<vtkProp3D> prop3d,double x,double y,double z);
    vtkSmartPointer<vtkProp3D> prop3d;//操作的vtkActor对象
    vtkSmartPointer<vtkTransform> transform;//操作对象的转换管线
    unsigned long long duration=0;//动画持续时间，毫秒为单位
    //我们默认动画开始时间为0，结束时间为clocktime，而步长则是每刷新一帧，动画已进行时间增加为多少
    //当我们设置vtk动画的frameRate为5时，这个步长为0.02，如果clocktime为10，那么一共刷新的帧数为50帧，
    //每一帧的持续时间我们无法预见，大概为0.062s，即62ms。
    //
    unsigned int stepSize=0.02;
};

#endif // ANIMATOR_H
