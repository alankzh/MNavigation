#include "animator.h"


Animator::Animator()
{

}

//prop3d直线移动到世界坐标系(x,y,z)点
void Animator::linearMotion(vtkSmartPointer<vtkProp3D> prop3d,double x, double y, double z){
    prop3d->GetPosition();
    //vtkSmartPointer<vtkTransform> transform=prop3d->Transform;
   // transform->Translate(x,y,z);
}

void Animator::scaleMotion(vtkSmartPointer<vtkProp3D> prop3d,double x,double y,double z){

}
