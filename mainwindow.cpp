﻿#include "mainwindow.h"
#include "CoordinateConverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(0, Qt::FramelessWindowHint), m_embedded(false)
{
    Q_UNUSED(parent);

    //Old UI
    update_background();
    init();
    setLayout();
    setConnection();
    progressBar=new ProgressBarWidget(ScreenTools::getComputerScreenWidth()/2,ScreenTools::getComputerScreenHeight()/2,this);
    this->setFocus();
    //new UI
    // setLayout2();
    //selectProWidget->disPlay();
}

MainWindow::~MainWindow()
{
    if(stlManager!=NULL){
        delete stlManager;
        stlManager=NULL;
    }
    if(actorM!=NULL){
        delete actorM;
        actorM=NULL;
    }
    if(stlLoadDialog!=NULL){
        delete stlLoadDialog;
        stlLoadDialog=NULL;
    }
    if(stlSelectDialog!=NULL){
        delete stlSelectDialog;
        stlSelectDialog=NULL;
    }
    if(stlDeleteDialog!=NULL){
        delete stlDeleteDialog;
        stlDeleteDialog=NULL;
    }
}

void MainWindow::setLayout2(){
    resize(QSize( Constant::NORMAL_WIDTH,Constant::NORMAL_HEIGHT));
    setFixedSize( Constant::NORMAL_WIDTH, Constant::NORMAL_HEIGHT);

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *titleLayout=new QHBoxLayout();
    titleButton=new BackgroundButton(this);
    titleButton->setBackground(":/resources/title2.png","png");
    titleButton->needClickEffect(false);
    titleButton->setPos(3,3);

    minimizeButton=new ThreeBackgroundButton(this);
    minimizeButton->setBackgroundFront(":/resources/Min_normal.png","png");
    minimizeButton->setBackgroundReverse(":/resources/min_click.png","png");

    maxmizeButton=new ThreeBackgroundButton(this);
    maxmizeButton->setBackgroundFront(":/resources/max_normal.png","png");
    maxmizeButton->setBackgroundReverse(":/resources/max_click.png","png");

    exitButton=new ThreeBackgroundButton(this);
    exitButton->setBackgroundFront(":/resources/power_normal.png","png");
    exitButton->setBackgroundReverse(":/resources/power_click.png","png");
    exitButton->setBackgroundHover(":/resources/power_hover.png","png");

    titleLayout->addWidget(titleButton,0,Qt::AlignLeft|Qt::AlignTop);
    titleLayout->addWidget(minimizeButton,0,Qt::AlignRight);
    titleLayout->addWidget(maxmizeButton);
    titleLayout->addWidget(exitButton);
    titleLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(titleLayout,1);


    QHBoxLayout *funcLayout=new QHBoxLayout();
    pEndMarkButton=new MarkButton(this);
    pEndMarkButton->setBackgroundNormal(":/resources/magnify2.png","png");
    pEndMarkButton->setBackgroundMarked(":/resources/magnify.png","png");
    pStartMarkButton=new MarkButton(this);
    pStartMarkButton->setBackgroundNormal(":/resources/shrink2.png","png");
    pStartMarkButton->setBackgroundMarked(":/resources/shrink.png","png");
    funcLayout->addWidget(pEndMarkButton,Qt::AlignHCenter);
    funcLayout->addWidget(pStartMarkButton,Qt::AlignHCenter);
    funcLayout->setAlignment(mainLayout,Qt::AlignTop);
    funcLayout->setMargin(0);
    mainLayout->addLayout(funcLayout,1);

    QHBoxLayout *logicLayout=new QHBoxLayout();

    QGridLayout *vLayout=new QGridLayout();
    volumeWidget=new myVolumeWidget(this);
    sagitalWidget=new mySlicerWidget(this);
    coronalWidget=new mySlicerWidget(this);
    axialWidget=new mySlicerWidget(this);
    vLayout->addWidget(volumeWidget,0,0);
    vLayout->addWidget(sagitalWidget,0,1);
    vLayout->addWidget(coronalWidget,1,0);
    vLayout->addWidget(axialWidget,1,1);
    QVBoxLayout *oLayout=new QVBoxLayout();
    volumeLoadButton=new BackgroundButton(this);
    volumeLoadButton->setBackground(":/resources/loadVolume.png","png");
    stlLoadButton=new BackgroundButton(this);
    stlLoadButton->setBackground(":/resources/loadStl.png","png");
    stlSelectButton=new BackgroundButton(this);
    stlSelectButton->setBackground(":/resources/selectStl.png","png");
    stlDeleteButton=new BackgroundButton(this);
    stlDeleteButton->setBackground(":/resources/deleteStl.png","png");
    volumeMagnifyButton=new BackgroundButton(this);
    volumeMagnifyButton->setBackground(":/resources/volumeMagnify.png","png");
    volumeMagnifyButton->setClickedColor(QColor(185,188,193,150));
    oLayout->addWidget(volumeLoadButton,0,Qt::AlignTop);
    oLayout->addWidget(stlLoadButton);
    oLayout->addWidget(stlSelectButton);
    oLayout->addWidget(stlDeleteButton);
    oLayout->addWidget(volumeMagnifyButton);
    BackgroundButton *placeHolder=new BackgroundButton(this);
    placeHolder->needClickEffect(false);
    oLayout->addWidget(placeHolder,1,Qt::AlignBottom);
    oLayout->setSpacing(5);
    oLayout->setAlignment(Qt::AlignRight);
    logicLayout->addLayout(vLayout,20);
    logicLayout->addLayout(oLayout,1);
    mainLayout->addLayout(logicLayout,20);

    connect(maxmizeButton,SIGNAL(clicked()),this,SLOT(maxmizeClicked()));
    connect(minimizeButton,SIGNAL(clicked()),this,SLOT(minimizeClicked()));
}

