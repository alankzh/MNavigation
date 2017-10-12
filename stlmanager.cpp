#include "stlmanager.h"

stlManager::stlManager()
{
}

vtkSmartPointer<vtkActor> stlManager::LoadStl(const char *dirPath){
    qDebug()<<"stlManager::LoadStl";
    qDebug()<<"dirPath:"<<dirPath;
    vtkSmartPointer<vtkSTLReader> stlReader=vtkSmartPointer<vtkSTLReader>::New();
    stlReader->SetFileName(dirPath);
    stlReader->Update();//耗时操作
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(stlReader->GetOutputPort());
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
     qDebug()<<"stlManager::LoadStl111111111111111111111111111111";
    return actor;
}
