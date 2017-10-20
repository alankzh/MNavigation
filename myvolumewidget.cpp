#include "myvolumewidget.h"
#include "CoordinateConverter.h"
#include "actormanager.h"

myVolumeWidget::myVolumeWidget(QWidget *parent):QVTKWidget(parent)
{
    settingDefault=new RenderSetting();//构造函数初始化
    setLocation(20,55,735,365);//默认的几何位置
    //设置默认背景为黑色
    m_pRenderer=vtkSmartPointer<vtkRenderer>::New();
    m_pRenderer->SetRenderWindow(this->GetRenderWindow());
    m_pRenderer->ResetCamera();
    m_pRenderer->SetBackground(0,0,0);
	vtkConnections = vtkSmartPointer<vtkEventQtSlotConnect>::New();
	connect(this, SIGNAL(OnMarkClick(vtkVector3d)), parent, SIGNAL(Mark(vtkVector3d)));
	connect(parent, SIGNAL(Mark(vtkVector3d)), this, SLOT(MarkReact(vtkVector3d)));
}

/**
 * 体绘制，传入的路径为文件夹地址
 */
bool myVolumeWidget::setVolumeData(const char *dirPath){
    if(hasVolume){
        dicomReader->Delete();
        volume->Delete();
    }
    vtkAlgorithm *reader=0;
    vtkImageData *input=0;
    //读取.dcm
    dicomReader = vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->SetDirectoryName(dirPath);
    dicomReader->Update();//耗时操作
    input=dicomReader->GetOutput();
    reader=dicomReader;
    // Verify that we actually have a volume
    int dim[3];
    input->GetDimensions(dim);
    if ( dim[0] < 2 ||
         dim[1] < 2 ||
         dim[2] < 2 )
    {
        cout << "Error loading data!" << endl;
        // exit(EXIT_FAILURE);
        return false;
    }else{

    }

    // Create our volume and mapper
    volume =  vtkSmartPointer<vtkVolume>::New();
    vtkSmartPointer<vtkSmartVolumeMapper> mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    mapper->SetInputConnection( reader->GetOutputPort() );
    // Create the property and attach the transfer functions
    settingDefault->args->property->SetIndependentComponents(true);
    settingDefault->args->property->SetColor( settingDefault->args->colorFun );
    settingDefault->args->property->SetScalarOpacity( settingDefault->args->opacityFun );
    settingDefault->args->property->SetInterpolationTypeToLinear();
    // connect up the volume to the property and the mapper
    volume->SetProperty( settingDefault->args->property );
    volume->SetMapper( mapper );
    mapper->SetBlendModeToComposite();

	VolumeBounds = vtkVector<double,6>(volume->GetBounds());

    m_pRenderer=vtkSmartPointer<vtkRenderer>::New();
    this->GetRenderWindow()->AddRenderer(m_pRenderer);
    this->GetRenderWindow()->GetInteractor()->GetInteractorStyle()->SetDefaultRenderer(m_pRenderer);
    // Add the volume to the scene
    m_pRenderer->AddVolume( volume );

	volume->RotateX(30);
    //    ui->volumeSlider->setRange(0,255);
    //    ui->volumeSlider->setValue(120);
    settingDefault->SetRenderType(RenderSetting::RenderType::CT_Bone);//默认的渲染
    m_pRenderer->ResetCamera();
    //   m_pRenderer->GetActiveCamera()->Zoom(1.5);
    m_pRenderer->DrawOn();
    updateRender();

    hasVolume=true;
	ListenMarkClick();

    return true;
}

/**
 * 设置几何位置
*/
void myVolumeWidget::setLocation(int x,int y,int width,int height){
    this->setGeometry(x,y,width,height);
}

/**
 *设置rendersettiing类中的渲染数值
*/
void myVolumeWidget::renderValueChange(double shiftValue){
    settingDefault->ShiftRenderFunction(shiftValue,settingDefault->args->colorFun);
    settingDefault->ShiftRenderFunction(shiftValue,settingDefault->args->opacityFun);
    this->GetRenderWindow()->Render();
}

/**
 * 更新绘制
 */
void myVolumeWidget::updateRender(){
    this->GetRenderWindow()->Render();
 //   qvtkwidget->GetRenderWindow()->GetInteractor()->Start();
}

/**
 * 获取此窗口内的核心控件vtkImageViewer2
 * 慎用
 */
vtkSmartPointer<vtkRenderer> myVolumeWidget::getRenderer(){
    return m_pRenderer;
}

/**
 * @brief myVolumeWidget::getVolume
 * 返回渲染的体绘制数据
 * @return
 */
vtkSmartPointer<vtkVolume> myVolumeWidget::getVolume(){
    if(hasVolume){
         return volume;
    }else{
        //TODO 抛出错误
        return NULL;
    }
}

/**
 * @brief myVolumeWidget::hasVolumeData
 * 是否有体绘制数据
 * @return
 */
bool myVolumeWidget::hasVolumeData(){
    return hasVolume;
}

vtkVector<double, 6> myVolumeWidget::GetVolumeBounds() const{
	return VolumeBounds;
}

void myVolumeWidget::ListenMarkClick() {
	vtkConnections->Connect(m_pRenderer->GetRenderWindow()->GetInteractor(), vtkCommand::LeftButtonPressEvent, this, SLOT(Mark(vtkObject*, unsigned long, void*, void*)));
}

// TO DO: calculate the right point's position in the volume, and emit the signal
void myVolumeWidget::Mark(vtkObject* obj, unsigned long, void*, void*) {
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
	int EventPointX = iren->GetEventPosition()[0];
	int EventPointY = iren->GetEventPosition()[1];
}

void myVolumeWidget::MarkReact(vtkVector3d ModelPosition) {
	vtkVector3d worldPostion = CoordinateConverter::ModelToWorld(volume, ModelPosition);
	actorManager* manager = new actorManager;
	auto sphere = manager->getSphereActor(worldPostion[0], worldPostion[1], worldPostion[2]);
	m_pRenderer->AddActor(sphere);
	updateRender();
}