//主窗口更新背景
void MainWindow::update_background(){
    m_background=QPixmap(":/resources/background.jpg", "jpg");
    QBitmap bitmap = m_background.createHeuristicMask();
        setWindowState(Qt::WindowMaximized);
    setFixedSize(m_background.size());
    setMask(bitmap);
    update();
}

//初始化
void MainWindow::init(){
    proSelectButton=new QPushButton(QString::fromLocal8Bit("材质"),this);
    selectProWidget=new SelectPropertyWidget(this);
    titleButton=new BackgroundButton(this);
    minimizeButton=new ThreeBackgroundButton(this);
    maxmizeButton=new ThreeBackgroundButton(this);
    pEndMarkButton=new MarkButton(this);
    pStartMarkButton=new MarkButton(this);
    exitButton=new ThreeBackgroundButton(this);
    volumeLoadButton=new BackgroundButton(this);
    stlLoadButton=new BackgroundButton(this);
    stlSelectButton=new BackgroundButton(this);
    stlDeleteButton=new BackgroundButton(this);
    volumeMagnifyButton=new BackgroundButton(this);
    magnifyButton=new BackgroundButton(this);
    shrinkButton=new BackgroundButton(this);
    volumeWidget=new myVolumeWidget(this);
    sagitalWidget=new mySlicerWidget(this);
    axialWidget=new mySlicerWidget(this);
    coronalWidget=new mySlicerWidget(this);
    stlLoadDialog=new MyDialog();
    stlSelectDialog=new MyDialog();
    stlDeleteDialog=new MyDialog();
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
    progressBar=new ProgressBarWidget(ScreenTools::getComputerScreenWidth()/2,ScreenTools::getComputerScreenHeight()/2,this);

    observer=ProgressObserver::New();
    receive=new ProgressReceive();
    observer->setProgressReceiver(receive);

    proSelectButton->setGeometry(1200,3,60,40);

    titleButton->setBackground(":/resources/title2.png","png");
    titleButton->needClickEffect(false);
    titleButton->setPos(3,3);

    pEndMarkButton->setPos(1000,3);
    pEndMarkButton->setBackgroundNormal(":/resources/magnify2.png","png");
    pEndMarkButton->setBackgroundMarked(":/resources/magnify.png","png");
    pStartMarkButton->setPos(1050,3);
    pStartMarkButton->setBackgroundNormal(":/resources/shrink2.png","png");
    pStartMarkButton->setBackgroundMarked(":/resources/shrink.png","png");

    exitButton->setPos(1531,3);
    exitButton->setBackgroundFront(":/resources/power_normal.png","png");
    exitButton->setBackgroundReverse(":/resources/power_click.png","png");
    exitButton->setBackgroundHover(":/resources/power_hover.png","png");

    volumeLoadButton->setPos(1531,78);
    volumeLoadButton->setBackground(":/resources/loadVolume.png","png");

    stlLoadButton->setPos(1531,147);
    stlLoadButton->setBackground(":/resources/loadStl.png","png");

    stlSelectButton->setPos(1531,216);
    stlSelectButton->setBackground(":/resources/selectStl.png","png");

    stlDeleteButton->setPos(1531,285);
    stlDeleteButton->setBackground(":/resources/deleteStl.png","png");

    volumeMagnifyButton->setPos(1531,372);
    volumeMagnifyButton->setBackground(":/resources/volumeMagnify.png","png");
    volumeMagnifyButton->setClickedColor(QColor(185,188,193,150));

    magnifyButton->setPos(1536,445);
    magnifyButton->setBackground(":/resources/mainMagnify2.png","png");
    magnifyButton->setClickedColor(QColor(185,188,193,150));
    shrinkButton->setPos(1536,501);
    shrinkButton->setBackground(":/resources/mainShrink2.png","png");
    shrinkButton->setClickedColor(QColor(185,188,193,150));

    BackgroundButton *focusButton=new BackgroundButton(this);
    focusButton->setPos(1541,576);
    focusButton->setBackground(":/resources/max_normal.png","png");
    connect(focusButton,SIGNAL(clicked()),this,SLOT(focusButtonClicked()));

    stlLoadDialog->setGeometry(stlLoadButton->getXpos()-100,stlLoadButton->getYpos()+100,200,200);
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

    stlSelectDialog->setGeometry(stlSelectButton->getXpos()-100,stlSelectButton->getYpos()+100,200,200);
    stlSelectDialog->setGridTexts(stlList);
    stlSelectDialog->setHint(QString::fromLocal8Bit("选中你要操作的.stl模型"));

    stlDeleteDialog->setGridTexts(stlList);
    stlDeleteDialog->setGeometry(stlDeleteButton->getXpos()-100,stlDeleteButton->getYpos()+100,200,200);
    stlDeleteDialog->setHint(QString::fromLocal8Bit("选择删除场景中的.stl模型"));

    volumeWidget->setLocation(20,55,735,365);//默认的几何位置

    volumeSlider->setGeometry(20,425,735,20);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0,240);

    sagitalWidget->setLocation(775,55,735,365);
    sagitalSlider->setGeometry(775,425,713,20);
    sagitalLabel->setGeometry(1490,425,18,20);
    sagitalLabel->setText(QString::fromLocal8Bit("0"));
    sagitalLabel->setAlignment(Qt::AlignCenter);
    sagitalSlider->setOrientation(Qt::Horizontal);

    axialWidget->setLocation(775,455,735,365);
    axialSlider->setGeometry(775,830,713,20);
    axialLabel->setGeometry(1490,830,18,20);
    axialLabel->setText(QString::fromLocal8Bit("0"));
    axialLabel->setAlignment(Qt::AlignCenter);
    axialSlider->setOrientation(Qt::Horizontal);

    coronalWidget->setLocation(20,455,735,365);
    coronalSlider->setGeometry(20,830,713,20);
    coronalLabel->setGeometry(735,830,18,20);
    coronalLabel->setText(QString::fromLocal8Bit("0"));
    coronalLabel->setAlignment(Qt::AlignCenter);
    coronalSlider->setOrientation(Qt::Horizontal);

}

