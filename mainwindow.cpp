#include "mainwindow.h"
#include "CoordinateConverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(0, Qt::FramelessWindowHint), m_embedded(false)
{
    Q_UNUSED(parent);

    update_background();
    init();

    //主窗口焦点
    this->setFocus();
    setLayout();
    setConnection();
    QPushButton *textButton1=new QPushButton(this);
    textButton1->setGeometry(1531,434,60,60);
}

MainWindow::~MainWindow()
{
}

//主窗口更新背景
void MainWindow::update_background(){
    m_background=QPixmap(":/resources/background.jpg", "jpg");
    QBitmap bitmap = m_background.createHeuristicMask();
    setFixedSize(m_background.size());
    setMask(bitmap);
    update();
}

//初始化
void MainWindow::init(){
    greenButton1=new GreenButton(this);
    greenButton2=new GreenButton(this);
    navigationButton=new BackgroundButton(this);
    exitButton=new BackgroundButton(this);
    translateButton=new BackgroundButton(this);
    magnifyButton=new BackgroundButton(this);
    shrinkButton=new BackgroundButton(this);
    isOpenDir=false;
    volumeWidget=new myVolumeWidget(this);
    sagitalWidget=new mySlicerWidget(this);
    axialWidget=new mySlicerWidget(this);
    coronalWidget=new mySlicerWidget(this);
    lastposition=120;
    volumeSlider=new QSlider(this);
    sagitalSlider=new QSlider(this);
    axialSlider=new QSlider(this);
    coronalSlider=new QSlider(this);
    vtkQtConnect=vtkSmartPointer<vtkEventQtSlotConnect>::New();
    stlM=new stlManager();
    actorM=new actorManager();
}

//布局
void MainWindow::setLayout(){
    greenButton1->setPos(1531,55);
    greenButton2->setPos(1531,118);

    navigationButton->setPos(510,3);
    navigationButton->setBackground(":/resources/navigation.png","png");
    exitButton->setPos(1530,3);
    exitButton->setBackground(":/resources/mainPower.png","png");
    exitButton->setClickedColor(QColor(95,100,137,150));
    translateButton->setPos(1531,181);
    translateButton->setBackground(":/resources/mainTranslation","png");
    translateButton->setClickedColor(QColor(185,188,193,150));
    magnifyButton->setPos(1531,271);
    magnifyButton->setBackground(":/resources/mainMagnify.png","png");
    magnifyButton->setClickedColor(QColor(185,188,193,150));
    shrinkButton->setPos(1531,334);
    shrinkButton->setBackground(":/resources/mainShrink.png","png");
    shrinkButton->setClickedColor(QColor(185,188,193,150));

    volumeWidget->setLocation(20,55,735,365);//默认的几何位置
    volumeSlider->setGeometry(20,425,735,20);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0,255);

    sagitalWidget->setLocation(775,55,735,365);
    sagitalSlider->setGeometry(775,425,735,20);
    sagitalSlider->setOrientation(Qt::Horizontal);

    axialWidget->setLocation(775,455,735,365);
    axialSlider->setGeometry(775,830,735,20);
    axialSlider->setOrientation(Qt::Horizontal);

    coronalWidget->setLocation(20,455,735,365);
    coronalSlider->setGeometry(20,830,735,20);
    coronalSlider->setOrientation(Qt::Horizontal);
}

//按钮信号连接
void MainWindow::setConnection(){
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitClicked()));
    connect(navigationButton,SIGNAL(clicked()),this,SLOT(navigationClicked()));
    connect(translateButton,SIGNAL(clicked()),this,SLOT(translateClicked()));
    connect(magnifyButton,SIGNAL(clicked()),this,SLOT(magnifyClicked()));
    connect(shrinkButton,SIGNAL(clicked()),this,SLOT(shrinkCliked()));

}

