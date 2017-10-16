#include "stlmanager.h"

stlManager::stlManager()
{

}

vtkSmartPointer<vtkActor> stlManager::LoadStl(const char *dirPath,QString stlName){
    qDebug()<<"stlManager::LoadStl";
    qDebug()<<"dirPath:"<<dirPath;
    vtkSmartPointer<vtkSTLReader> stlReader=vtkSmartPointer<vtkSTLReader>::New();
    stlReader->SetFileName(dirPath);
    stlReader->Update();//耗时操作
    vtkSmartPointer<vtkTransform> transform= vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter= vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    //   transform->Translate(120,0,0);
    transformFilter->SetTransform(transform);
    transformFilter->SetInputConnection(stlReader->GetOutputPort());
    transformFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(transformFilter->GetOutputPort());
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    transformGroup[stlName]=transform;//加入操作队列中

    return actor;
}

void stlManager::translate(QString stlName,float x,float y,float z){
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->Translate(x,y,z);

}

void stlManager::rotateWXYZ(QString stlName,double w,double x,double y,double z){
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateWXYZ(w,x,y,z);
}

void stlManager::rotateX(QString stlName,double angle){
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateX(angle);
}

void stlManager::rotateY(QString stlName,double angle){
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateY(angle);
}

void stlManager::rotateZ(QString stlName,double angle){
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateZ(angle);
}

void stlManager::scale(QString stlName,double s){
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->Scale(s,s,s);
}
void stlManager::saveLocation(QString stlName){
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    double* position=transform->GetPosition();
    double* orientation=transform->GetOrientationWXYZ();
    double* scale=transform->GetScale();
    qDebug()<<"position[0]: "<<position[0]<<"  |  position[1]: "<<position[1]<<"  | position[2]: "<<position[2];
    qDebug()<<"orientation[0]: "<<orientation[0]<<"  |  orientation[1]: "<<orientation[1]<<"  | orientation[2]: "<<orientation[2];
    qDebug()<<"scale[0]: "<<scale[0]<<"  |  scale[1]: "<<scale[1]<<"  | scale[2]: "<<scale[2];
}