//按钮信号连接
void MainWindow::setConnection(){
    //退出按钮点击的信号绑定
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitClicked()));
    //导航按钮的信号绑定
    connect(volumeLoadButton,SIGNAL(clicked()),this,SLOT(volumeLoadClicked()));
    //十字箭头按钮的信号绑定
    connect(volumeMagnifyButton,SIGNAL(clicked()),this,SLOT(volumeMagnifyClicked()));
    //放大按钮点击的信号绑定
    connect(magnifyButton,SIGNAL(clicked()),this,SLOT(magnifyClicked()));
    //缩小按钮点击的信号绑定
    connect(shrinkButton,SIGNAL(clicked()),this,SLOT(shrinkCliked()));

    connect(maxmizeButton,SIGNAL(clicked()),this,SLOT(maxmizeClicked()));
    connect(minimizeButton,SIGNAL(clicked()),this,SLOT(minimizeClicked()));

    //选择材质窗口的调出
    connect(proSelectButton,SIGNAL(released()),selectProWidget,SLOT(disPlaySlot()));

    //交还焦点给主窗口
    connect(volumeWidget,SIGNAL(payBackFocus()),this,SLOT(receiveFocus()));
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
    connect(stlLoadButton,SIGNAL(clicked()),this,SLOT(stlLoadButtonClicked()));
    //绿色按钮2点击的信号绑定
    connect(stlSelectButton,SIGNAL(clicked()),this,SLOT(stlSelectButtonClicked()));
    //删除按钮点击的信号绑定
    connect(stlDeleteButton, SIGNAL(clicked()), this, SLOT(stlDeleteButtonClicked()));
    //加载哪一个.stl模型对话框的信号绑定
    connect(stlLoadDialog, SIGNAL(onItemClicked(QString, int)), this, SLOT(loadStl(QString, int)));
    //选择操作哪一个.stl模型对话框的信号绑定
    connect(stlSelectDialog, SIGNAL(onItemClicked(QString, int)), this, SLOT(selectStl(QString, int)));
    //选择删除哪一个.stl模型对话框的信号绑定
    connect(stlDeleteDialog, SIGNAL(onItemClicked(QString, int)), this, SLOT(deleteStl(QString, int)));
    //加载新的材质时，让volumeSlicer归零
    connect(volumeWidget,SIGNAL(propertyChanged()),this,SLOT(volumeSlicerRetunZero()));
    //加载新的材质时，让选择材质窗口消失
    connect(volumeWidget,SIGNAL(propertyChanged()),selectProWidget,SLOT(disAppear()));

    //选择材质窗口发送材质给体绘制窗口
    connect(selectProWidget,SIGNAL(sendProName(std::string)),volumeWidget,SLOT(SetRenderPropertySlot(std::string)));

    //发送标记信号，播放标记动画
    connect(pEndMarkButton,SIGNAL(marked(bool)),this,SLOT(markedAnimator(bool)));
}


