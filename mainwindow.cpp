#include "mainwindow.h"


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

    //这个按钮可以让主窗口获取焦点
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

    volumeWidget=new myVolumeWidget(this);
    sagitalWidget=new mySlicerWidget(this);
    axialWidget=new mySlicerWidget(this);
    coronalWidget=new mySlicerWidget(this);

    stlLoadDialog=new MyDialog();
    stlSelectDialog=new MyDialog();
    stlDeleteDialog=new MyDialog();
    stlDeleteButton=new QPushButton(this);

    sagitalLabel=new QLabel(this);
    coronalLabel=new QLabel(this);
    axialLabel=new QLabel(this);
    volumeSlider=new QSlider(this);
    sagitalSlider=new QSlider(this);
    axialSlider=new QSlider(this);
    coronalSlider=new QSlider(this);

    isOpenDir=false;
    lastposition=120;
    vtkQtConnect=vtkSmartPointer<vtkEventQtSlotConnect>::New();
    stlManager=new StlManager();
    actorM=new actorManager();
}

//布局
void MainWindow::setLayout(){
    greenButton1->setPos(1531,55);
    stlLoadDialog->setGeometry(greenButton1->getXpos()-100,greenButton1->getYpos()+100,200,200);

    /**
     *TODO 这部分应该写入配置文件，而不是直接加载
     */
    stlList.append(QString::fromLocal8Bit("双通道导管"));
    stlList.append(QString::fromLocal8Bit("安全骨钻1"));
    stlList.append(QString::fromLocal8Bit("安全骨钻2"));
    stlList.append(QString::fromLocal8Bit("圆锯"));
    stlList.append(QString::fromLocal8Bit("细导丝"));
    stlList.append(QString::fromLocal8Bit("细针"));
    stlList.append(QString::fromLocal8Bit("人体"));
    stlLoadDialog->setGridTexts(stlList);

    greenButton2->setPos(1531,118);
    stlSelectDialog->setGeometry(greenButton2->getXpos()-100,greenButton2->getYpos()+100,200,200);
    stlSelectDialog->setHint(QString::fromLocal8Bit("选中你要操作的.stl模型"));

    navigationButton->setPos(510,3);
    navigationButton->setBackground(":/resources/navigation.png","png");
    stlDeleteButton->setGeometry(730,3,80,43);
    stlDeleteButton->setText(QString::fromLocal8Bit("删除.stl"));
    stlDeleteDialog->setGeometry(stlDeleteButton->x(),stlDeleteButton->y()+150,200,200);
    stlDeleteDialog->setHint(QString::fromLocal8Bit("选择删除场景中的.stl模型"));
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
    //退出按钮点击的信号绑定
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitClicked()));
    //导航按钮的信号绑定
    connect(navigationButton,SIGNAL(clicked()),this,SLOT(navigationClicked()));
    //十字箭头按钮的信号绑定
    connect(translateButton,SIGNAL(clicked()),this,SLOT(translateClicked()));
    //放大按钮点击的信号绑定
    connect(magnifyButton,SIGNAL(clicked()),this,SLOT(magnifyClicked()));
    //缩小按钮点击的信号绑定
    connect(shrinkButton,SIGNAL(clicked()),this,SLOT(shrinkCliked()));
}