//有体绘制数据时需要连接的信号
void MainWindow::setDrawConnection(){
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(vSlicerValueChange(int)));
    connect(sagitalSlider,SIGNAL(valueChanged(int)),this,SLOT(sSlicerValueChange(int)));
    connect(axialSlider,SIGNAL(valueChanged(int)),this,SLOT(aSlicerValueChange(int)));
    connect(coronalSlider,SIGNAL(valueChanged(int)),this,SLOT(cSlicerValueChange(int)));
    connect(greenButton1,SIGNAL(clicked()),this,SLOT(greenButton1Clicked()));
    connect(greenButton2,SIGNAL(clicked()),this,SLOT(greenButton2Clicked()));
    vtkQtConnect->Connect(volumeWidget->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(volumeWidgetClick(vtkObject*, unsigned long, void*, void*)));
}

//体绘制窗口下滑动条 拖动触发事件
void MainWindow::vSlicerValueChange(int v){
    double shiftValue=double(v-lastposition)/255.0;
    lastposition=v;
    volumeWidget->settingDefault->ShiftRenderFunction(shiftValue,1);
    volumeWidget->settingDefault->ShiftRenderFunction(shiftValue,2);
    volumeWidget->updateRender();

}

//sagital窗口下滑动条 拖动触发事件
void MainWindow::sSlicerValueChange(int v){
    sagitalWidget->setSlicerValue(v);
}

//axial窗口下滑动条 拖动触发事件
void MainWindow::aSlicerValueChange(int v){
    axialWidget->setSlicerValue(v);
}

//coronal窗口下滑动条 拖动触发事件
void MainWindow::cSlicerValueChange(int v){
    coronalWidget->setSlicerValue(v);
}

//导航按钮点击
void MainWindow::navigationClicked(){
    qDebug()<<"MainWindow::navigationClicked";
    onOpenVolumeDir();
}

//点击退出
void MainWindow::exitClicked(){
    qDebug()<<"MainWindow::exitClicked";
    //TODO 退出应该弹出窗口请求确认
    QCoreApplication::instance()->quit();
}

//十字交叉按钮
void MainWindow::translateClicked(){
    qDebug()<<"MainWindow::translateClicked";
    if(volumeWidget->width()<1000){
        volumeWidget->setLocation(20,55,1490,765);
        volumeSlider->setGeometry(20,830,1490,20);
        coronalSlider->hide();
        axialSlider->hide();
    }else{
        volumeWidget->setLocation(20,55,735,365);
        volumeSlider->setGeometry(20,425,735,20);
        coronalSlider->show();
        axialSlider->show();
    }
    volumeWidget->raise();
    update();
}

//放大按钮点击
void MainWindow::magnifyClicked(){
    qDebug()<<"MainWindow::magnifyClicked";
    //TODO 我tm也不知道这个按钮设计来干啥的
}

//缩小按钮
void MainWindow::shrinkCliked(){
    qDebug()<<"MainWindow::shrinkCliked";
    //TODO 我tm还是不知道这个按钮设计来干啥的
}

//主窗口重绘制触发事件，一般发生在窗口切换
void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.drawPixmap(e->rect(), m_background, e->rect());
}

//体绘制窗口点击事件
void MainWindow::volumeWidgetClick(vtkObject* obj, unsigned long, void*, void*){

}

