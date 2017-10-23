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
    vtkSmartPointer<vtkProp3D> prop3d;//������vtkActor����
    vtkSmartPointer<vtkTransform> transform;//���������ת������
    unsigned long long duration=0;//��������ʱ�䣬����Ϊ��λ
    //����Ĭ�϶�����ʼʱ��Ϊ0������ʱ��Ϊclocktime������������ÿˢ��һ֡�������ѽ���ʱ������Ϊ����
    //����������vtk������frameRateΪ5ʱ���������Ϊ0.02�����clocktimeΪ10����ôһ��ˢ�µ�֡��Ϊ50֡��
    //ÿһ֡�ĳ���ʱ�������޷�Ԥ�������Ϊ0.062s����62ms��
    //
    unsigned int stepSize=0.02;
};

#endif // ANIMATOR_H