//有体绘制数据时需要连接的信号
void MainWindow::setDrawConnection(){
    //体绘制窗口下滑动条数值改变的信号绑定
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(vSlicerValueChange(int)));
    //sagital截面窗口下滑动条数值改变的信号绑定
    connect(sagitalSlider,SIGNAL(valueChanged(int)),this,SLOT(sSlicerValueChange(int)));
    //axial截面窗口下滑动条数值改变的信号绑定
    connect(axialSlider,SIGNAL(valueChanged(int)),this,SLOT(aSlicerValueChange(int)));
    //coronal截面窗口下滑动条数值改变的信号绑定
    connect(coronalSlider,SIGNAL(valueChanged(int)),this,SLOT(cSlicerValueChange(int)));
    //绿色按钮1点击的信号绑定
    connect(greenButton1,SIGNAL(clicked()),this,SLOT(greenButton1Clicked()));
    //绿色按钮2点击的信号绑定
    connect(greenButton2,SIGNAL(clicked()),this,SLOT(greenButton2Clicked()));
    //删除按钮点击的信号绑定
    connect(stlDeleteButton,SIGNAL(clicked()),this,SLOT(deleteButtonClicked()));
    //加载哪一个.stl模型对话框的信号绑定
    connect(stlLoadDialog,SIGNAL(onItemClicked(QString,int)),this,SLOT(loadStl(QString,int)));
    //选择操作哪一个.stl模型对话框的信号绑定
    connect(stlSelectDialog,SIGNAL(onItemClicked(QString,int)),this,SLOT(selectStl(QString,int)));
    //选择删除哪一个.stl模型对话框的信号绑定
    connect(stlDeleteDialog,SIGNAL(onItemClicked(QString,int)),this,SLOT(deleteStl(QString,int)));
    //体绘制窗口的鼠标左键点击的信号绑定
    vtkQtConnect->Connect(volumeWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(volumeWidgetClick(vtkObject*, unsigned long, void*, void*)));
    //sagital截面窗口的鼠标左键点击的信号绑定
    vtkQtConnect->Connect(sagitalWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(sagitalWidgetClick(vtkObject*, unsigned long, void*, void*)));
    //axial截面窗口的鼠标左键点击的信号绑定
    vtkQtConnect->Connect(axialWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(axialWidgetClick(vtkObject*, unsigned long, void*, void*)));
    //coronal截面窗口的鼠标左键点击的的信号绑定
    vtkQtConnect->Connect(coronalWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(coronalWidgetClick(vtkObject*, unsigned long, void*, void*)));
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
    if(volumeWidget->getQVTKWidget()->width()<1000){
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
    volumeWidget->getQVTKWidget()->raise();
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
//sagital截面窗口点击事件
void MainWindow::sagitalWidgetClick(vtkObject* obj, unsigned long, void*, void*){
    qDebug()<<"MainWindow::sagitalClicked";
    //在三个截面窗口上联动，并绘制标记
    vtkSmartPointer<vtkImageViewer2> m_sagitalViewer2=sagitalWidget->getImageViewer2();
    vtkSmartPointer<vtkImageViewer2> m_axialViewer2=axialWidget->getImageViewer2();
    vtkSmartPointer<vtkImageViewer2> m_coronalViewer2=coronalWidget->getImageViewer2();
    vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    vtkImageActor* Actor = m_sagitalViewer2->GetImageActor();
    vtkRenderer* Renderer= m_sagitalViewer2->GetRenderer();
    /*BEGIN 以下是殊峰做的坐标转换*/
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

    double xRatio = (ViewEventPointX - originView[0]) / (xView[0] - originView[0]);
    double yRatio = (ViewEventPointY - originView[1]) / (yView[1] - originView[1]);

    vtkVector3d targetPosition = vtkVector3d();
    targetPosition[0] = xRatio * (xEnd[0] - origin[0]) + origin[0];
    targetPosition[1] = yRatio * (yEnd[1] - origin[1]) + origin[1];
    targetPosition[2] = origin[2];
    vtkMatrix4x4* matrix = volumeWidget->getVolume()->GetMatrix();
    vtkVector3d adjust = vtkVector3d(matrix->MultiplyDoublePoint(targetPosition.GetData()));
    /*END 殊峰做的坐标转换结束*/

    //绘制 十字线段标记
    if(adjust[0]>0&&adjust[1]>0){
        if(canTarger){
            volumeWidget->getRenderer()->AddActor(actorM->getSphereActor(adjust[0],adjust[1],adjust[2]));

            //sagital截面绘制十字，z轴高度一定
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]+1,adjust[1],350,adjust[0]+10,adjust[1],350));
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],adjust[1]+1,350,adjust[0],adjust[1]+10,350));
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]-1,adjust[1],350,adjust[0]-10,adjust[1],350));
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],adjust[1]-1,350,adjust[0],adjust[1]-10,350));

            //axial截面绘制十字，y轴高度一定
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]+1,999,adjust[2],adjust[0]+10,999,adjust[2]));
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],999,adjust[2]+1,adjust[0],999,adjust[2]+10));
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]-1,999,adjust[2],adjust[0]-10,999,adjust[2]));
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],999,adjust[2]-1,adjust[0],999,adjust[2]-10));


            //coronal截面绘制十字，x轴高度一定
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1]+1,adjust[2],699,adjust[1]+10,adjust[2]));
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1],adjust[2]+1,699,adjust[1],adjust[2]+10));
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1]-1,adjust[2],699,adjust[1]-10,adjust[2]));
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1],adjust[2]-1,699,adjust[1],adjust[2]-10));

            //这样操作之后，绘制的十字层级会正确显示
            sagitalSlider->setValue(sagitalSlider->value()+1);
            sagitalSlider->setValue(sagitalSlider->value()-1);
            axialSlider->setValue(axialSlider->value()+1);
            axialSlider->setValue(axialSlider->value()-1);
            coronalSlider->setValue(coronalSlider->value()+1);
            coronalSlider->setValue(coronalSlider->value()-1);
        }else{
        }
        sagitalWidget->updateRender();

        volumeWidget->getQVTKWidget()->GetRenderWindow()->Render();

        //坐标分发，将sagital截面的x坐标发送给coronal截面的切片，y坐标发送给axial截面的切片
        axialSlider->setValue((int) adjust[1]/proportionY);
        coronalSlider->setValue((int) adjust[0]/proportionX);
        update();
    }else{
        return;
    }
}
//axial截面窗口点击事件
void MainWindow::axialWidgetClick(vtkObject* obj, unsigned long, void*, void*){

}
//coronal截面窗口点击事件
void MainWindow::coronalWidgetClick(vtkObject* obj, unsigned long, void*, void*){

}