//体绘制窗口下滑动条 拖动触发事件
void MainWindow::vSlicerValueChange(int v){
    double shiftValue= 2 * v / 240.0 - 1;
    volumeWidget->ShiftRenderFunction(shiftValue);
    obtainFocus();
}

//sagital窗口下滑动条 拖动触发事件
void MainWindow::sSlicerValueChange(int v){
    sagitalWidget->setSlicerValue(v);
    sagitalLabel->setText(QString::number(v));
    this->update();
    obtainFocus();
}

//axial窗口下滑动条 拖动触发事件
void MainWindow::aSlicerValueChange(int v){
    axialWidget->setSlicerValue(v);
    axialLabel->setText(QString::number(v));
    this->update();
    obtainFocus();
}

//axial窗口下滑动条 拖动触发事件
void MainWindow::cSlicerValueChange(int v){
    coronalWidget->setSlicerValue(v);
    coronalLabel->setText(QString::number(v));
    this->update();
    obtainFocus();
}

//导航按钮点击
void MainWindow::volumeLoadClicked(){
    onOpenVolumeDir();
    obtainFocus();
}

//点击退出
void MainWindow::exitClicked(){
    //TODO 退出应该弹出窗口请求确认
    QCoreApplication::instance()->quit();
}

//十字交叉按钮
void MainWindow::volumeMagnifyClicked(){
    if(volumeWidget->width()<1000){
        volumeWidget->setLocation(20,55,1490,765);
        volumeSlider->setGeometry(20,830,1490,20);
        coronalSlider->hide();
        coronalLabel->hide();
        axialSlider->hide();
        axialLabel->hide();
    }else{
        volumeWidget->setLocation(20,55,735,365);
        volumeSlider->setGeometry(20,425,735,20);
        coronalSlider->show();
        coronalLabel->show();
        axialSlider->show();
        axialLabel->show();
    }
    volumeWidget->TextUIAdapt();
    volumeWidget->raise();
    update();
    obtainFocus();
}

void MainWindow::maxmizeClicked(){
    obtainFocus();
    if(max){
        this->showNormal();
    }else{
        this->showMaximized();
    }
    max=!max;
}

void MainWindow::minimizeClicked(){
    obtainFocus();
    this->showMinimized();
}

//放大按钮点击
void MainWindow::magnifyClicked(){
    //TODO 我tm也不知道这个按钮设计来干啥的
    obtainFocus();
}

//缩小按钮
void MainWindow::shrinkCliked(){
    //TODO 我tm还是不知道这个按钮设计来干啥的
    obtainFocus();
}

