#ifndef VTKCUSTOMTRANSFORMANIMATIONCUE_H
#define VTKCUSTOMTRANSFORMANIMATIONCUE_H

#include "vtks.h"
#include <QtWidgets>

/**
 * @brief The vtkCustomTransformAnimationCue class
 * 自定义动画类
 */
class vtkCustomTransformAnimationCue:public vtkAnimationCue
{
public:
    static vtkCustomTransformAnimationCue* New(){return new vtkCustomTransformAnimationCue;}
    vtkTypeMacro(vtkCustomTransformAnimationCue,vtkAnimationCue)
    //  vtkTypeRevisionMacro (vtkCustomTransformAnimationCue,vtkAnimationCue);
    vtkSmartPointer<vtkRenderWindow> RenWin;
    vtkSmartPointer<vtkSphereSource> Sphere;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkTransform> transform;

protected:
    vtkCustomTransformAnimationCue()
    {
        this->RenWin = 0;
        this->Sphere = 0;
        theta=0;
    }
    ~vtkCustomTransformAnimationCue(){}

    double theta;
    // Overridden to adjust the sphere'sradius depending on the frame we
    // are rendering. In this animation wewant to change the StartTheta
    // of the sphere from 0 to 180 over thelength of the cue.
    virtual void TickInternal(double currenttime, double deltatime, double clocktime);
};

#endif // VTKCUSTOMTRANSFORMANIMATIONCUE_H
