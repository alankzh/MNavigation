#ifndef MYVTKCUSTOMANIMATIONCUE_H
#define MYVTKCUSTOMANIMATIONCUE_H

#include "vtks.h"
#include "qts.h"
#include "motion.h"
#include "animatorfinisherlistener.h"

/**
 * @brief The vtkCustomTransformAnimationCue class
 * 自定义动画类
 */
class MyVtkCustomAnimationCue:public vtkAnimationCue
{
public:
    static MyVtkCustomAnimationCue* New(){return new MyVtkCustomAnimationCue;}
    vtkTypeMacro(MyVtkCustomAnimationCue,vtkAnimationCue)
    //  vtkTypeRevisionMacro (vtkCustomTransformAnimationCue,vtkAnimationCue);
    vtkSmartPointer<vtkRenderWindow> RenWin;
    void addMotion(Motion *motion);
    void removeMotion(Motion *motion);
    void setOnAnimationFinishListener(AnimatorFinishListener *listener);
protected:
    MyVtkCustomAnimationCue()
    {
        this->RenWin = 0;
        theta=0;
    }
    ~MyVtkCustomAnimationCue(){
        if(motionList.size()>0){
            for(int i=0,j=motionList.size();i<j;i++){
                delete  motionList.at(i);
            }
            motionList.clear();
        }
    }

    double theta;
    // Overridden to adjust the sphere'sradius depending on the frame we
    // are rendering. In this animation wewant to change the StartTheta
    // of the sphere from 0 to 180 over thelength of the cue.
    virtual void TickInternal(double currenttime, double deltatime, double clocktime);
private:
    QList<Motion *> motionList={};
};

#endif // MYVTKCUSTOMANIMATIONCUE_H
