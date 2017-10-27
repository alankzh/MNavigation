#ifndef ANIMATORSET_H
#define ANIMATORSET_H

#include "animator.h"
#include "motion.h"
#include "vtks.h"
#include "qts.h"
#include "animatorfinisherlistener.h"
#include "myvtkcustomanimationcue.h"

/**
 * @brief The animatorSet class
 * 多个动画联合播放，可设置模式
 */
class AnimatorSet:public AnimatorFinishListener
{
public:
    AnimatorSet();
    ~AnimatorSet();
    void addAnimator(Animator *animator);
    void setDuration(double d);
    void start();
    virtual void onAnimatorFinish();
private:
  //  QList<*Animator> animatorList;
    vtkSmartPointer<vtkAnimationScene> animationScene;
    vtkSmartPointer<MyVtkCustomAnimationCue>  animationCue;
    double duration=0;//毫秒
};

#endif // ANIMATORSET_H
