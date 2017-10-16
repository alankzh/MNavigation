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
    virtual void TickInternal(double currenttime, double deltatime, double clocktime)
    {
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("ss.zzz ");
        qDebug()<<"time:"<<current_date;
        qDebug()<<"currenttime:"<<currenttime;
        qDebug()<<"deltatime:"<<deltatime;
        qDebug()<<"clocktime:"<<clocktime;
        //  double new_st = currenttime * 180;
        // since the cue is in normalizedmode, the currenttime will be in the
        // range[0,1], where 0 is start ofthe cue and 1 is end of the cue.
        //  this->Sphere->SetStartTheta(new_st);
        transform->Translate(currenttime*5,0,0);
        this->RenWin->Render();
    }
};

#endif // VTKCUSTOMTRANSFORMANIMATIONCUE_H
