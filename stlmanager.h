#ifndef STLMANAGER_H
#define STLMANAGER_H

#include "qts.h"
#include "vtks.h"
#include <Qmap>
#include <qstring.h>

/**
 * @brief The stlManager class
 * 管理导入的stl模型
 * 目前只存在返回actor的方法
 * TODO 需要管理这些加载进来的stl模型
 */
class stlManager
{
     QMap<QString,vtkSmartPointer<vtkTransform>> transformGroup;
public:
    stlManager();

     vtkSmartPointer<vtkActorCollection> StlCollection;
     vtkSmartPointer<vtkActor> LoadStl(const char *dirPath,QString stlName);
     void translate(QString stlName,float x,float y,float z);
     void rotateWXYZ(QString stlName,double w,double x,double y,double z);
     void rotateX(QString stlName,double angle);
     void rotateY(QString stlName,double angle);
     void rotateZ(QString stlName,double angle);
     void scale(QString stlName,double s);
     void saveLocation(QString stlName);
};

#endif // STLMANAGER_H
