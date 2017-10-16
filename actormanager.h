#ifndef ACTORMANGER_H
#define ACTORMANGER_H

#include "vtks.h"
#include "qts.h"

class actorManager
{
public:
    actorManager();
    vtkSmartPointer<vtkActor> getLineActor(double x,double y,double z,double x1,double y1,double z1);
    vtkSmartPointer<vtkActor> getSphereActor(double x,double y,double z);
};

#endif // ACTORMANGER_H
