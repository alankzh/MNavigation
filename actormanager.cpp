#include "actormanager.h"

/**
 * @brief actorManger::actorManger
 * 管理四个窗口中的绘制actor对象，但是并不包括体绘制窗口中的.stl对象
 * TODO actor的标识符应该包括属于哪个窗口、唯一标识符
 * TODO 对actor有删除操作
 * TODO 对actor的平移、着色工作
 */
actorManager::actorManager()
{

}

/**
 * @brief Widget::getLineActor
 * 返回一个线段actor，通过传递两个3d x、y、z坐标确定位置
 * @param x
 * @param y
 * @param z
 * @param x1
 * @param y1
 * @param z1
 * @return
 */
vtkSmartPointer<vtkActor> actorManager::getLineActor(double x,double y,double z,
                                              double x1,double y1,double z1){
    vtkSmartPointer<vtkLineSource> line=vtkSmartPointer<vtkLineSource>::New();
    line->SetPoint1(x,y,z);
    line->SetPoint2(x1,y1,z1);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(line->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(4);
    actor->GetProperty()->SetColor(1.0,0.0,0.0);

    return actor;
}

/**
 * @brief Widget::getSphereActor
 * 创建一个球体actor，坐标x、y、z用于确立球体位置
 * @param x
 * @param y
 * @param z
 * @return
 */
vtkSmartPointer<vtkActor> actorManager::getSphereActor(double x,double y,double z){
    vtkSmartPointer<vtkSphereSource> sphereSource=vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(x,y,z);   // 设置中心
    sphereSource->SetRadius(10);  // 设置半径
    sphereSource->SetThetaResolution(52);
    sphereSource->SetPhiResolution(52);
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.0,1.0,0.0);

    return actor;
}