//打开体绘制文件夹
void MainWindow::onOpenVolumeDir(){
    qDebug()<<"MainWindow::onOpenVolumeDir";
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

    volumeWidget->setVolumeData(dirPath_str);
    if(volumeWidget->hasVolumeData()){
        volumeSlider->setValue(120);
        lastposition=120;
        //TODO弹出进度条

        //sagittal为xy方向截面
        sagitalWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::XY);
        sagitalWidget->setSlicerValue(100);
        sagitalSlider->setRange(sagitalWidget->getSlicerMin(),sagitalWidget->getSlicerMax());
        sagitalSlider->setValue(100);

        //axial为xz截面
        axialWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::XZ);
        axialWidget->setSlicerValue(140);
        axialSlider->setRange(axialWidget->getSlicerMin(),axialWidget->getSlicerMax());
        axialSlider->setValue(140);

        //coronal为yz截面
        coronalWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::YZ);
        coronalWidget->setSlicerValue(140);
        coronalSlider->setRange(coronalWidget->getSlicerMin(),coronalWidget->getSlicerMax());
        coronalSlider->setValue(140);

        setDrawConnection();

        //得到边界与三个截面Slice的比例关系
        double *boundary=sagitalWidget->getImageViewer2()->GetImageActor()->GetBounds();
        boundary[1]=sagitalWidget->getImageViewer2()->GetImageActor()->GetBounds()[1];
        boundary[3]=sagitalWidget->getImageViewer2()->GetImageActor()->GetBounds()[3];
        boundary[5]=coronalWidget->getImageViewer2()->GetImageActor()->GetBounds()[5];

        qDebug()<<"boundarx:"<<boundary[1];
        qDebug()<<"boundary:"<<boundary[3];
        qDebug()<<"boundarz:"<<boundary[5];
        qDebug()<<"sagitalSlicerMAX:"<<sagitalWidget->getImageViewer2()->GetSliceMax();
        qDebug()<<"axialSlicerMax:"<<sagitalWidget->getImageViewer2()->GetSliceMax();
        qDebug()<<"coronalSlicerMax:"<<coronalWidget->getImageViewer2()->GetSliceMax();

        proportionZ=boundary[5]/sagitalWidget->getImageViewer2()->GetSliceMax();
        qDebug()<<"proportionZ"<<proportionZ;
        proportionY=boundary[3]/axialWidget->getImageViewer2()->GetSliceMax();
        qDebug()<<"proportionY"<<proportionY;
        proportionX=boundary[1]/coronalWidget->getImageViewer2()->GetSliceMax();
        qDebug()<<"proportionX"<<proportionX;
    }else{
        //TODO  这里提示路径错误
    }

}

//主窗口键盘事件
void MainWindow::keyPressEvent(QKeyEvent *event){
    Q_UNUSED(event);
    if(!volumeWidget->hasVolumeData()){
        qDebug()<<"noVolumeData";
        return;
    }
    qDebug()<<"keyPressEvent:"<<event->key();
    if(event->key()==Qt::Key_0){
        volumeWidget->settingDefault->SetRenderType(RenderSetting::RenderType::CT_Normal);
        this->setWindowTitle("CT_Normal");
        lastposition=120;
        volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_1){
        volumeWidget->settingDefault->SetRenderType(RenderSetting::RenderType::CT_Bone);
        this->setWindowTitle("CT_Bone");
        lastposition=120;
        volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_2){
        volumeWidget->settingDefault->SetRenderType(RenderSetting::RenderType::CT_AAA);
        this->setWindowTitle("CT_AAA");
        lastposition=120;
        volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_3){
        volumeWidget->settingDefault->SetRenderType(RenderSetting::RenderType::CT_Liver_Vasculature);
        this->setWindowTitle("CT_Liver_Vasculature");
        lastposition=120;
        volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_4){
        volumeWidget->settingDefault->SetRenderType(RenderSetting::RenderType::CT_Lung);
        this->setWindowTitle("CT_Lung");
        lastposition=120;
        volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_5){
        volumeWidget->settingDefault->SetRenderType(RenderSetting::RenderType::MR_Default);
        this->setWindowTitle("MR_Default");
        lastposition=120;
        volumeSlider->setValue(120);
    }
    if(event->key()==Qt::Key_6){
        volumeWidget->settingDefault->SetRenderType(RenderSetting::RenderType::MR_Brain);
        this->setWindowTitle("MR_Brain");
        lastposition=120;
        volumeSlider->setValue(120);
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
        //加载人体
        operationStlName="body";
        vtkSmartPointer<vtkActor> operationActor=stlM->LoadStl("E:/MNavigation/externalResources/body.stl",operationStlName);
        operationActor->GetProperty()->SetOpacity(0.2);
        operationActor->GetProperty()->SetColor(0.243,0.5725,0.843);
        volumeWidget->getRenderer()->AddActor(operationActor);
        volumeWidget->GetRenderWindow()->Render();
    }
    if(event->key()==Qt::Key_V){
        canTarger=!canTarger;
    }
    volumeWidget->updateRender();
}

