#include "myvolumewidget.h"

myVolumeWidget::myVolumeWidget(QWidget *parent)
{
    qvtkwidget=new QVTKWidget(parent);
    settingDefault=new RenderSetting();//构造函数初始化
    setLocation(20,55,735,365);//默认的几何位置
}

/**
 * 体绘制，传入的路径为文件夹地址
 */
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
    }

    // Create our volume and mapper
    vtkSmartPointer<vtkVolume> volume =  vtkSmartPointer<vtkVolume>::New();
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

    m_pRenderer=vtkSmartPointer<vtkRenderer>::New();
    qvtkwidget->GetRenderWindow()->AddRenderer(m_pRenderer);
    qvtkwidget->GetRenderWindow()->GetInteractor()->GetInteractorStyle()->SetDefaultRenderer(m_pRenderer);
    // Add the volume to the scene
    m_pRenderer->AddVolume( volume );
    //    ui->volumeSlider->setRange(0,255);
    //    ui->volumeSlider->setValue(120);
    settingDefault->SetRenderType(RenderSetting::RenderType::CT_Bone);//默认的渲染
    m_pRenderer->ResetCamera();
    //   m_pRenderer->GetActiveCamera()->Zoom(1.5);
    m_pRenderer->DrawOn();

    updateRender();

    return true;
}

/**
 * 设置几何位置
*/
void myVolumeWidget::setLocation(int x,int y,int width,int height){
    qvtkwidget->setGeometry(x,y,width,height);
}

/**
 *设置rendersettiing类中的渲染数值
*/
void myVolumeWidget::renderValueChange(double shiftValue){
    settingDefault->ShiftRenderFunction(shiftValue,settingDefault->args->colorFun);
    settingDefault->ShiftRenderFunction(shiftValue,settingDefault->args->opacityFun);
    qvtkwidget->GetRenderWindow()->Render();
}
/**
 * 更新绘制
 * 并且更新交互方式
 */
void myVolumeWidget::updateRender(){
    qvtkwidget->GetRenderWindow()->Render();
    qvtkwidget->GetRenderWindow()->GetInteractor()->Start();
}


/**
 * 获取此窗口内的核心控件QVTKWidget
 * 慎用
 */
QVTKWidget* myVolumeWidget::getQVTKWidget(){
    return qvtkwidget;
}
/**
 * 获取此窗口内的核心控件vtkImageViewer2
 * 慎用
 */
vtkSmartPointer<vtkRenderer> myVolumeWidget::getRenderer(){
    return m_pRenderer;
}
