#ifndef StlManager_H
#define StlManager_H

#include "qts.h"
#include "vtks.h"
#include <Qmap>
#include <qstring.h>

/**
 * @brief The StlManager class
 * 管理导入的stl模型
 * 目前只存在返回actor的方法
 * TODO 需要管理这些加载进来的stl模型
 */
class StlManager
{
    QMap<QString,vtkSmartPointer<vtkTransform>> transformGroup;
    QMap<QString,vtkSmartPointer<vtkActor>> stlActorGroup;
    QList<QString> stlActorNameList={};
public:
    StlManager();

    vtkSmartPointer<vtkActorCollection> StlCollection;
    vtkSmartPointer<vtkActor> LoadStl(const QString dirPath,QString stlName);
    void deleteActor(QString stlName,vtkSmartPointer<vtkRenderer> render);
    QMap<QString,vtkSmartPointer<vtkActor>> getActorGroup();
    QList<QString> getActorList();

    void translate(QString stlName,float x,float y,float z);
    void rotateWXYZ(QString stlName,double w,double x,double y,double z);
    void rotateX(QString stlName,double angle);
    void rotateY(QString stlName,double angle);
    void rotateZ(QString stlName,double angle);
    void scale(QString stlName,double s);
    void saveLocation(QString stlName);

};

#endif // StlManager_H
