#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "vtks.h"
#include "animatorfinisherlistener.h"
#include "myvtkcustomanimationcue.h"
#include "motion.h"


/**
 * @brief The Animator class
 * supply base motion for vtkActor
 */
class Animator:public AnimatorFinishListener
{
public:
    Animator(vtkSmartPointer<vtkRenderWindow> r,vtkSmartPointer<vtkActor> actor,Motion::MOTIONS f,double angle,double x,double y,double z);
    Animator(vtkSmartPointer<vtkRenderWindow> r,vtkSmartPointer<vtkActor> actor,Motion::MOTIONS f,double x,double y,double z);
    Animator(vtkSmartPointer<vtkRenderWindow> r,vtkSmartPointer<vtkActor> actor,Motion::MOTIONS f,double angle);
    ~Animator();
    virtual void onAnimatorFinish();
    void setDuration(double  d);
    double getDuration();
    Motion* getMotion();
    vtkSmartPointer<vtkRenderWindow> getRenderWindow();
    void start();
private:
    vtkSmartPointer<vtkRenderWindow> renWin;//渲染窗口
    vtkSmartPointer<vtkActor> actor;//操作的vtkActor对象
    vtkSmartPointer<vtkMatrix4x4> beginMatrix4x4;//操作对象开始时的矩阵
    vtkSmartPointer<vtkMatrix4x4> endMatrix4x4;//操作对象结束时的矩阵
    vtkSmartPointer<vtkAnimationScene> animationScene;
    vtkSmartPointer<MyVtkCustomAnimationCue>  animationCue;
    double  duration=0;//动画持续时间，毫秒为单位
    Motion *motion;
    void outMatrix4x4(vtkSmartPointer<vtkMatrix4x4>);
    void init();
};

#endif // ANIMATOR_H
