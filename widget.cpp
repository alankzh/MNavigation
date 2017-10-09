#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QCoreApplication>
#include <vtkCamera.h>

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
    vtkOutputWindow::GlobalWarningDisplayOff();//关闭伴随的vtkOutputWindow
    onOpenVolumeDir();//软件开始直接打开文件夹

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
    m_vtkQtConnect=vtkEventQtSlotConnect::New();

    settingDefault=new RenderSetting();//构造函数初始化
    lastposition=120;
    isOpenDir=false;

    GreenButton greenbutton1=new GreenButton(this);
    greenbutton1.setXpos(510-60);
    greenbutton1.setYpos(3);
    greenbutton1.setGeometry(510-60,3,60,60);
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
}

void Widget::onOpenVolumeDir(){
     if(isOpenDir){
      init();
     }
     qDebug()<<"onOpenVolumeDir";
     QString dirPath=QFileDialog::getExistingDirectory(this,tr("打开体绘制数据存储文件夹"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
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

    volumeWidget->GetRenderWindow()->AddRenderer(m_pRenderer);
    volumeWidget->GetRenderWindow()->GetInteractor()->GetInteractorStyle()->SetDefaultRenderer(m_pRenderer);
    // Add the volume to the scene
    m_pRenderer->AddVolume( volume );
    m_pRenderer->ResetCamera();
    ui->volumeSlider->setRange(0,255);
    ui->volumeSlider->setValue(120);
    settingDefault->SetRenderType(RenderSetting::RenderType::CT_Bone);//默认的渲染
//    ui->volumeSlider->setValue(0);

    m_sagitalViewer2->SetInputConnection(dicomReader->GetOutputPort());
    m_sagitalViewer2->SetRenderWindow(sagitalWidget->GetRenderWindow());
    m_sagitalViewer2->SetSliceOrientationToXY();
    ui->sagitalSlider->setRange(m_sagitalViewer2->GetSliceMin(),m_sagitalViewer2->GetSliceMax());
    m_sagitalViewer2->SetSlice(100);//TODO 滑动条
    ui->sagitalSlider->setValue(100);
//  m_sagitalViewer2->GetImageActor()->InterpolateOff();
    m_sagitalViewer2->SetupInteractor(sagitalWidget->GetRenderWindow()->GetInteractor());
    m_sagitalViewer2->GetRenderer()->GetActiveCamera()->Zoom(2.5);//镜头拉近

    m_pRenderer->ResetCamera();
    m_pRenderer->DrawOn();

    m_coronalViewer2->SetInputConnection(dicomReader->GetOutputPort());
    m_coronalViewer2->SetRenderWindow(coronalWidget->GetRenderWindow());
    m_coronalViewer2->SetSliceOrientationToYZ();
    ui->coronalSlider->setRange(m_coronalViewer2->GetSliceMin(),m_coronalViewer2->GetSliceMax());
    m_coronalViewer2->SetSlice(140);
    ui->coronalSlider->setValue(140);
//  m_coronalViewer2->GetImageActor()->InterpolateOff();
    m_coronalViewer2->SetupInteractor(coronalWidget->GetRenderWindow()->GetInteractor());
    m_coronalViewer2->GetRenderer()->GetActiveCamera()->Zoom(2.5);//镜头拉近

    m_pRenderer->ResetCamera();
    m_pRenderer->DrawOn();

    m_axialViewer2->SetInputConnection(dicomReader->GetOutputPort());
    m_axialViewer2->SetRenderWindow(axialWidget->GetRenderWindow());
    m_axialViewer2->SetSliceOrientationToXZ();
    ui->axialSlider->setRange(m_axialViewer2->GetSliceMin(),m_axialViewer2->GetSliceMax());
    m_axialViewer2->SetSlice(140);
    ui->axialSlider->setValue(140);
//  m_axialViewer2->GetImageActor()->InterpolateOff();
    m_axialViewer2->SetupInteractor(axialWidget->GetRenderWindow()->GetInteractor());
    m_axialViewer2->GetRenderer()->GetActiveCamera()->Zoom(2.5);//镜头拉近


    m_pRenderer->ResetCamera();
    m_pRenderer->GetActiveCamera()->Zoom(1.5);
    m_pRenderer->DrawOn();
    // interact with data

    setConnect();

    m_sagitalViewer2->GetRenderWindow()->Render();
    m_coronalViewer2->GetRenderWindow()->Render();
    m_axialViewer2->GetRenderWindow()->Render();
    volumeWidget->GetRenderWindow()->Render();
    volumeWidget->GetRenderWindow()->GetInteractor()->Start();


}

void Widget::setConnect(){
    //体绘制窗口的点击事件
    qDebug()<<"setConnect";
    m_vtkQtConnect->Connect(volumeWidget->GetRenderWindow()->GetInteractor(),vtkCommand::MouseMoveEvent|vtkCommand::LeftButtonPressEvent,this,SLOT(mouseClick(vtkObject*)));
    qDebug()<<"setConnectEnd";
}


void Widget::paintEvent(QPaintEvent *event){

}

void Widget::keyPressEvent(QKeyEvent *event){
    Q_UNUSED(event);
    qDebug()<<"keyPressEvent:"<<event->key();


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
    volumeWidget->GetRenderWindow()->Render();
}

void Widget::mouseClick(vtkObject *obj){
    qDebug()<<"mouseClick";
    //获取交互器
   vtkRenderWindowInteractor *iren=vtkRenderWindowInteractor::SafeDownCast(obj);

   //获取鼠标的当前位置
   int eventPos[2];
   iren->GetEventPosition(eventPos);
   this->setWindowTitle(QString("x:%1 y:%2").arg(eventPos[0]).arg(eventPos[1]));
   this->update();
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
    m_sagitalViewer2->GetRenderWindow()->Render();
}


void Widget::on_coronalSlider_valueChanged(int value)
{
    m_coronalViewer2->SetSlice(value);
    m_coronalViewer2->GetRenderWindow()->Render();
}

void Widget::on_axialSlider_valueChanged(int value)
{
    m_axialViewer2->SetSlice(value);
    m_axialViewer2->GetRenderWindow()->Render();
}


void Widget::on_navigationButton_clicked()
{
   onOpenVolumeDir();
}
