#include "myslicerwidget.h"
#include "CoordinateConverter.h"
#include "actormanager.h"
#include "TextAnnotation.h"
#include <sstream>

mySlicerWidget::mySlicerWidget(QWidget *parent): QVTKWidget(parent)
{
    //设置窗口背景为黑色，否则三个窗口背景会透明
    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer2->SetRenderWindow(this->GetRenderWindow());
    imageViewer2->SetupInteractor(this->GetRenderWindow()->GetInteractor());
    imageViewer2->GetRenderer()->ResetCamera();
    imageViewer2->GetRenderer()->SetBackground(0,0,0);
	vtkConnections = vtkSmartPointer<vtkEventQtSlotConnect>::New();
	connect(this, SIGNAL(OnMarkClick(vtkVector3d)), parent, SIGNAL(Mark(vtkVector3d)));
	connect(parent, SIGNAL(Mark(vtkVector3d)), this, SLOT(MarkReact(vtkVector3d)));
    updateRender();
}

/**
 *设置几何位置
*/
void mySlicerWidget::setLocation(int x,int y,int width,int height){
    this->setGeometry(x,y,width,height);
}

/**
 *设置imageViewer2中截图截取位置
*/
void mySlicerWidget::setSlicerValue(int shiftValue){
    imageViewer2->SetSlice(shiftValue);
	int min = imageViewer2->GetSliceMin();
	int max = imageViewer2->GetSliceMax();
	float ratio = (float)(shiftValue - min) / (max - min);
	std::string value;
	std::stringstream ss;
	ss << ratio;
	ss >> value;
	std::cout << "value: " << value << std::endl;
	depth_info->SetInput(((std::string)"Slice Depth: " + value).c_str());
    updateRender();
}

/**
*设置imageViewer2中截图截取位置,根据比例
*/
void mySlicerWidget::setSlicerValueByRatio(double ratio) {
	int min = imageViewer2->GetSliceMin();
	int max = imageViewer2->GetSliceMax();
	int target = (int)ratio * (max - min) + min;
	setSlicerValue(target);
}

/**
 * @brief mySlicerWidget::setSlicerData
 * 设置imageViewer2中截面的数据源
 * @param dicomReader
 * 读取体绘制文件夹的数据源
 * @param o
 * 设置截面截取的坐标平面
 * 坐标平面有XY平面、YZ平面、XZ平面
 */
void mySlicerWidget::setSlicerData(vtkSmartPointer<vtkDICOMImageReader> dicomReader,mySlicerWidget::ORIENTATION o=mySlicerWidget::ORIENTATION::defalut){
    imageViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer2->SetInputConnection(dicomReader->GetOutputPort());
    imageViewer2->SetRenderWindow(this->GetRenderWindow());
    imageViewer2->SetupInteractor(this->GetRenderWindow()->GetInteractor());
	direction_info = Text::CreateAnnotation("Slice Direction:", vtkVector3d(1, 1, 1));
	direction_info->SetPosition(5, 340);
	imageViewer2->GetRenderer()->AddViewProp(direction_info);
	depth_info = Text::CreateAnnotation("Slice Depth:", vtkVector3d(0.3, 0.3, 1));
	depth_info->SetPosition(5, 0);
	imageViewer2->GetRenderer()->AddViewProp(depth_info);
	ListenMarkClick();
    if(o!=0){
        setOrientation(o);
    }

    updateRender();
}

/**
 * 设置截面截取的坐标平面
 */
void mySlicerWidget::setOrientation(mySlicerWidget::ORIENTATION o){
    switch(o){
    case XY:
        imageViewer2->SetSliceOrientationToXY();
		direction_info->SetInput(((std::string)"Slice Direction: " + (std::string)"sagital").c_str());
        break;
    case YZ:
        imageViewer2->SetSliceOrientationToYZ();
		direction_info->SetInput(((std::string)"Slice Direction: " + (std::string)"coronal").c_str());
        break;
    case XZ:
        imageViewer2->SetSliceOrientationToXZ();
		direction_info->SetInput(((std::string)"Slice Direction: " + (std::string)"axial").c_str());
        break;
    }
}

mySlicerWidget::ORIENTATION mySlicerWidget::GetOrientation() const {
	if (imageViewer2 != NULL) {
		int orientation = imageViewer2->GetSliceOrientation();
		switch (orientation)
		{
		case 0:
			return YZ;
		case 1:
			return XZ;
		case 2:
			return XY;
		default:
			return defalut;
			break;
		}
	}
	return defalut;
}

/**
 * 获取截面截取最大值
 */
int mySlicerWidget::getSlicerMax(){
    return imageViewer2->GetSliceMax();
}

/**
 * 获取截面截取最小值
 */
int mySlicerWidget::getSlicerMin(){
    return imageViewer2->GetSliceMin();
}

/**
 * 获取截面截取值
 */
int mySlicerWidget::getSlicer(){
    return imageViewer2->GetSlice();
}

/**
 * 更新此窗口内的Render使窗口重新渲染
 */
void mySlicerWidget::updateRender(){
    imageViewer2->GetRenderWindow()->Render();
}

/**
 * 获取此窗口内的核心控件vtkImageViewer2
 * 慎用
 */
vtkSmartPointer<vtkImageViewer2> mySlicerWidget::getImageViewer2(){
    return imageViewer2;
}

void mySlicerWidget::ListenMarkClick() {
	vtkConnections->Connect(imageViewer2->GetRenderWindow()->GetInteractor(), vtkCommand::RightButtonPressEvent, this, SLOT(Mark(vtkObject*, unsigned long, void*, void*)));
}

void mySlicerWidget::Mark(vtkObject* obj, unsigned long, void*, void*) {
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
	int EventPointX = iren->GetEventPosition()[0];
	int EventPointY = iren->GetEventPosition()[1];
	vtkVector3d modelPosition = CoordinateConverter::EventToModel(imageViewer2, EventPointX, EventPointY);
	emit this->OnMarkClick(modelPosition);
}

void mySlicerWidget::MarkReact(vtkVector3d ModelPosition) {
	setSlicerValue(CoordinateConverter::ModelToSlice(imageViewer2, ModelPosition));
	vtkVector3d worldPostion = CoordinateConverter::ModelToWorld(imageViewer2->GetImageActor(), ModelPosition);
	actorManager* manager = new actorManager;
	auto sphere = manager->getSphereActor(worldPostion[0], worldPostion[1], worldPostion[2]);
	imageViewer2->GetRenderer()->AddActor(sphere);
	updateRender();
}
