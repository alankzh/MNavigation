#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QCoreApplication>
#include <vtkCamera.h>


/**
 * @brief Widget::Widget
 * 历史遗留的主窗口，留着测试一些小功能。
 */

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //TODO 固定了大小，需要以后自适应
    this->setMaximumSize(1600,880);
    this->setMinimumSize(1600,880);

    qDebug()<<"main";
    init();
    style();

    //  onOpenVolumeDir();//软件开始直接打开文件夹
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init(){
    qDebug()<<"init";
    m_pImageViewer=vtkSmartPointer<vtkImageViewer2>::New();
    m_pRenderer=vtkSmartPointer<vtkRenderer>::New();
    volumeWidget=ui->volumeWidget;
    sagitalWidget=ui->sagitalWidget;
    coronalWidget=ui->coronalWidget;
    axialWidget=ui->axialWidget;
    m_sagitalViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    m_coronalViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    m_axialViewer2=vtkSmartPointer<vtkImageViewer2>::New();
    m_vtkQtConnect=vtkSmartPointer<vtkEventQtSlotConnect>::New();

    settingDefault=new RenderSetting();//构造函数初始化
    lastposition=120;
    isOpenDir=false;
    canPaintSphere=false;

    stlM=new StlManager();

    qDebug()<<"current applicationDirPath: "<<QCoreApplication::applicationDirPath();
    qDebug()<<"current currentPath: "<<QDir::currentPath();
    //   ui->sagitalLabel->setText("applicationDirPath:"+QCoreApplication::applicationDirPath());
    //   ui->axialLabel->setText(" currentPath:"+QDir::currentPath());

}

