#include "myvolumewidget.h"
#include "CoordinateConverter.h"
#include "actormanager.h"
#include "vtkVolumePicker.h"
#include "RenderPropertyGenerator.h"
#include "vtkVector.h"
#include "vtkAutoInit.h"
#include "TextAnnotation.h"
#include <sstream>


myVolumeWidget::myVolumeWidget(QWidget *parent):QVTKWidget(parent)
{	
    setLocation(20,55,735,365);//默认的几何位置
    //设置默认背景为黑色
    m_pRenderer=vtkSmartPointer<vtkRenderer>::New();
    m_pRenderer->SetRenderWindow(this->GetRenderWindow());
    m_pRenderer->ResetCamera();
    m_pRenderer->SetBackground(0,0,0);

    vtkConnections = vtkSmartPointer<vtkEventQtSlotConnect>::New();
    connect(this, SIGNAL(OnMarkClick(vtkVector3d)), parent, SIGNAL(Mark(vtkVector3d)));
    connect(parent, SIGNAL(Mark(vtkVector3d)), this, SLOT(MarkReact(vtkVector3d)));
    ListenVTKInteractorEvent();
    hasVolume=false;

    volume_info = Text::CreateAnnotation("Hello", vtkVector3d(1, 1, 1));
    volume_info->SetDisplayPosition(5, 325);

    property_info = Text::CreateAnnotation("property names", vtkVector3d(0, 1, 0));
    property_info->SetDisplayPosition(5, 300);

    mouse_info = Text::CreateAnnotation("mouse", vtkVector3d(1,0,1));
    mouse_info->SetDisplayPosition(5, 0);

    observer=new ProgressObserver(this);
}

bool myVolumeWidget::setVolumeData(const char *dirPath){

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
    volume->SetMapper( mapper );

    mapper->SetBlendModeToComposite();

    VolumeBounds = vtkVector<double,6>(volume->GetBounds());

    this->GetRenderWindow()->RemoveRenderer(m_pRenderer);
    m_pRenderer=vtkSmartPointer<vtkRenderer>::New();

    this->GetRenderWindow()->AddRenderer(m_pRenderer);
    this->GetRenderWindow()->GetInteractor()->GetInteractorStyle()->SetDefaultRenderer(m_pRenderer);
    // Add the volume to the scene
    m_pRenderer->AddVolume( volume );
    m_pRenderer->AddViewProp(volume_info);
    m_pRenderer->AddViewProp(property_info);
    m_pRenderer->AddViewProp(mouse_info);

    std::string input_text = "PatientName: " + (std::string)dicomReader->GetPatientName() + "\n" + "StudyID: " + (std::string)dicomReader->GetStudyUID();
    volume_info->SetInput(input_text.c_str());



    volume->RotateX(30);
    //    ui->volumeSlider->setRange(0,255);
    //    ui->volumeSlider->setValue(120);

    m_pRenderer->ResetCamera();
    //   m_pRenderer->GetActiveCamera()->Zoom(1.5);
    m_pRenderer->DrawOn();

    hasVolume=true;
    SetRenderPropertyType("CT_Bone");
    updateRender();
    return true;
}

void myVolumeWidget::setLocation(int x,int y,int width,int height){
    this->setGeometry(x,y,width,height);
}

void myVolumeWidget::updateRender(){
    this->GetRenderWindow()->Render();
}

vtkSmartPointer<vtkRenderer> myVolumeWidget::getRenderer(){
    return m_pRenderer;
}

vtkSmartPointer<vtkVolume> myVolumeWidget::getVolume(){
    if(hasVolume){
        return volume;
    }else{
        //TODO 抛出错误
        return NULL;
    }
}

bool myVolumeWidget::hasVolumeData(){
    return hasVolume;
}

vtkVector<double, 6> myVolumeWidget::GetVolumeBounds() const{
    return VolumeBounds;
}

void myVolumeWidget::ShiftRenderFunction(double shift) {
    if (hasVolume) {
        RenderPropertyGenerator::ShiftRenderFunction(shift,getVolume()->GetProperty(), property_name_);
        updateRender();
    }
}