//打开体绘制文件夹
void MainWindow::onOpenVolumeDir(){
    qDebug()<<"MainWindow::onOpenVolumeDir";
    QString dirPath=QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("打开体绘制数据存储文件夹"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
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
        stlManager->translate(operationStlName,10,0,0);
    }
    if(event->key()==Qt::Key_W){
        stlManager->translate(operationStlName,0,10,0);
    }
    if(event->key()==Qt::Key_E){
        stlManager->translate(operationStlName,0,0,10);
    }
    if(event->key()==Qt::Key_A){
        stlManager->translate(operationStlName,-10,0,0);
    }
    if(event->key()==Qt::Key_S){
        stlManager->translate(operationStlName,0,-10,0);
    }
    if(event->key()==Qt::Key_D){
        stlManager->translate(operationStlName,0,0,-10);
    }
    if(event->key()==Qt::Key_Z){
        stlManager->scale(operationStlName,0.9);
    }
    if(event->key()==Qt::Key_X){
        stlManager->scale(operationStlName,1.1);
    }
    if(event->key()==Qt::Key_U){
        stlManager->rotateX(operationStlName,10);
    }
    if(event->key()==Qt::Key_I){
        stlManager->rotateY(operationStlName,10);
    }
    if(event->key()==Qt::Key_O){
        stlManager->rotateZ(operationStlName,10);
    }
    if(event->key()==Qt::Key_J){
        stlManager->rotateX(operationStlName,-10);
    }
    if(event->key()==Qt::Key_K){
        stlManager->rotateY(operationStlName,-10);
    }
    if(event->key()==Qt::Key_L){
        stlManager->rotateZ(operationStlName,-10);
    }

    /**
      *加载人体的功能已经列入stlLoadDialog对话框的选项中，
      * Opacity和Color的设置也移植了过去
      */
//    if(event->key()==Qt::Key_M){
//        //加载人体
//        operationStlName="body";
//        vtkSmartPointer<vtkActor> operationActor=stlManager->LoadStl(QDir::currentPath()+"/externalResources/body.stl",operationStlName);
//        operationActor->GetProperty()->SetOpacity(0.2);
//        operationActor->GetProperty()->SetColor(0.243,0.5725,0.843);
//        volumeWidget->getRenderer()->AddActor(operationActor);
//        volumeWidget->getQVTKWidget()->GetRenderWindow()->Render();
//    }
    if(event->key()==Qt::Key_V){
        canTarger=!canTarger;
    }
    volumeWidget->updateRender();
}
void MainWindow::deleteButtonClicked(){
    if(!volumeWidget->hasVolumeData()){
        return ;
    }
    //每次弹出对话框之前更新当前场景中已经加载的.stl模型的标识符有哪些
    stlDeleteDialog->setGridTexts(stlManager->getActorList());
    stlDeleteDialog->show();
}

