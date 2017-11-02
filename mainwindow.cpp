#include "mainwindow.h"
#include "CoordinateConverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(0, Qt::FramelessWindowHint), m_embedded(false)
{
    Q_UNUSED(parent);

    update_background();
    init();


    this->setFocus();
    setLayout();
    setConnection();

    BackgroundButton *titleButton=new BackgroundButton(this);
    titleButton->setBackground(":/resources/title2.png","png");
    titleButton->setGeometry(3,3,334,32);
    titleButton->setPos(3,3);
    titleButton->needClickEffect(false);
}

MainWindow::~MainWindow()
{
}

//主窗口更新背景
void MainWindow::update_background(){
    m_background=QPixmap(":/resources/background2.png", "png");
    QBitmap bitmap = m_background.createHeuristicMask();
    setFixedSize(m_background.size());
    setMask(bitmap);
    update();
}

//初始化
void MainWindow::init(){
    greenButton1=new BackgroundButton(this);
    greenButton2=new BackgroundButton(this);
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
    stlDeleteButton=new BackgroundButton(this);

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
    exitButton->setPos(1531,3);
    exitButton->setBackground(":/resources/power_normal.png","png");
    exitButton->setClickedColor(QColor(95,100,137,150));

    navigationButton->setPos(1531,78);
    navigationButton->setBackground(":/resources/loadVolume.png","png");

    greenButton1->setPos(1531,147);
    greenButton1->setBackground(":/resources/loadStl.png","png");

    greenButton2->setPos(1531,216);
    greenButton2->setBackground(":/resources/selectStl.png","png");

    // stlDeleteButton->setGeometry(730,3,80,43);
    stlDeleteButton->setPos(1531,285);
    //  stlDeleteButton->setText(QString::fromLocal8Bit("删除.stl"));
    stlDeleteButton->setBackground(":/resources/deleteStl.png","png");

    translateButton->setPos(1541,372);
    translateButton->setBackground(":/resources/max_normal.png","png");
    translateButton->setClickedColor(QColor(185,188,193,150));

    magnifyButton->setPos(1536,425);
    magnifyButton->setBackground(":/resources/mainMagnify2.png","png");
    magnifyButton->setClickedColor(QColor(185,188,193,150));
    shrinkButton->setPos(1536,481);
    shrinkButton->setBackground(":/resources/mainShrink2.png","png");
    shrinkButton->setClickedColor(QColor(185,188,193,150));

    BackgroundButton *focusButton=new BackgroundButton(this);
    focusButton->setBackground(":/resources/getFocus.png","png");
    connect(focusButton,SIGNAL(clicked()),this,SLOT(focusButtonClicked()));
    focusButton->setGeometry(1531,556,66,67);
    focusButton->setPos(1531,556);

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

    stlSelectDialog->setGeometry(greenButton2->getXpos()-100,greenButton2->getYpos()+100,200,200);
    stlSelectDialog->setGridTexts(stlList);
    stlSelectDialog->setHint(QString::fromLocal8Bit("选中你要操作的.stl模型"));

    stlDeleteDialog->setGridTexts(stlList);
    stlDeleteDialog->setGeometry(stlDeleteButton->getXpos()-100,stlDeleteButton->getYpos()+100,200,200);
    stlDeleteDialog->setHint(QString::fromLocal8Bit("选择删除场景中的.stl模型"));

    volumeWidget->setLocation(20,55,735,365);//默认的几何位置

    volumeSlider->setGeometry(20,425,735,20);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0,255);

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
    connect(stlDeleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    //加载哪一个.stl模型对话框的信号绑定
    connect(stlLoadDialog, SIGNAL(onItemClicked(QString, int)), this, SLOT(loadStl(QString, int)));
    //选择操作哪一个.stl模型对话框的信号绑定
    connect(stlSelectDialog, SIGNAL(onItemClicked(QString, int)), this, SLOT(selectStl(QString, int)));
    //选择删除哪一个.stl模型对话框的信号绑定
    connect(stlDeleteDialog, SIGNAL(onItemClicked(QString, int)), this, SLOT(deleteStl(QString, int)));
}

//体绘制窗口下滑动条 拖动触发事件
void MainWindow::vSlicerValueChange(int v){
    double shiftValue=double(v-lastposition)/255.0;
    lastposition=v;
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
void MainWindow::navigationClicked(){
    qDebug()<<"MainWindow::navigationClicked";
    onOpenVolumeDir();
    obtainFocus();
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
    obtainFocus();
}

//放大按钮点击
void MainWindow::magnifyClicked(){
    qDebug()<<"MainWindow::magnifyClicked";
    //TODO 我tm也不知道这个按钮设计来干啥的
    obtainFocus();
}

//缩小按钮
void MainWindow::shrinkCliked(){
    qDebug()<<"MainWindow::shrinkCliked";
    //TODO 我tm还是不知道这个按钮设计来干啥的
    obtainFocus();
}

//主窗口重绘制触发事件，一般发生在窗口切换
void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.drawPixmap(e->rect(), m_background, e->rect());
    obtainFocus();
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
        sagitalLabel->setText("100");

        //axial为xz截面
        axialWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::XZ);
        axialWidget->setSlicerValue(140);
        axialSlider->setRange(axialWidget->getSlicerMin(),axialWidget->getSlicerMax());
        axialSlider->setValue(140);
        axialLabel->setText("140");

        //coronal为yz截面
        coronalWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::YZ);
        coronalWidget->setSlicerValue(140);
        coronalSlider->setRange(coronalWidget->getSlicerMin(),coronalWidget->getSlicerMax());
        coronalSlider->setValue(140);
        coronalLabel->setText("140");

        setDrawConnection();

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

void MainWindow::deleteButtonClicked(){
    if(!volumeWidget->hasVolumeData()){
        return ;
    }

    //每次弹出对话框之前更新当前场景中已经加载的.stl模型的标识符有哪些
    //stlDeleteDialog->setGridTexts(stlManager->getActorList());
    stlDeleteDialog->show();
    obtainFocus();
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

void MainWindow::greenButton2Clicked(){
    qDebug()<<"on_greenButton2_clicked";
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