//打开体绘制文件夹
void MainWindow::onOpenVolumeDir(){
    if(volumeWidget->hasVolumeData()){

    }
    QString dirPath=QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("打开体绘制数据存储文件夹"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug()<<dirPath;
    if(dirPath.isEmpty()==true) {
        return;
    }

    /*new thread load --------------------------------------*/
    if(volumeWidget->hasVolumeData()){
        DicomLoader::ReleaseData();
    }
    DicomLoader::ErrorCode (*readerFuncPointer)(std::string ,ProgressObserver::Pointer observer);
    readerFuncPointer=DicomLoader::ReadDicomData;
    threadHelper=new LoadThreadHelper(readerFuncPointer,dirPath,observer,progressBar,this,0);
    threadHelper->startThread();
    return;
    /*new thread load ---------------------------------------*/
}

//主窗口重绘制触发事件，一般发生在窗口切换
void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    obtainFocus();
}

//主窗口键盘事件
void MainWindow::keyPressEvent(QKeyEvent *event){
    Q_UNUSED(event);
    if(!volumeWidget->hasVolumeData()){
        qDebug()<<"noVolumeData";
        return;
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
    if(event->key()==Qt::Key_V){
        canTarger=!canTarger;
    }
    volumeWidget->updateRender();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(this->rect().contains(event->pos())){
        mouseClickPoint=event->pos();
        isMouseHover=true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(isMouseHover){
        isMouseHover=false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if((event->buttons()&Qt::LeftButton)&&isMouseHover){
        //拖动
        move(event->globalPos()-mouseClickPoint);
    }else{
        qDebug()<<"i catch u,little bug";
    }
}

void MainWindow::stlDeleteButtonClicked(){
    if(!volumeWidget->hasVolumeData()){
        return ;
    }
    stlDeleteDialog->show();
    obtainFocus();
}

void MainWindow::deleteStl(QString name, int index){
    stlManager->deleteActor(name,volumeWidget->getRenderer());
}

//绿色按钮1点击事件,弹出对话框，选择要加载的.stl模型
void MainWindow::stlLoadButtonClicked(){
    //弹出对话框，选择要加载的.stl模型
    if (volumeWidget->hasVolumeData()) {
        stlLoadDialog->show();
    }
    obtainFocus();
}

/**
* @brief MainWindow::loadStl
*  体绘制窗口加载.stl模型
* @param name
* 模型名
* @param index
*/
void MainWindow::loadStl(QString name, int index) {
    //默认当前操作的.stl模型为最后加载的那个
    operationStlName = name;
    qDebug() << "MainWindow::loadStl";
    QString dirPath = QDir::currentPath() + "/externalResources/";
    /*根据选择的.stl名加载控件，
    * TODO 这里应该读取配置文件
    */
    switch (index) {
    case 0:
        dirPath += "qx_1.stl";
        break;
    case 1:
        dirPath += "YLQX_A_1.stl";
        break;
    case 2:
        dirPath += "YLQX_B_1.stl";
        break;
    case 3:
        dirPath += "YLQX_C_1.stl";
        break;
    case 4:
        dirPath += "YLQX_D.stl";
        break;
    case 5:
        dirPath += "YLQX_E.stl";
        break;
    case 6:
        dirPath += "body.stl";
    }
    vtkSmartPointer<vtkActor> operationActor = stlManager->LoadStl(dirPath, operationStlName);
    if (operationActor == NULL) {
        return;
    }
    //如果为人体，默认设置了一些颜色和透明度
    //TODO 对.stl模型颜色和透明度的设置应该放在stlManageranager这个类中
    if (index == 6) {
        operationActor->GetProperty()->SetOpacity(0.2);
        operationActor->GetProperty()->SetColor(0.243, 0.5725, 0.843);
    }
    volumeWidget->getRenderer()->AddActor(operationActor);
    volumeWidget->GetRenderWindow()->Render();
}

void MainWindow::selectStl(QString name, int index) {
    operationStlName = name;
}

void MainWindow::stlSelectButtonClicked(){
    if(!volumeWidget->hasVolumeData()){
        return;
    }
    stlSelectDialog->show();
    obtainFocus();
}

void MainWindow::focusButtonClicked(){
    obtainFocus();
}

void MainWindow::obtainFocus(){
    this->setFocus();
}

//体绘制窗口下滑动条归零
void MainWindow::volumeSlicerRetunZero(){
    qDebug()<<"ThreadID："<<QThread::currentThreadId();
    lastposition=120;
    volumeSlider->setValue(120);
}
//当体绘制数据加载完毕
void MainWindow::onDataLoadingDone(){
    qDebug()<<"MainWindow::onDataLoadingDone";
    volumeWidget->loadData(DicomLoader::GetData());
    if(volumeWidget->hasVolumeData()){
        volumeSlider->setValue(120);
        lastposition=120;

        //sagittal为xy方向截面
        sagitalWidget->loadSlicerData(DicomLoader::GetData(),mySlicerWidget::ORIENTATION::XY);
        sagitalWidget->setSlicerValue(sagitalWidget->getSlicerMax()/2);
        sagitalSlider->setRange(sagitalWidget->getSlicerMin(),sagitalWidget->getSlicerMax());
        sagitalSlider->setValue(sagitalWidget->getSlicerMax()/2);
        sagitalLabel->setText(QString::number(sagitalWidget->getSlicerMax()/2));

        //axial为xz截面
        axialWidget->loadSlicerData(DicomLoader::GetData(),mySlicerWidget::ORIENTATION::XZ);
        axialWidget->setSlicerValue(axialWidget->getSlicerMax()/2);
        axialSlider->setRange(axialWidget->getSlicerMin(),axialWidget->getSlicerMax());
        axialSlider->setValue(axialWidget->getSlicerMax()/2);
        axialLabel->setText(QString::number(axialWidget->getSlicerMax()/2));

        //coronal为yz截面
        coronalWidget->loadSlicerData(DicomLoader::GetData(),mySlicerWidget::ORIENTATION::YZ);
        coronalWidget->setSlicerValue(coronalWidget->getSlicerMax()/2);
        coronalSlider->setRange(coronalWidget->getSlicerMin(),coronalWidget->getSlicerMax());
        coronalSlider->setValue(coronalWidget->getSlicerMax()/2);
        coronalLabel->setText(QString::number(coronalWidget->getSlicerMax()/2));

        setDrawConnection();

    }else{
        //TODO  这里提示路径错误
    }
}

//得到子控件退回的焦点
void MainWindow::receiveFocus(){
    obtainFocus();
}

//显示细针、细导丝、双通道导管先后沿着一条线段进入的动画
//目前这条线段的position由设置的固定位置来给出
void MainWindow::markedAnimator(bool marked){
    qDebug()<<"MainWindow::markedAnimator";
    if(!marked){
        return;
    }else{
        stlManager->deleteActor(QString::fromLocal8Bit("step1"),volumeWidget->getRenderer());
        stlManager->deleteActor(QString::fromLocal8Bit("step2"),volumeWidget->getRenderer());
        stlManager->deleteActor(QString::fromLocal8Bit("step3"),volumeWidget->getRenderer());
    }
    double ps[3]={200,200,50};//起点
    double pe[3]={0,0,400};//终点
    vtkSmartPointer<vtkLineSource> lineSource=vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkPoints> points =vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(ps);
    points->InsertNextPoint(pe);
    lineSource->SetPoints(points);
    lineSource->Update();
    vtkSmartPointer<vtkDataSetMapper> line_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    line_mapper->SetInputConnection(lineSource->GetOutputPort());
    vtkSmartPointer<vtkActor> lineActor=vtkSmartPointer<vtkActor>::New();
    lineActor->SetMapper(line_mapper);
    lineActor->GetProperty()->SetColor(0,1,0);
    volumeWidget->getRenderer()->AddActor(lineActor);

    startSurgeryAnimator(ps,pe);
}

void MainWindow::startSurgeryAnimator(double ps[], double pe[]){
    double line[3]={pe[0]-ps[0],pe[1]-ps[1],pe[2]-ps[2]};
    QString dirUPPath = QDir::currentPath() + "/externalResources/";
    vtkSmartPointer<vtkActor> step3=stlManager->LoadStl(dirUPPath+"qx_1.stl",QString::fromLocal8Bit("step3"));

    //y方向单位向量与直线的夹角
    double angle=acos(sqrt(line[1]*line[1])/sqrt(line[0]*line[0]+line[1]*line[1]+line[2]*line[2]))*180/3.1415926;
    //y方向单位向量与直线line所合成平面的法线向量
    double normal[3]={line[1]*0-line[2]*1,
                      line[2]*0-line[0]*0,
                      line[0]*1-line[1]*0,
                     };
    volumeWidget->getRenderer()->AddActor(step3);
    step3->SetPosition(ps);
    step3->RotateWXYZ(angle,normal[0],normal[1],normal[2]);
    volumeWidget->GetRenderWindow()->Render();
    Animator *animator3=new Animator(volumeWidget->GetRenderWindow(),step3,Motion::translate,pe[0],pe[1],pe[2]);
    animator3->setDuration(1000);
    animator3->start();

    qDebug()<<"animator end";
}

