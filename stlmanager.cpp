#include "stlmanager.h"

/**
 * @brief StlManager::StlManager
 * 体绘制窗口出现的.stl模型的统一管理类
 * TODO 记录模型所做的操作
 * TODO hindden模型
 * TODO 重显示模型
 * TODO 完全删除模型
 */
StlManager::StlManager()
{

}

/**
 * @brief StlManager::LoadStl
 * 加载一个外部.stl模型，并且纳入管理中
 * TODO 目前没有对模型名stlName做重复化提示，应该在模型名重复时返回false，
 * @param dirPath
 * 外部路径
 * @param stlName
 * 模型名，也是模型唯一标识
 * @return
 */
vtkSmartPointer<vtkActor> StlManager::LoadStl(const QString dirPath,QString stlName){
    qDebug()<<"StlManager::LoadStl";
    qDebug()<<"dirPath:"<<dirPath;

    //TODO   目前对加载同一个类型模型做的第一种方式处理，但以后业务逻辑可能会更改
    //两种处理思路  1.不允许加载同一个类型模型第二次
    //2.加载同一个类型模型在stlName后添加标记，以使得标识符不一样
    if(stlActorGroup.contains(stlName)){
        return NULL;
    }
    vtkSmartPointer<vtkSTLReader> stlReader=vtkSmartPointer<vtkSTLReader>::New();
    stlReader->SetFileName(dirPath.toLocal8Bit().data());
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
    transformGroup[stlName]=transform;//加入操作群组中
    stlActorGroup[stlName]=actor;//加入actor群组中
    stlActorNameList.append(stlName);
    return actor;
}

//返回actor群组
QMap<QString,vtkSmartPointer<vtkActor>> StlManager::getActorGroup(){
    return stlActorGroup;
}
//返回actor标识符列表
QList<QString> StlManager::getActorList(){
    return stlActorNameList;
}


/**
 * @brief StlManager::deleteActor
 * 从render中删除标识符为stlName的.stl vtkActor
 * @param stlName
 * @param render
 */
void StlManager::deleteActor(QString stlName,vtkSmartPointer<vtkRenderer> render){
    if(stlActorGroup.contains(stlName)){
        render->RemoveActor(stlActorGroup[stlName]);
        stlActorGroup.remove(stlName);
        transformGroup.remove(stlName);
        stlActorNameList.removeAt(stlActorNameList.indexOf(stlName));
    }
}

/**
 * @brief StlManager::translate
 * 对模型的平移操作
 * @param stlName
 * 模型唯一标识
 * @param x
 * 平移到的x坐标
 * @param y
 * 平移到的y坐标
 * @param z
 * 平移到的z坐标
 */
void StlManager::translate(QString stlName,float x,float y,float z){
    if(!transformGroup.contains(stlName)){
        return;
    }
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->Translate(x,y,z);
}

/**
 * @brief StlManager::rotateWXYZ
 * 将模型绕指定轴旋转一定角度
 * @param stlName
 * 模型唯一标识
 * @param w
 * 旋转角度
 * @param x
 * 旋转轴x
 * @param y
 * 旋转轴y
 * @param z
 * 旋转轴z
 */
void StlManager::rotateWXYZ(QString stlName,double w,double x,double y,double z){
    if(!transformGroup.contains(stlName)){
        return;
    }
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateWXYZ(w,x,y,z);
}

/**
 * @brief StlManager::rotateX
 * 将模型绕x轴旋转一定角度
 * @param stlName
 * 模型唯一标识
 * @param angle
 * 旋转角度
 */
void StlManager::rotateX(QString stlName,double angle){
    if(!transformGroup.contains(stlName)){
        return;
    }
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateX(angle);
}

/**
 * @brief StlManager::rotateY
 * 将模型绕y轴旋转一定角度
 * @param stlName
 * 模型唯一标识
 * @param angle
 * 旋转角度
 */
void StlManager::rotateY(QString stlName,double angle){
    if(!transformGroup.contains(stlName)){
        return;
    }
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateY(angle);
}

/**
 * @brief StlManager::rotateZ
 * 将模型绕z轴旋转一定角度
 * @param stlName
 * 模型唯一标识
 * @param angle
 * 旋转角度
 */
void StlManager::rotateZ(QString stlName,double angle){
    if(!transformGroup.contains(stlName)){
        return;
    }
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->RotateZ(angle);
}

/**
 * @brief StlManager::scale
 * 将模型缩放s倍
 * @param stlName
 * 模型唯一标识
 * @param s
 * 缩放倍数，可以为小数
 */
void StlManager::scale(QString stlName,double s){
    if(!transformGroup.contains(stlName)){
        return;
    }
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    transform->Scale(s,s,s);
}

/**
 * @brief StlManager::saveLocation
 * 设置模型位置
 * TODO 模型进入之后所做的所有矩阵操作应该记录下来，当模型hindden后又重新显示时，
 * 应根据这些记录的矩阵操作还原模型所处的位置
 * @param stlName
 * 模型唯一标识
 */
void StlManager::saveLocation(QString stlName){
    if(!transformGroup.contains(stlName)){
        return;
    }
    vtkSmartPointer<vtkTransform> transform=transformGroup.value(stlName);
    double* position=transform->GetPosition();
    double* orientation=transform->GetOrientationWXYZ();
    double* scale=transform->GetScale();
    qDebug()<<"position[0]: "<<position[0]<<"  |  position[1]: "<<position[1]<<"  | position[2]: "<<position[2];
    qDebug()<<"orientation[0]: "<<orientation[0]<<"  |  orientation[1]: "<<orientation[1]<<"  | orientation[2]: "<<orientation[2];
    qDebug()<<"scale[0]: "<<scale[0]<<"  |  scale[1]: "<<scale[1]<<"  | scale[2]: "<<scale[2];
}

