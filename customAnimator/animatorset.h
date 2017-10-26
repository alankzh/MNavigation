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
 * ����������ϲ��ţ�������ģʽ
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
    double duration=0;//����
};

#endif // ANIMATORSET_H
