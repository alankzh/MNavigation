#ifndef STLMANAGER_H
#define STLMANAGER_H

#include "qts.h"
#include "vtks.h"

/**
 * @brief The stlManager class
 * 管理导入的stl模型
 * 目前只存在返回actor的方法
 * TODO 需要管理这些加载进来的stl模型
 */
class stlManager
{
public:
    stlManager();

    static vtkSmartPointer<vtkActorCollection> StlCollection;
    static vtkSmartPointer<vtkActor> LoadStl(const char *dirPath);

};

#endif // STLMANAGER_H