void Widget::style(){
    qDebug()<<"style";
    ui->greenButton1->setStyleSheet("border: 5px");

    //163,163为原始分辨率，这里稍做了调整。
    QPixmap pixmap(":/resources/navigation.png", "png");
    int sizeW=ui->navigationButton->geometry().width();
    int sizeH=ui->navigationButton->geometry().height();
    QPixmap fitpixmap=pixmap.scaled(120,65).scaled(sizeW,sizeH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->navigationButton->setIcon(QIcon(fitpixmap));
    ui->navigationButton->setIconSize(QSize(sizeW,sizeH));
    ui->navigationButton->setFlat(true);//就是这句能够实现按钮透明，用png图片时很有用
    ui->navigationButton->setStyleSheet("border: 0px");//消除边框，取消点击效果
    ui->navigationButton->setFlat(1);

    QPixmap pixmap2(":/resources/greenButton.png", "png");
    sizeW=ui->greenButton1->geometry().width();
    sizeH=ui->greenButton1->geometry().height();
    QPixmap fitpixmap2=pixmap2.scaled(69,62).scaled(sizeW,sizeH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->greenButton1->setIcon(QIcon(fitpixmap2));
    ui->greenButton1->setIconSize(QSize(sizeW,sizeH));
    ui->greenButton1->setFlat(true);//就是这句能够实现按钮透明，用png图片时很有用
    ui->greenButton1->setStyleSheet("border: 0px");//消除边框，取消点击效果
    ui->greenButton1->setFlat(1);

    ui->greenButton2->setIcon(QIcon(fitpixmap2));
    ui->greenButton2->setIconSize(QSize(sizeW,sizeH));
    ui->greenButton2->setFlat(true);//就是这句能够实现按钮透明，用png图片时很有用
    ui->greenButton2->setStyleSheet("border: 0px");//消除边框，取消点击效果
    ui->greenButton2->setFlat(1);

    QPixmap pixmap3(":/resources/mainPower.png", "png");
    sizeW=ui->exitButton->geometry().width();
    sizeH=ui->exitButton->geometry().height();
    QPixmap fitpixmap3=pixmap3.scaled(69,62).scaled(sizeW,sizeH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->exitButton->setIcon(QIcon(fitpixmap3));
    ui->exitButton->setIconSize(QSize(sizeW,sizeH));
    ui->exitButton->setFlat(true);//就是这句能够实现按钮透明，用png图片时很有用
    ui->exitButton->setStyleSheet("border: 0px");//消除边框，取消点击效果
    ui->exitButton->setFlat(1);

    QPixmap pixmap4(":/resources/mainTranslation.png", "png");
    sizeW=ui->translateButton->geometry().width();
    sizeH=ui->translateButton->geometry().height();
    QPixmap fitpixmap4=pixmap4.scaled(69,62).scaled(sizeW,sizeH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->translateButton->setIcon(QIcon(fitpixmap4));
    ui->translateButton->setIconSize(QSize(sizeW,sizeH));
    ui->translateButton->setFlat(true);//就是这句能够实现按钮透明，用png图片时很有用
    ui->translateButton->setStyleSheet("border: 0px");//消除边框，取消点击效果
    ui->translateButton->setFlat(1);

    QPixmap pixmap5(":/resources/mainMagnify.png", "png");
    sizeW=ui->magnifyButton->geometry().width();
    sizeH=ui->magnifyButton->geometry().height();
    QPixmap fitpixmap5=pixmap5.scaled(69,62).scaled(sizeW,sizeH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->magnifyButton->setIcon(QIcon(fitpixmap5));
    ui->magnifyButton->setIconSize(QSize(sizeW,sizeH));
    ui->magnifyButton->setFlat(true);//就是这句能够实现按钮透明，用png图片时很有用
    ui->magnifyButton->setStyleSheet("border: 0px");//消除边框，取消点击效果
    ui->magnifyButton->setFlat(1);

    QPixmap pixmap6(":/resources/mainShrink.png", "png");
    sizeW=ui->shrinkButton->geometry().width();
    sizeH=ui->shrinkButton->geometry().height();
    QPixmap fitpixmap6=pixmap6.scaled(69,62).scaled(sizeW,sizeH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->shrinkButton->setIcon(QIcon(fitpixmap6));
    ui->shrinkButton->setIconSize(QSize(sizeW,sizeH));
    ui->shrinkButton->setFlat(true);//就是这句能够实现按钮透明，用png图片时很有用
    ui->shrinkButton->setStyleSheet("border: 0px");//消除边框，取消点击效果
    ui->shrinkButton->setFlat(1);

    ui->axialSliderNum->setText("0");
    ui->sagitalSliderNum->setText("0");
    ui->coronalSliderNum->setText("0");
}

void Widget::onOpenVolumeDir(){
    if(isOpenDir){
        init();
    }
    qDebug()<<"onOpenVolumeDir";
    //TODO
    // QString dirPath=QFileDialog::getExistingDirectory(this,tr("打开体绘制数据存储文件夹"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString dirPath="E:/vtkDataSource/Demo Data Spine/dicom";
    qDebug()<<dirPath;
    if(dirPath.isEmpty()==true) {
        qDebug()<<"exit";
        //        QApplication::exit();
        return;
    }else{
        isOpenDir=true;
    }
    //支持带中文路径的读取
    QByteArray ba=dirPath.toLocal8Bit();
    const char *dirPath_str=ba.data();
    // Read the data
    vtkAlgorithm *reader=0;
    vtkImageData *input=0;
    //读取.dcm
    vtkSmartPointer<vtkDICOMImageReader> dicomReader = vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->SetDirectoryName(dirPath_str);
    dicomReader->Update();
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
        return;
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

    volumeWidget->GetRenderWindow()->AddRenderer(m_pRenderer);
    volumeWidget->GetRenderWindow()->GetInteractor()->GetInteractorStyle()->SetDefaultRenderer(m_pRenderer);
    // Add the volume to the scene
    m_pRenderer->AddVolume( volume );
    m_pRenderer->ResetCamera();
    ui->volumeSlider->setRange(0,255);
    ui->volumeSlider->setValue(120);
    settingDefault->SetRenderType(RenderSetting::RenderType::CT_AAA);//默认的渲染
    //    ui->volumeSlider->setValue(0);
    m_sagitalViewer2->SetInputConnection(dicomReader->GetOutputPort());
    m_sagitalViewer2->SetRenderWindow(sagitalWidget->GetRenderWindow());
    m_sagitalViewer2->SetSliceOrientationToXY();
    ui->sagitalSlider->setRange(m_sagitalViewer2->GetSliceMin(),m_sagitalViewer2->GetSliceMax());
    m_sagitalViewer2->SetSlice(100);//TODO 滑动条
    ui->sagitalSlider->setValue(100);
    //  m_sagitalViewer2->GetImageActor()->InterpolateOff();
    m_sagitalViewer2->SetupInteractor(sagitalWidget->GetRenderWindow()->GetInteractor());
    m_sagitalViewer2->GetRenderer()->ResetCamera();//镜头拉近

    m_coronalViewer2->SetInputConnection(dicomReader->GetOutputPort());
    m_coronalViewer2->SetRenderWindow(coronalWidget->GetRenderWindow());
    m_coronalViewer2->SetSliceOrientationToYZ();
    ui->coronalSlider->setRange(m_coronalViewer2->GetSliceMin(),m_coronalViewer2->GetSliceMax());
    m_coronalViewer2->SetSlice(140);
    ui->coronalSlider->setValue(140);
    //  m_coronalViewer2->GetImageActor()->InterpolateOff();
    m_coronalViewer2->SetupInteractor(coronalWidget->GetRenderWindow()->GetInteractor());
    m_coronalViewer2->GetRenderer()->ResetCamera();//镜头拉近

    m_axialViewer2->SetInputConnection(dicomReader->GetOutputPort());
    m_axialViewer2->SetRenderWindow(axialWidget->GetRenderWindow());
    m_axialViewer2->SetSliceOrientationToXZ();
    ui->axialSlider->setRange(m_axialViewer2->GetSliceMin(),m_axialViewer2->GetSliceMax());
    m_axialViewer2->SetSlice(140);
    ui->axialSlider->setValue(140);
    //  m_axialViewer2->GetImageActor()->InterpolateOff();
    m_axialViewer2->SetupInteractor(axialWidget->GetRenderWindow()->GetInteractor());
    m_axialViewer2->GetRenderer()->ResetCamera();//镜头拉近

    /*
    double c_x=175,c_y=135,c_z=120;

    vtkSmartPointer<vtkActor> actor0=getSphereActor(1.0*c_x,0.0*c_y,0.0*c_z);
    actor0->GetProperty()->SetColor(1,0,0);//x轴红色

     vtkSmartPointer<vtkActor> actor00=getSphereActor(0.0*c_x,0.0*c_y,0.0*c_z);
     actor00->GetProperty()->SetColor(0.32,0,0.68);//紫色
    m_pRenderer->AddActor(actor00);//画了一个球

    vtkSmartPointer<vtkActor> actor2=getSphereActor(0.0*c_x,1.0*c_y,0.0*c_z);
    actor2->GetProperty()->SetColor(0,0,1);//y轴蓝色
    vtkSmartPointer<vtkActor> actor3=getSphereActor(0.0*c_x,0.0*c_y,1.0*c_z);
    actor3->GetProperty()->SetColor(0.68,0.62,0.193);//z轴屎黄色
    m_pRenderer->AddActor(actor2);//画了一个球
    m_pRenderer->AddActor(actor3);//画了一个球
    m_pRenderer->AddActor(getSphereActor(1.0*c_x,1.0*c_y,0.0*c_z));//画了一个球
    m_pRenderer->AddActor(getSphereActor(0.0*c_x,1.0*c_y,1.0*c_z));//画了一个球
    m_pRenderer->AddActor(getSphereActor(1.0*c_x,0.0*c_y,1.0*c_z));//画了一个球
    m_pRenderer->AddActor(getSphereActor(1.0*c_x,1.0*c_y,1.0*c_z));//画了一个球
    m_pRenderer->AddActor(actor0);//画了一个球

   */
    //   m_pRenderer->Delete();
    m_pRenderer->ResetCamera();
    //   m_pRenderer->GetActiveCamera()->Zoom(1.5);
    m_pRenderer->DrawOn();
    // interact with data
    m_sagitalViewer2->GetRenderWindow()->Render();
    m_coronalViewer2->GetRenderWindow()->Render();
    m_axialViewer2->GetRenderWindow()->Render();
    volumeWidget->GetRenderWindow()->Render();
    volumeWidget->GetRenderWindow()->GetInteractor()->Start();
    setConnect();


    //得到边界与三个截面Slice的比例关系
    double *boundary=m_sagitalViewer2->GetImageActor()->GetBounds();
    boundary[1]=m_sagitalViewer2->GetImageActor()->GetBounds()[1];
    boundary[3]=m_sagitalViewer2->GetImageActor()->GetBounds()[3];
    boundary[5]=m_coronalViewer2->GetImageActor()->GetBounds()[5];

    qDebug()<<"boundarx:"<<boundary[1];
    qDebug()<<"boundary:"<<boundary[3];
    qDebug()<<"boundarz:"<<boundary[5];
    qDebug()<<"sagitalSlicerMAX:"<<m_sagitalViewer2->GetSliceMax();
    qDebug()<<"axialSlicerMax:"<<m_axialViewer2->GetSliceMax();
    qDebug()<<"coronalSlicerMax:"<<m_coronalViewer2->GetSliceMax();

    proportionZ=boundary[5]/m_sagitalViewer2->GetSliceMax();
    qDebug()<<"proportionZ"<<proportionZ;
    proportionY=boundary[3]/m_axialViewer2->GetSliceMax();
    qDebug()<<"proportionY"<<proportionY;
    proportionX=boundary[1]/m_coronalViewer2->GetSliceMax();
    qDebug()<<"proportionX"<<proportionX;

}

void Widget::setConnect(){
    //体绘制窗口的点击事件
    qDebug()<<"setConnect";
    //  m_vtkQtConnect->Connect(axialWidget->GetRenderWindow()->GetInteractor(),vtkCommand::MouseMoveEvent||vtkCommand::LeftButtonPressEvent,this,SLOT(mouseClick(vtkObject*, unsigned long, void*, void*)));
    //目前只链接了sagitalWidget
    m_vtkQtConnect->Connect(volumeWidget->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(mouseClick(vtkObject*, unsigned long, void*, void*)));
    m_vtkQtConnect->Connect(sagitalWidget->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(sagitalClicked(vtkObject*, unsigned long, void*, void*)));
    m_vtkQtConnect->Connect(axialWidget->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(axialClicked(vtkObject*, unsigned long, void*, void*)));
    m_vtkQtConnect->Connect(coronalWidget->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(coronalClicked(vtkObject*, unsigned long, void*, void*)));
    qDebug()<<"setConnectEnd";
}

void Widget::sagitalClicked(vtkObject *obj, unsigned long, void*, void*){
    qDebug()<<"Widget::sagitalClicked";

    vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    // SliceData* data = (SliceData*)ClientData;
    vtkImageActor* Actor = m_sagitalViewer2->GetImageActor();
    vtkRenderer* Renderer= m_sagitalViewer2->GetRenderer();

    double* boundary;
    boundary = Actor->GetBounds();

    int* Size = Renderer->GetSize();
    double ViewEventPointX = (double)EventPointX * 2 / Size[0] - 1;
    double ViewEventPointY = (double)EventPointY * 2 / Size[1] - 1;
    double x = boundary[1];//长
    double y = boundary[3];//宽
    double z = boundary[5];//高
    vtkVector3d origin = vtkVector3d(0, 0, z);
    vtkVector3d xEnd = vtkVector3d(x, 0, z);
    vtkVector3d yEnd = vtkVector3d(0, y, z);

    vtkVector3d originView = origin;
    Renderer->WorldToView(originView[0],originView[1],originView[2]);
    vtkVector3d xView=xEnd;
    Renderer->WorldToView(xView[0], xView[1], xView[2]);
    vtkVector3d yView=yEnd;
    Renderer->WorldToView(yView[0],yView[1],yView[2]);

    qDebug()<<"xView[0] :"<<xView[0] ;
    qDebug()<<"originView[0] :"<<originView[0] ;
    qDebug()<<"xView[0] :"<<xView[0] ;
    qDebug()<<"originView[1]:"<<originView[1];

    double xRatio = (ViewEventPointX - originView[0]) / (xView[0] - originView[0]);
    double yRatio = (ViewEventPointY - originView[1]) / (yView[1] - originView[1]);

    vtkVector3d targetPosition = vtkVector3d();
    targetPosition[0] = xRatio * (xEnd[0] - origin[0]) + origin[0];
    targetPosition[1] = yRatio * (yEnd[1] - origin[1]) + origin[1];
    targetPosition[2] = origin[2];
    vtkMatrix4x4* matrix = volume->GetMatrix();
    vtkVector3d adjust = vtkVector3d(matrix->MultiplyDoublePoint(targetPosition.GetData()));

    qDebug()<<"EventPointX:"<<EventPointX;
    qDebug()<<"EventPointY:"<<EventPointY;
    if(adjust[0]>0&&adjust[1]>0){
        if(canTarger){
            m_pRenderer->AddActor(getSphereActor(adjust[0],adjust[1],adjust[2]));

            m_sagitalViewer2->GetRenderer()->AddActor(getLineActorXY(adjust[0]+1,adjust[1],adjust[0]+10,adjust[1]));
            m_sagitalViewer2->GetRenderer()->AddActor(getLineActorXY(adjust[0],adjust[1]+1,adjust[0],adjust[1]+10));
            m_sagitalViewer2->GetRenderer()->AddActor(getLineActorXY(adjust[0]-1,adjust[1],adjust[0]-10,adjust[1]));
            m_sagitalViewer2->GetRenderer()->AddActor(getLineActorXY(adjust[0],adjust[1]-1,adjust[0],adjust[1]-10));

            m_axialViewer2->GetRenderer()->AddActor(getLineActorXZ(adjust[0]+1,adjust[2],adjust[0]+10,adjust[2]));
            m_axialViewer2->GetRenderer()->AddActor(getLineActorXZ(adjust[0],adjust[2]+1,adjust[0],adjust[2]+10));
            m_axialViewer2->GetRenderer()->AddActor(getLineActorXZ(adjust[0]-1,adjust[2],adjust[0]-10,adjust[2]));
            m_axialViewer2->GetRenderer()->AddActor(getLineActorXZ(adjust[0],adjust[2]-1,adjust[0],adjust[2]-10));

            m_coronalViewer2->GetRenderer()->AddActor(getLineActorYZ(adjust[1]+1,adjust[2],adjust[1]+10,adjust[2]));
            m_coronalViewer2->GetRenderer()->AddActor(getLineActorYZ(adjust[1],adjust[2]+1,adjust[1],adjust[2]+10));
            m_coronalViewer2->GetRenderer()->AddActor(getLineActorYZ(adjust[1]-1,adjust[2],adjust[1]-10,adjust[2]));
            m_coronalViewer2->GetRenderer()->AddActor(getLineActorYZ(adjust[1],adjust[2]-1,adjust[1],adjust[2]-10));

            ui->sagitalSlider->setValue(ui->sagitalSlider->value()+1);
            ui->sagitalSlider->setValue(ui->sagitalSlider->value()-1);

            ui->axialSlider->setValue(ui->axialSlider->value()+1);
            ui->axialSlider->setValue(ui->axialSlider->value()-1);

            ui->coronalSlider->setValue(ui->coronalSlider->value()+1);
            ui->coronalSlider->setValue(ui->coronalSlider->value()-1);
        }else{

        }
        m_sagitalViewer2->GetRenderWindow()->Render();
        //   m_sagitalViewer2->GetRenderer()->Render();
        //    m_axialViewer2->GetRenderer()->AddActor(getSphereActor(targetPosition[0],targetPosition[2],0));
        //    m_coronalViewer2->GetRenderer()->AddActor(getSphereActor(targetPosition[1],targetPosition[2],0));

        volumeWidget->GetRenderWindow()->Render();
        ui->axialSlider->setValue((int) adjust[0]/proportionX);
        ui->coronalSlider->setValue((int) adjust[1]/proportionY);
        ui->sagitalLabel->setText("x:"+(QString::number(adjust[0],10,6))+"y:"+(QString::number(adjust[1],10,6))+"z:"+(QString::number(adjust[2],10,6)));
        update();
    }else{
        return;
    }
}
void Widget::axialClicked(vtkObject *obj, unsigned long, void*, void*){
    qDebug()<<"Widget::sagitalClicked";
    vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    // SliceData* data = (SliceData*)ClientData;
    vtkImageActor* Actor = m_axialViewer2->GetImageActor();
    vtkRenderer* Renderer= m_axialViewer2->GetRenderer();

    double* boundary;
    boundary = Actor->GetBounds();

    int* Size = Renderer->GetSize();
    double ViewEventPointX = (double)EventPointX * 2 / Size[0] - 1;
    double ViewEventPointY = (double)EventPointY * 2 / Size[1] - 1;
    double x = boundary[1];//长
    double y = boundary[3];//宽
    double z = boundary[5];//高

    //  vtkVector3d origin = vtkVector3d(0, 0, z);
    //   vtkVector3d xEnd = vtkVector3d(x, 0, z);
    //  vtkVector3d yEnd = vtkVector3d(0, y, z);
    vtkVector3d origin = vtkVector3d(0, y, 0);
    vtkVector3d xEnd = vtkVector3d(x, y, 0);
    vtkVector3d zEnd = vtkVector3d(0, y, z);

    vtkVector3d originView = origin;
    Renderer->WorldToView(originView[0],originView[1],originView[2]);
    vtkVector3d xView=xEnd;
    Renderer->WorldToView(xView[0], xView[1], xView[2]);
    vtkVector3d zView=zEnd;
    Renderer->WorldToView(zView[0],zView[1],zView[2]);

    double xRatio = (ViewEventPointX - originView[0]) / (xView[0] - originView[0]);
    double zRatio = (ViewEventPointY - originView[1]) / (zView[1] - originView[1]);

    vtkVector3d targetPosition = vtkVector3d();

    targetPosition[0] = xRatio * (xEnd[0] - origin[0]) + origin[0];
    targetPosition[1] = origin[1];
    targetPosition[2] = zRatio * (zEnd[2] - origin[2]) + origin[2];

    vtkMatrix4x4* matrix = volume->GetMatrix();
    vtkVector3d adjust = vtkVector3d(matrix->MultiplyDoublePoint(targetPosition.GetData()));

    if(adjust[0]>0&&adjust[2]>0){
        //   m_pRenderer->AddActor(getSphereActor(adjust[0],adjust[1],adjust[2]));


        ui->axialSlider->setValue(ui->axialSlider->value()+1);
        ui->axialSlider->setValue(ui->axialSlider->value()-1);

        volumeWidget->GetRenderWindow()->Render();
        ui->coronalSlider->setValue((int) adjust[0]/proportionX);
        ui->sagitalSlider->setValue((int) adjust[2]/proportionZ);
        ui->axialLabel->setText("x:"+(QString::number(adjust[0],10,6))+"y:"+(QString::number(adjust[1],10,6))+"z:"+(QString::number(adjust[2],10,6)));
        update();
    }
}
void Widget::coronalClicked(vtkObject *obj, unsigned long, void*, void*){
    qDebug()<<"Widget::coronalClicked";

    vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    vtkImageActor* Actor = m_coronalViewer2->GetImageActor();
    vtkRenderer* Renderer= m_coronalViewer2->GetRenderer();

    double* boundary;
    boundary = Actor->GetBounds();

    int* Size = Renderer->GetSize();
    double ViewEventPointX = (double)EventPointX * 2 / Size[0] - 1;
    double ViewEventPointY = (double)EventPointY * 2 / Size[1] - 1;
    double x = boundary[1];//长
    double y = boundary[3];//宽
    double z = boundary[5];//高

    vtkVector3d origin = vtkVector3d(x, 0, 0);
    vtkVector3d xEnd = vtkVector3d(x, y, 0);
    vtkVector3d yEnd = vtkVector3d(x, 0, z);

    vtkVector3d originView = origin;
    Renderer->WorldToView(originView[0],originView[1],originView[2]);
    vtkVector3d xView=xEnd;
    Renderer->WorldToView(xView[0], xView[1], xView[2]);
    vtkVector3d yView=yEnd;
    Renderer->WorldToView(yView[0],yView[1],yView[2]);
    double xRatio = (ViewEventPointX - originView[0]) / (xView[0] - originView[0]);
    double yRatio = (ViewEventPointY - originView[1]) / (yView[1] - originView[1]);

    vtkVector3d targetPosition = vtkVector3d();

    targetPosition[0] = origin[0];
    targetPosition[1] = xRatio * (xEnd[1] - origin[1]) + origin[1];
    targetPosition[2] = yRatio * (yEnd[2] - origin[2]) + origin[2];

    vtkMatrix4x4* matrix = volume->GetMatrix();
    vtkVector3d adjust = vtkVector3d(matrix->MultiplyDoublePoint(targetPosition.GetData()));

    if(adjust[1]>0&&adjust[2]>0){
        //    m_pRenderer->AddActor(getSphereActor(adjust[0],adjust[1],adjust[2]));



        ui->coronalSlider->setValue(ui->coronalSlider->value()+1);
        ui->coronalSlider->setValue(ui->coronalSlider->value()-1);

        volumeWidget->GetRenderWindow()->Render();
        ui->axialSlider->setValue((int) adjust[1]/proportionY);
        ui->sagitalSlider->setValue((int) adjust[2]/proportionZ);
        ui->coronalLabel->setText("x:"+(QString::number(adjust[0],10,6))+"y:"+(QString::number(adjust[1],10,6))+"z:"+(QString::number(adjust[2],10,6)));
        update();
    }
}
void Widget::mouseClick(vtkObject *obj, unsigned long, void*, void*){
    qDebug()<<"Widget::mouseClick";

    /*
    if(canPaintSphere){
        //获取交互器
        vtkRenderWindowInteractor *iren=vtkRenderWindowInteractor::SafeDownCast(obj);
        //获取鼠标的当前位置
        int eventPos[2];
        iren->GetEventPosition(eventPos);
        int x=eventPos[0];
        int y=eventPos[1];
        this->setWindowTitle(QString("x:%1 y:%2").arg(eventPos[0]).arg(eventPos[1]));
        if((x<224)||(x>510))
            return;
        if((y>310)||(y<31))
            return;

        double xx=(510.0-x)*175/286+10;
        double yy=(y-31)*135/235+5;

        qDebug()<<"xy截面切片最大:"<<(m_sagitalViewer2->GetSliceMax());
        qDebug()<<"xy截面切片最小:"<<(m_sagitalViewer2->GetSliceMin());
        qDebug()<<"当前截面:"<<m_sagitalViewer2->GetSlice();
        m_pRenderer->AddActor(getSphereActor(xx,yy,m_sagitalViewer2->GetSlice()*0.4));
        m_pRenderer->DrawOn();
        m_pRenderer->GetRenderWindow()->Render();
        this->update();
        //  canPaintSphere=false;
    }else{
    }
    */
}

void Widget::paintEvent(QPaintEvent *event){
}

void Widget::keyPressEvent(QKeyEvent *event){
    Q_UNUSED(event);
    // qDebug()<<"keyPressEvent:"<<event->key();
    if(event->key()==Qt::Key_0){
        settingDefault->SetRenderType(RenderSetting::RenderType::CT_Normal);
        this->setWindowTitle("CT_Normal");
        lastposition=120;
        ui->volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_1){
        settingDefault->SetRenderType(RenderSetting::RenderType::CT_Bone);
        this->setWindowTitle("CT_Bone");
        lastposition=120;
        ui->volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_2){
        settingDefault->SetRenderType(RenderSetting::RenderType::CT_AAA);
        this->setWindowTitle("CT_AAA");
        lastposition=120;
        ui->volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_3){
        settingDefault->SetRenderType(RenderSetting::RenderType::CT_Liver_Vasculature);
        this->setWindowTitle("CT_Liver_Vasculature");
        lastposition=120;
        ui->volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_4){
        settingDefault->SetRenderType(RenderSetting::RenderType::CT_Lung);
        this->setWindowTitle("CT_Lung");
        lastposition=120;
        ui->volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_5){
        settingDefault->SetRenderType(RenderSetting::RenderType::MR_Default);
        this->setWindowTitle("MR_Default");
        lastposition=120;
        ui->volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_6){
        settingDefault->SetRenderType(RenderSetting::RenderType::MR_Brain);
        this->setWindowTitle("MR_Brain");
        lastposition=120;
        ui->volumeSlider->setValue(120);
    }
    /*变换操作开始*/
    if(event->key()==Qt::Key_Q){
        stlM->translate(operationStlName,10,0,0);
    }
    if(event->key()==Qt::Key_W){
        stlM->translate(operationStlName,0,10,0);
    }
    if(event->key()==Qt::Key_E){
        stlM->translate(operationStlName,0,0,10);
    }
    if(event->key()==Qt::Key_A){
        stlM->translate(operationStlName,-10,0,0);
    }
    if(event->key()==Qt::Key_S){
        stlM->translate(operationStlName,0,-10,0);
    }
    if(event->key()==Qt::Key_D){
        stlM->translate(operationStlName,0,0,-10);
    }
    if(event->key()==Qt::Key_Z){
        stlM->scale(operationStlName,0.9);
    }
    if(event->key()==Qt::Key_X){
        stlM->scale(operationStlName,1.1);
    }
    if(event->key()==Qt::Key_U){
        stlM->rotateX(operationStlName,10);
    }
    if(event->key()==Qt::Key_I){
        stlM->rotateY(operationStlName,10);
    }
    if(event->key()==Qt::Key_O){
        stlM->rotateZ(operationStlName,10);
    }
    if(event->key()==Qt::Key_J){
        stlM->rotateX(operationStlName,-10);
    }
    if(event->key()==Qt::Key_K){
        stlM->rotateY(operationStlName,-10);
    }
    if(event->key()==Qt::Key_L){
        stlM->rotateZ(operationStlName,-10);
    }
    if(event->key()==Qt::Key_M){
        operationStlName="body";
        operationActor=stlM->LoadStl(QDir::currentPath()+"/externalResources/body.stl",operationStlName);
        operationActor->GetProperty()->SetOpacity(0.2);
        operationActor->GetProperty()->SetColor(0.243,0.5725,0.843);
        m_pRenderer->AddActor(operationActor);
        volumeWidget->GetRenderWindow()->Render();
    }
    if(event->key()==Qt::Key_C){
        double* position=operationActor->GetPosition();
        double* orientation=operationActor->GetOrientationWXYZ();
        double* scale=operationActor->GetScale();
        qDebug()<<"position[0]: "<<position[0]<<"  |  position[1]: "<<position[1]<<"  | position[2]: "<<position[2];
        qDebug()<<"orientation[0]: "<<orientation[0]<<"  |  orientation[1]: "<<orientation[1]<<"  | orientation[2]: "<<orientation[2];
        qDebug()<<"scale[0]: "<<scale[0]<<"  |  scale[1]: "<<scale[1]<<"  | scale[2]: "<<scale[2];
    }
    if(event->key()==Qt::Key_V){
        canTarger=!canTarger;
    }
    volumeWidget->GetRenderWindow()->Render();
}

void Widget::on_volumeSlider_valueChanged(int value)
{
    qDebug()<<"on_volumeSlider_valueChanged";
    qDebug()<<"lastposition:"<<lastposition;
    double shiftValue=double(value-lastposition)/255.0;
    qDebug()<<"shiftValue:"<<shiftValue;
    lastposition=value;

    settingDefault->ShiftRenderFunction(shiftValue,1);
    settingDefault->ShiftRenderFunction(shiftValue,2);

    volumeWidget->GetRenderWindow()->Render();
}

void Widget::on_sagitalSlider_valueChanged(int value)
{
    m_sagitalViewer2->SetSlice(value);
    ui->sagitalSliderNum->setText(QString::number(value));
    update();
    m_sagitalViewer2->GetRenderWindow()->Render();
}

void Widget::on_coronalSlider_valueChanged(int value)
{
    m_coronalViewer2->SetSlice(value);
    ui->coronalSliderNum->setText(QString::number(value));
    update();
    m_coronalViewer2->GetRenderWindow()->Render();
}

void Widget::on_axialSlider_valueChanged(int value)
{
    m_axialViewer2->SetSlice(value);
    ui->axialSliderNum->setText(QString::number(value));
    update();
    m_axialViewer2->GetRenderWindow()->Render();
}

void Widget::on_navigationButton_clicked()
{
    onOpenVolumeDir();
}

//在指定位置创建一个球体，组装，并返回actor以用于Render
vtkSmartPointer<vtkActor> Widget::getSphereActor(double x,double y,double z){
    vtkSmartPointer<vtkSphereSource> sphereSource=vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(x,y,z);   // 设置中心
    sphereSource->SetRadius(10);             // 设置半径
    sphereSource->SetThetaResolution(52);
    sphereSource->SetPhiResolution(52);
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> actor=vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.0,1.0,0.0);

    return actor;
}

vtkSmartPointer<vtkActor> Widget::getLineActorXY(double x,double y,double x1,double y1){
    vtkSmartPointer<vtkLineSource> line=vtkSmartPointer<vtkLineSource>::New();
    line->SetPoint1(x,y,350);
    line->SetPoint2(x1,y1,350);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(line->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(4);
    actor->GetProperty()->SetColor(1.0,0.0,0.0);

    return actor;
}

vtkSmartPointer<vtkActor> Widget::getLineActorXZ(double x,double z,double x1,double z1){
    vtkSmartPointer<vtkLineSource> line=vtkSmartPointer<vtkLineSource>::New();
    line->SetPoint1(x,999,z);
    line->SetPoint2(x1,999,z1);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(line->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(4);
    actor->GetProperty()->SetColor(1.0,0.0,0.0);

    return actor;
}

vtkSmartPointer<vtkActor> Widget::getLineActorYZ(double y,double z,double y1,double z1){
    vtkSmartPointer<vtkLineSource> line=vtkSmartPointer<vtkLineSource>::New();
    line->SetPoint1(699,y,z);
    line->SetPoint2(699,y1,z1);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(line->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(4);
    actor->GetProperty()->SetColor(1.0,0.0,0.0);

    return actor;
}

void Widget::setQVTKEventConnection(QMouseEvent* event){
    qDebug()<<"mousemove move";
    qDebug()<<event->x();
    qDebug()<<event->y();
}

void Widget::on_greenButton1_clicked()
{
    qDebug()<<"on_greenButton1_clicked";
    canPaintSphere=!canPaintSphere;
    operationStlName="gx_1";
    m_pRenderer->AddActor(stlM->LoadStl(QDir::currentPath()+"/externalResources/qx_1.stl",operationStlName));
    volumeWidget->GetRenderWindow()->Render();

}

void Widget::on_greenButton2_clicked()
{
    qDebug()<<"on_greenButton2_clicked";
    vtkSmartPointer<vtkRenderWindow> renWin =m_pRenderer->GetRenderWindow();
    vtkSmartPointer<vtkActor> a=getSphereActor(0,0,0);
    m_pRenderer->AddActor(a);
    Animator *animator=new Animator(renWin,a,Motion::translate,0,100,0);
    Animator *animator2=new Animator(renWin,a,Motion::scale,1.5,1.5,1.5);
    AnimatorSet *animatorSet=new AnimatorSet();
    animatorSet->addAnimator(animator);
    animatorSet->addAnimator(animator2);
    animatorSet->setDuration(3000);
    animatorSet->start();


//    Animator *animators=new Animator(renWin,a,Motion::scale,1.5,1.5,3);
//    animators->setDuration(2000);
//    animators->start();


//    Animator *animators2=new Animator(renWin,a,Motion::scale,3,3,3);
//    animators2->setDuration(2000);
//    animators2->start();

    //    vtkSmartPointer<vtkRenderWindow> renWin =m_pRenderer->GetRenderWindow();
    //    vtkSmartPointer<vtkActor> a=getSphereActor(0,0,0);
    //    m_pRenderer->AddActor(a);
    //    Animator *animator=new Animator(renWin,a,Motion::translate,100,0,0);
    //    animator->setDuration(2000);
    //    animator->start();

    //    Animator *animator2=new Animator(renWin,a,Motion::translate,0,100,0);
    //    animator2->setDuration(2000);
    //    animator2->start();

    //    //start again well be duration error
    // //   animator->start();
}

void Widget::on_translateButton_clicked()
{
    operationCliked=!operationCliked;
    if(operationCliked){
        ui->volumeWidget->setGeometry(20,55,1490,765);
    }else{
        ui->volumeWidget->setGeometry(20,55,735,365);
    }
    ui->volumeWidget->raise();
    update();
}
