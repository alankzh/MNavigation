#ifndef MOTION_H
#define MOTION_H

#include "vtks.h"
#include "animatorfinisherlistener.h"
#include "qts.h"

class Motion
{
public:
    enum MOTIONS{
        translate,
        scale,
        rotate,
        rotateX,
        rotateY,
        rotateZ
    };

    Motion(vtkSmartPointer<vtkActor> actor,MOTIONS flag);
    ~Motion();

    void setOnAnimationFinishListener(AnimatorFinishListener *listener);
    void onAnimationUpdate(double currenttime,double deltatime,double clocktime);
    void setEndAngle(double a);
    void setRotationAxis(double x,double y,double z);
    void setEndPosition(double x,double y,double z);
private:
    void linearMotion(double x, double y, double z);
    void scaleMotion(double x,double y,double z);
    void rotateMotion(double angle,double x,double y,double z);
    void rotateXMotion(double angle);
    void rotateYMotion(double angle);
    void rotateZMotion(double angle);
    void onTranformArithmetic();
    AnimatorFinishListener *listener;
    vtkSmartPointer<vtkActor> actor;
    double beginPosition[3]={};
    double beginScale[3]={};
    double lastA=0;
    double angle;//����Ҫ��ת���ĽǶ�
    double x;//����Ҫ�ƶ�����λ��
    double y;//����Ҫ�ƶ�����λ��
    double z;//����Ҫ�ƶ�����λ��
    double axis[3]={};//��ת��
    Motion::MOTIONS flag;
};

#endif // MOTION_H