void myVolumeWidget::SetRenderPropertyType(std::string property_name) {

    std::cout << "set property type" << std::endl;
    if (hasVolume) {
        RenderPropertyGenerator::ApplyVolumeProperty(property_name, getVolume()->GetProperty());
        SetPropertyName(property_name);
        emit propertyChanged();
        property_info->SetInput(((std::string)("Rendering Property: ") + property_name).c_str());
        updateRender();
    }
}

void myVolumeWidget::SetPropertyName(std::string name) {
    property_name_ = name;
}

void myVolumeWidget::ListenVTKInteractorEvent() {
    vtkConnections->Connect(this->GetRenderWindow()->GetInteractor(), vtkCommand::AnyEvent, this, SLOT(vtkInteractorEventDispatch(vtkObject*, unsigned long, void*, void*)));
}

void myVolumeWidget::Mark(vtkRenderWindowInteractor* iren) {
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    auto picker = vtkSmartPointer<vtkVolumePicker>::New();
    picker->Pick(EventPointX, EventPointY, 0, getRenderer());
    auto target = picker->GetProp3D();
    if (mc.isMarker(target)) {
        mc.RemoveMarker(target);
        getRenderer()->RemoveActor(target);
        target->Delete();
        return;
    }
    picker->SetVolumeOpacityIsovalue(0.5);
    picker->Pick(EventPointX, EventPointY, 0, getRenderer());
    vtkVector3d WorldPosition = vtkVector3d(picker->GetPickPosition());
    vtkVector3d ModelPosition = CoordinateConverter::WorldToModel(volume, WorldPosition);
    emit OnMarkClick(ModelPosition);
}

void myVolumeWidget::SelectMark(vtkRenderWindowInteractor* iren) {
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    auto picker = vtkSmartPointer<vtkVolumePicker>::New();
    picker->Pick(EventPointX, EventPointY, 0, getRenderer());
    mc.SelectMarker(picker->GetProp3D());
}

void myVolumeWidget::MarkReact(vtkVector3d ModelPosition) {
    vtkVector3d worldPostion = CoordinateConverter::ModelToWorld(volume, ModelPosition);
    mc.CreateMarker(getRenderer(), worldPostion);
    updateRender();
}

void myVolumeWidget::DrawLine() {
    mc.CreateLine(getRenderer());
    updateRender();
}

void myVolumeWidget::vtkInteractorEventDispatch(vtkObject* obj, unsigned long eventID, void*, void*) {
    if(!hasVolume){
        emit payBackFocus();
        return;
    }
    auto iren = vtkRenderWindowInteractor::SafeDownCast(obj);
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    switch (eventID)
    {
    case vtkCommand::RightButtonPressEvent:
        if (mc.TestMark(EventPointX,EventPointY,getRenderer())) {
            auto picker = vtkSmartPointer<vtkVolumePicker>::New();
            picker->SetVolumeOpacityIsovalue(0.5);
            picker->Pick(EventPointX, EventPointY, 0, getRenderer());
            vtkVector3d WorldPosition = vtkVector3d(picker->GetPickPosition());
            vtkVector3d ModelPosition = CoordinateConverter::WorldToModel(volume, WorldPosition);
            emit OnMarkClick(ModelPosition);
        }
        break;
    case vtkCommand::LeftButtonPressEvent:
        SelectMark(iren);
        break;
    case vtkCommand::KeyPressEvent:
        if (*(iren->GetKeySym()) = 'B') {
            DrawLine();
        }
        break;
    case vtkCommand::MouseMoveEvent:
    {
        std::string x;
        std::string y;
        std::stringstream ss;
        ss << EventPointX;
        ss >> x;
        ss.clear();
        ss << EventPointY;
        ss >> y;
        std::string input = (std::string)"Horizontal: " + x + "  Vertical: " + y;
        mouse_info->SetInput(input.c_str());
    }

        break;
    default:
        break;
    }
    emit payBackFocus();

}