void MainWindow::deleteStl(QString name, int index){
    //如果当期操作的.stl为要删除的，那么置空
//    if(operationStlName.compare(name)){
//         operationStlName=NULL;
//    }
    stlManager->deleteActor(name,volumeWidget->getRenderer());
}

//绿色按钮1点击事件,弹出对话框，选择要加载的.stl模型
void MainWindow::greenButton1Clicked(){
    //弹出对话框，选择要加载的.stl模型
    if(volumeWidget->hasVolumeData()){
        stlLoadDialog->show();
    }
}

/**
 * @brief MainWindow::loadStl
 *  体绘制窗口加载.stl模型
 * @param name
 * 模型名
 * @param index
 */
void MainWindow::loadStl(QString name, int index){
    //默认当前操作的.stl模型为最后加载的那个
    operationStlName=name;

    QString dirPath=QDir::currentPath()+"/externalResources/";
    /*根据选择的.stl名加载控件，
     * TODO 这里应该读取配置文件
     */
    switch(index){
    case 0:
        dirPath+="qx_1.stl";
        break;
    case 1:
        dirPath+="YLQX_A_1.stl";
        break;
    case 2:
        dirPath+="YLQX_B_1.stl";
        break;
    case 3:
        dirPath+="YLQX_C_1.stl";
        break;
    case 4:
        dirPath+="YLQX_D.stl";
        break;
    case 5:
        dirPath+="YLQX_E.stl";
        break;
    case 6:
        dirPath+="body.stl";
    }
    vtkSmartPointer<vtkActor> operationActor=stlManager->LoadStl(dirPath,operationStlName);
    if(operationActor==NULL){
        return;
    }
    //如果为人体，默认设置了一些颜色和透明度
    //TODO 对.stl模型颜色和透明度的设置应该放在stlManageranager这个类中
    if(index==6){
        operationActor->GetProperty()->SetOpacity(0.2);
        operationActor->GetProperty()->SetColor(0.243,0.5725,0.843);
    }
    volumeWidget->getRenderer()->AddActor(operationActor);
    volumeWidget->getQVTKWidget()->GetRenderWindow()->Render();
}

void MainWindow::selectStl(QString name, int index){
    operationStlName=name;
}

//绿色按钮2点击事件，弹出对话框，选择你要操作的.stl模型
void MainWindow::greenButton2Clicked(){
    qDebug()<<"on_greenButton2_clicked";
    if(!volumeWidget->hasVolumeData()){
        return;
    }
    //每次弹出对话框之前更新当前场景中已经加载的.stl模型的标识符有哪些
    stlSelectDialog->setGridTexts(stlManager->getActorList());
    stlSelectDialog->show();

    /*  以下代码为老版本绿色按钮2功能，播放一个自定义的动画
    vtkSmartPointer<vtkRenderWindow> renWin =volumeWidget->getQVTKWidget()->GetRenderWindow();
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
    */


    /*以下代码为手动绘制小球，并根据点击次数移动
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