//绿色按钮1点击事件
void MainWindow::greenButton1Clicked(){
    qDebug()<<"MainWindow::greenButton1Clicked";
    //加载探针1
    if(volumeWidget->hasVolumeData()){
        operationStlName="gx_1";
        volumeWidget->getRenderer()->AddActor(stlM->LoadStl("E:/MNavigation/externalResources/qx_1.stl",operationStlName));
        volumeWidget->GetRenderWindow()->Render();
    }
}

//绿色按钮2点击事件
void MainWindow::greenButton2Clicked(){
    qDebug()<<"on_greenButton2_clicked";

    vtkSmartPointer<vtkRenderWindow> renWin =volumeWidget->GetRenderWindow();
    vtkSmartPointer<vtkRenderer> m_pRenderer=volumeWidget->getRenderer();
    //    vtkSmartPointer<vtkRenderWindowInteractor> iren =vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //   vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //   iren->SetInteractorStyle(style);

    //  renWin->AddRenderer(m_pRenderer);
    //  iren->SetRenderWindow(renWin);
    vtkSmartPointer<vtkSphereSource> sphere =vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(0,0,0);   // 设置中心
    sphere->SetRadius(10);             // 设置半径
    sphere->SetThetaResolution(52);
    sphere->SetPhiResolution(52);
    vtkSmartPointer<vtkPolyDataMapper> mapper =vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkTransform> transform= vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter= vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    //   transform->Translate(120,0,0);
    transformFilter->SetTransform(transform);
    transformFilter->SetInputConnection(sphere->GetOutputPort());
    transformFilter->Update();
    mapper->SetInputConnection(transformFilter->GetOutputPort());

    vtkSmartPointer<vtkActor> actor1 =vtkSmartPointer<vtkActor>::New();
    actor1->SetMapper(mapper);
    actor1->GetProperty()->SetColor(0.32,0,0.68);
    m_pRenderer->AddActor(actor1);
    renWin->Render();

    //Create an Animation Scene
    vtkSmartPointer<vtkAnimationScene> scene = vtkSmartPointer<vtkAnimationScene>::New();
    //   scene->SetLoop(true);
    scene->SetTimeModeToRelative();
    scene->SetFrameRate(5);
    scene->SetStartTime(0);
    scene->SetEndTime(10);

    // Create an Animation Cue to animate thecamera.
    vtkSmartPointer<vtkCustomTransformAnimationCue> cue1 = vtkSmartPointer<vtkCustomTransformAnimationCue>::New();
    cue1->Sphere = sphere;
    cue1->RenWin = renWin;
    cue1->renderer=m_pRenderer;
    cue1->transform=transform;

    cue1->SetTimeModeToNormalized();
    cue1->SetStartTime(0);
    cue1->SetEndTime(1.0);
    scene->AddCue(cue1);

    scene->Play();
    scene->Stop();

    /*
    if(clickTimes>0){
        qDebug()<<"clickTimes:"<<clickTimes;
        qDebug()<<"actors:"<<m_pRenderer->GetActors()->GetNumberOfItems();
       m_pRenderer->RemoveActor(actor);
    }
    clickTimes++;
    vtkSmartPointer<vtkSphereSource> sphere =vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(clickTimes*20,0,0);   // 设置中心
    sphere->SetRadius(10);             // 设置半径
    sphere->SetThetaResolution(52);
    sphere->SetPhiResolution(52);
    vtkSmartPointer<vtkPolyDataMapper> mapper =vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort());

    actor=getSphereActor(0,0,0);
    actor->GetProperty()->SetColor(0.32,0,0.68);
    actor->SetMapper(mapper);
    m_pRenderer->AddActor(actor);
    m_pRenderer->GetRenderWindow()->Render();
    m_pRenderer->GetRenderWindow()->GetInteractor()->Start();
    */
}