void myVolumeWidget::TextUIAdapt() {

    int* size = m_pRenderer->GetSize();

    if (size[0] > 1000) {
        volume_info->SetDisplayPosition(5, size[1] - 80);
        property_info->SetDisplayPosition(5, size[1] - 120);
        mouse_info->SetDisplayPosition(5, 0);
    }
    else {
        volume_info->SetDisplayPosition(5, 325);
        property_info->SetDisplayPosition(5, 300);
        mouse_info->SetDisplayPosition(5, 0);
    }
}

/**
 * @brief myVolumeWidget::SetRenderPropertySlot
 * see in SetRenderPropertyType
 * @param property_name
 */
void myVolumeWidget::SetRenderPropertySlot(std::string property_name){
    this->SetRenderPropertyType(property_name);
}


/*start-edit with lvyunxiao-------------------------------------------------------------------------------*/
//这个函数运行在子线程中
void myVolumeWidget::doInThread(){
    qDebug()<<"myVolumeWidget::doInThread";
    qDebug()<<"subThreadID："<<QThread::currentThreadId();
    if(dirPath.isEmpty()){
        emit interrupt();
    }
    if(dicomReader!=NULL){
        qDebug()<<"dicomReader not null";
    //    dicomReader->Delete();
        dicomReader=NULL;
    }else{
        qDebug()<<"dicomReader is NULL";
    }
    dicomReader = vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->AddObserver(vtkCommand::ProgressEvent,observer);
    QByteArray ba=dirPath.toLocal8Bit();
    const char *dirPath_str=ba.data();
    dicomReader->SetDirectoryName(dirPath_str);
    //继承了vtkCommand的进度监听者
    dicomReader->Update();
    emit done();
}
//当子线程结束后会自动调用这里
void myVolumeWidget::onThreadDone(){
    qDebug()<<"myVolumeWidget::onThreadDone";
    qDebug()<<"ThreadID："<<QThread::currentThreadId();
    vtkAlgorithm *reader=0;
    vtkImageData *input=0;
    //change
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
        //TODO 弹出窗提示文件路径不对
        return ;
    }else{

    }
    // Create our volume and mapper


    if(hasVolume){
        qDebug()<<"clear";
        m_pRenderer->RemoveAllViewProps();
        m_pRenderer->RemoveVolume(volume);
    }else{
        this->GetRenderWindow()->RemoveRenderer(m_pRenderer);
        m_pRenderer=vtkSmartPointer<vtkRenderer>::New();
        this->GetRenderWindow()->AddRenderer(m_pRenderer);
        this->GetRenderWindow()->GetInteractor()->GetInteractorStyle()->SetDefaultRenderer(m_pRenderer);
    }
    hasVolume=true;

    volume =  vtkSmartPointer<vtkVolume>::New();
    vtkSmartPointer<vtkSmartVolumeMapper> mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    mapper->SetInputConnection( reader->GetOutputPort() );
    volume->SetMapper( mapper );
    mapper->SetBlendModeToComposite();
    VolumeBounds = vtkVector<double,6>(volume->GetBounds());

    // Add the volume to the scene
    m_pRenderer->AddVolume( volume );
    volume->RotateX(30);

    m_pRenderer->AddViewProp(volume_info);
    m_pRenderer->AddViewProp(property_info);
    m_pRenderer->AddViewProp(mouse_info);

    std::string input_text = "PatientName: " + (std::string)dicomReader->GetPatientName() + "\n" + "StudyID: " + (std::string)dicomReader->GetStudyUID();
    volume_info->SetInput(input_text.c_str());

    //    ui->volumeSlider->setRange(0,255);
    //    ui->volumeSlider->setValue(120);
    m_pRenderer->ResetCamera();
    //   m_pRenderer->GetActiveCamera()->Zoom(1.5);
    m_pRenderer->DrawOn();
    SetRenderPropertyType("CT_Bone");
    updateRender();
}

void myVolumeWidget::setPath(QString str){
    dirPath=str;
}

void myVolumeWidget::emitProgress(int progress){
    emit setProgress(progress);
}

/*end-edit with lvyunxiao-------------------------------------------------------------------------------------------*/
