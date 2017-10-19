#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(0, Qt::FramelessWindowHint), m_embedded(false)
{
    Q_UNUSED(parent);

    update_background();
    init();

    //�����ڽ���
    this->setFocus();
    setLayout();
    setConnection();

    //�����ť�����������ڻ�ȡ����
    QPushButton *textButton1=new QPushButton(this);
    textButton1->setGeometry(1531,434,60,60);
}

MainWindow::~MainWindow()
{
}

//�����ڸ��±���
void MainWindow::update_background(){
    m_background=QPixmap(":/resources/background.jpg", "jpg");
    QBitmap bitmap = m_background.createHeuristicMask();
    setFixedSize(m_background.size());
    setMask(bitmap);
    update();
}

//��ʼ��
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

//����
void MainWindow::setLayout(){
    greenButton1->setPos(1531,55);
    stlLoadDialog->setGeometry(greenButton1->getXpos()-100,greenButton1->getYpos()+100,200,200);

    /**
     *TODO �ⲿ��Ӧ��д�������ļ���������ֱ�Ӽ���
     */
    stlList.append(QString::fromLocal8Bit("˫ͨ������"));
    stlList.append(QString::fromLocal8Bit("��ȫ����1"));
    stlList.append(QString::fromLocal8Bit("��ȫ����2"));
    stlList.append(QString::fromLocal8Bit("Բ��"));
    stlList.append(QString::fromLocal8Bit("ϸ��˿"));
    stlList.append(QString::fromLocal8Bit("ϸ��"));
    stlList.append(QString::fromLocal8Bit("����"));
    stlLoadDialog->setGridTexts(stlList);

    greenButton2->setPos(1531,118);
    stlSelectDialog->setGeometry(greenButton2->getXpos()-100,greenButton2->getYpos()+100,200,200);
    stlSelectDialog->setHint(QString::fromLocal8Bit("ѡ����Ҫ������.stlģ��"));

    navigationButton->setPos(510,3);
    navigationButton->setBackground(":/resources/navigation.png","png");
    stlDeleteButton->setGeometry(730,3,80,43);
    stlDeleteButton->setText(QString::fromLocal8Bit("ɾ��.stl"));
    stlDeleteDialog->setGeometry(stlDeleteButton->x(),stlDeleteButton->y()+150,200,200);
    stlDeleteDialog->setHint(QString::fromLocal8Bit("ѡ��ɾ�������е�.stlģ��"));
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

    volumeWidget->setLocation(20,55,735,365);//Ĭ�ϵļ���λ��
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

//��ť�ź�����
void MainWindow::setConnection(){
    //�˳���ť������źŰ�
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitClicked()));
    //������ť���źŰ�
    connect(navigationButton,SIGNAL(clicked()),this,SLOT(navigationClicked()));
    //ʮ�ּ�ͷ��ť���źŰ�
    connect(translateButton,SIGNAL(clicked()),this,SLOT(translateClicked()));
    //�Ŵ�ť������źŰ�
    connect(magnifyButton,SIGNAL(clicked()),this,SLOT(magnifyClicked()));
    //��С��ť������źŰ�
    connect(shrinkButton,SIGNAL(clicked()),this,SLOT(shrinkCliked()));
}

//�����������ʱ��Ҫ���ӵ��ź�
void MainWindow::setDrawConnection(){
    //����ƴ����»�������ֵ�ı���źŰ�
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(vSlicerValueChange(int)));
    //sagital���洰���»�������ֵ�ı���źŰ�
    connect(sagitalSlider,SIGNAL(valueChanged(int)),this,SLOT(sSlicerValueChange(int)));
    //axial���洰���»�������ֵ�ı���źŰ�
    connect(axialSlider,SIGNAL(valueChanged(int)),this,SLOT(aSlicerValueChange(int)));
    //coronal���洰���»�������ֵ�ı���źŰ�
    connect(coronalSlider,SIGNAL(valueChanged(int)),this,SLOT(cSlicerValueChange(int)));
    //��ɫ��ť1������źŰ�
    connect(greenButton1,SIGNAL(clicked()),this,SLOT(greenButton1Clicked()));
    //��ɫ��ť2������źŰ�
    connect(greenButton2,SIGNAL(clicked()),this,SLOT(greenButton2Clicked()));
    //ɾ����ť������źŰ�
    connect(stlDeleteButton,SIGNAL(clicked()),this,SLOT(deleteButtonClicked()));
    //������һ��.stlģ�ͶԻ�����źŰ�
    connect(stlLoadDialog,SIGNAL(onItemClicked(QString,int)),this,SLOT(loadStl(QString,int)));
    //ѡ�������һ��.stlģ�ͶԻ�����źŰ�
    connect(stlSelectDialog,SIGNAL(onItemClicked(QString,int)),this,SLOT(selectStl(QString,int)));
    //ѡ��ɾ����һ��.stlģ�ͶԻ�����źŰ�
    connect(stlDeleteDialog,SIGNAL(onItemClicked(QString,int)),this,SLOT(deleteStl(QString,int)));
    //����ƴ��ڵ�������������źŰ�
    vtkQtConnect->Connect(volumeWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(volumeWidgetClick(vtkObject*, unsigned long, void*, void*)));
    //sagital���洰�ڵ�������������źŰ�
    vtkQtConnect->Connect(sagitalWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(sagitalWidgetClick(vtkObject*, unsigned long, void*, void*)));
    //axial���洰�ڵ�������������źŰ�
    vtkQtConnect->Connect(axialWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(axialWidgetClick(vtkObject*, unsigned long, void*, void*)));
    //coronal���洰�ڵ�����������ĵ��źŰ�
    vtkQtConnect->Connect(coronalWidget->getQVTKWidget()->GetRenderWindow()->GetInteractor(),vtkCommand::LeftButtonPressEvent,this,SLOT(coronalWidgetClick(vtkObject*, unsigned long, void*, void*)));
}

//����ƴ����»����� �϶������¼�
void MainWindow::vSlicerValueChange(int v){
    double shiftValue=double(v-lastposition)/255.0;
    lastposition=v;
    volumeWidget->settingDefault->ShiftRenderFunction(shiftValue,1);
    volumeWidget->settingDefault->ShiftRenderFunction(shiftValue,2);
    volumeWidget->updateRender();

}
//sagital�����»����� �϶������¼�
void MainWindow::sSlicerValueChange(int v){
    sagitalWidget->setSlicerValue(v);
}
//axial�����»����� �϶������¼�
void MainWindow::aSlicerValueChange(int v){
    axialWidget->setSlicerValue(v);
}
//coronal�����»����� �϶������¼�
void MainWindow::cSlicerValueChange(int v){
    coronalWidget->setSlicerValue(v);
}

//������ť���
void MainWindow::navigationClicked(){
    qDebug()<<"MainWindow::navigationClicked";
    onOpenVolumeDir();
}
//����˳�
void MainWindow::exitClicked(){
    qDebug()<<"MainWindow::exitClicked";
    //TODO �˳�Ӧ�õ�����������ȷ��
    QCoreApplication::instance()->quit();
}
//ʮ�ֽ��水ť
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
//�Ŵ�ť���
void MainWindow::magnifyClicked(){
    qDebug()<<"MainWindow::magnifyClicked";
    //TODO ��tmҲ��֪�������ť�������ɶ��
}
//��С��ť
void MainWindow::shrinkCliked(){
    qDebug()<<"MainWindow::shrinkCliked";
    //TODO ��tm���ǲ�֪�������ť�������ɶ��
}

//�������ػ��ƴ����¼���һ�㷢���ڴ����л�
void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.drawPixmap(e->rect(), m_background, e->rect());
}

//����ƴ��ڵ���¼�
void MainWindow::volumeWidgetClick(vtkObject* obj, unsigned long, void*, void*){

}
//sagital���洰�ڵ���¼�
void MainWindow::sagitalWidgetClick(vtkObject* obj, unsigned long, void*, void*){
    qDebug()<<"MainWindow::sagitalClicked";
    //���������洰���������������Ʊ��
    vtkSmartPointer<vtkImageViewer2> m_sagitalViewer2=sagitalWidget->getImageViewer2();
    vtkSmartPointer<vtkImageViewer2> m_axialViewer2=axialWidget->getImageViewer2();
    vtkSmartPointer<vtkImageViewer2> m_coronalViewer2=coronalWidget->getImageViewer2();
    vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
    int EventPointX = iren->GetEventPosition()[0];
    int EventPointY = iren->GetEventPosition()[1];
    vtkImageActor* Actor = m_sagitalViewer2->GetImageActor();
    vtkRenderer* Renderer= m_sagitalViewer2->GetRenderer();
    /*BEGIN �����������������ת��*/
    double* boundary;
    boundary = Actor->GetBounds();
    int* Size = Renderer->GetSize();
    double ViewEventPointX = (double)EventPointX * 2 / Size[0] - 1;
    double ViewEventPointY = (double)EventPointY * 2 / Size[1] - 1;
    double x = boundary[1];//��
    double y = boundary[3];//��
    double z = boundary[5];//��
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
    /*END �����������ת������*/

    //���� ʮ���߶α��
    if(adjust[0]>0&&adjust[1]>0){
        if(canTarger){
            volumeWidget->getRenderer()->AddActor(actorM->getSphereActor(adjust[0],adjust[1],adjust[2]));

            //sagital�������ʮ�֣�z��߶�һ��
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]+1,adjust[1],350,adjust[0]+10,adjust[1],350));
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],adjust[1]+1,350,adjust[0],adjust[1]+10,350));
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]-1,adjust[1],350,adjust[0]-10,adjust[1],350));
            m_sagitalViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],adjust[1]-1,350,adjust[0],adjust[1]-10,350));

            //axial�������ʮ�֣�y��߶�һ��
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]+1,999,adjust[2],adjust[0]+10,999,adjust[2]));
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],999,adjust[2]+1,adjust[0],999,adjust[2]+10));
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0]-1,999,adjust[2],adjust[0]-10,999,adjust[2]));
            m_axialViewer2->GetRenderer()->AddActor(actorM->getLineActor(adjust[0],999,adjust[2]-1,adjust[0],999,adjust[2]-10));


            //coronal�������ʮ�֣�x��߶�һ��
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1]+1,adjust[2],699,adjust[1]+10,adjust[2]));
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1],adjust[2]+1,699,adjust[1],adjust[2]+10));
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1]-1,adjust[2],699,adjust[1]-10,adjust[2]));
            m_coronalViewer2->GetRenderer()->AddActor(actorM->getLineActor(699,adjust[1],adjust[2]-1,699,adjust[1],adjust[2]-10));

            //��������֮�󣬻��Ƶ�ʮ�ֲ㼶����ȷ��ʾ
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

        //����ַ�����sagital�����x���귢�͸�coronal�������Ƭ��y���귢�͸�axial�������Ƭ
        axialSlider->setValue((int) adjust[1]/proportionY);
        coronalSlider->setValue((int) adjust[0]/proportionX);
        update();
    }else{
        return;
    }
}
//axial���洰�ڵ���¼�
void MainWindow::axialWidgetClick(vtkObject* obj, unsigned long, void*, void*){

}
//coronal���洰�ڵ���¼�
void MainWindow::coronalWidgetClick(vtkObject* obj, unsigned long, void*, void*){

}

//��������ļ���
void MainWindow::onOpenVolumeDir(){
    qDebug()<<"MainWindow::onOpenVolumeDir";
    QString dirPath=QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("����������ݴ洢�ļ���"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug()<<dirPath;
    if(dirPath.isEmpty()==true) {
        qDebug()<<"exit";
        //        QApplication::exit();
        return;
    }else{
        isOpenDir=true;
    }
    //֧�ִ�����·���Ķ�ȡ
    QByteArray ba=dirPath.toLocal8Bit();
    const char *dirPath_str=ba.data();

    volumeWidget->setVolumeData(dirPath_str);
    if(volumeWidget->hasVolumeData()){
        volumeSlider->setValue(120);
        lastposition=120;
        //TODO����������

        //sagittalΪxy�������
        sagitalWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::XY);
        sagitalWidget->setSlicerValue(100);
        sagitalSlider->setRange(sagitalWidget->getSlicerMin(),sagitalWidget->getSlicerMax());
        sagitalSlider->setValue(100);

        //axialΪxz����
        axialWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::XZ);
        axialWidget->setSlicerValue(140);
        axialSlider->setRange(axialWidget->getSlicerMin(),axialWidget->getSlicerMax());
        axialSlider->setValue(140);

        //coronalΪyz����
        coronalWidget->setSlicerData(volumeWidget->dicomReader,mySlicerWidget::ORIENTATION::YZ);
        coronalWidget->setSlicerValue(140);
        coronalSlider->setRange(coronalWidget->getSlicerMin(),coronalWidget->getSlicerMax());
        coronalSlider->setValue(140);

        setDrawConnection();

        //�õ��߽�����������Slice�ı�����ϵ
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
        //TODO  ������ʾ·������
    }

}

//�����ڼ����¼�
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
    /*�任������ʼ*/
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
      *��������Ĺ����Ѿ�����stlLoadDialog�Ի����ѡ���У�
      * Opacity��Color������Ҳ��ֲ�˹�ȥ
      */
//    if(event->key()==Qt::Key_M){
//        //��������
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
    //ÿ�ε����Ի���֮ǰ���µ�ǰ�������Ѿ����ص�.stlģ�͵ı�ʶ������Щ
    stlDeleteDialog->setGridTexts(stlManager->getActorList());
    stlDeleteDialog->show();
}

void MainWindow::deleteStl(QString name, int index){
    //������ڲ�����.stlΪҪɾ���ģ���ô�ÿ�
//    if(operationStlName.compare(name)){
//         operationStlName=NULL;
//    }
    stlManager->deleteActor(name,volumeWidget->getRenderer());
}

//��ɫ��ť1����¼�,�����Ի���ѡ��Ҫ���ص�.stlģ��
void MainWindow::greenButton1Clicked(){
    //�����Ի���ѡ��Ҫ���ص�.stlģ��
    if(volumeWidget->hasVolumeData()){
        stlLoadDialog->show();
    }
}

/**
 * @brief MainWindow::loadStl
 *  ����ƴ��ڼ���.stlģ��
 * @param name
 * ģ����
 * @param index
 */
void MainWindow::loadStl(QString name, int index){
    //Ĭ�ϵ�ǰ������.stlģ��Ϊ�����ص��Ǹ�
    operationStlName=name;

    QString dirPath=QDir::currentPath()+"/externalResources/";
    /*����ѡ���.stl�����ؿؼ���
     * TODO ����Ӧ�ö�ȡ�����ļ�
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
    //���Ϊ���壬Ĭ��������һЩ��ɫ��͸����
    //TODO ��.stlģ����ɫ��͸���ȵ�����Ӧ�÷���stlManageranager�������
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

//��ɫ��ť2����¼��������Ի���ѡ����Ҫ������.stlģ��
void MainWindow::greenButton2Clicked(){
    qDebug()<<"on_greenButton2_clicked";
    if(!volumeWidget->hasVolumeData()){
        return;
    }
    //ÿ�ε����Ի���֮ǰ���µ�ǰ�������Ѿ����ص�.stlģ�͵ı�ʶ������Щ
    stlSelectDialog->setGridTexts(stlManager->getActorList());
    stlSelectDialog->show();

    /*  ���´���Ϊ�ϰ汾��ɫ��ť2���ܣ�����һ���Զ���Ķ���
    vtkSmartPointer<vtkRenderWindow> renWin =volumeWidget->getQVTKWidget()->GetRenderWindow();
    vtkSmartPointer<vtkRenderer> m_pRenderer=volumeWidget->getRenderer();
    //    vtkSmartPointer<vtkRenderWindowInteractor> iren =vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //   vtkSmartPointer<vtkInteractorStyleTrackballCamera> style=vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //   iren->SetInteractorStyle(style);

    //  renWin->AddRenderer(m_pRenderer);
    //  iren->SetRenderWindow(renWin);
    vtkSmartPointer<vtkSphereSource> sphere =vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(0,0,0);   // ��������
    sphere->SetRadius(10);             // ���ð뾶
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


    /*���´���Ϊ�ֶ�����С�򣬲����ݵ�������ƶ�
    if(clickTimes>0){
        qDebug()<<"clickTimes:"<<clickTimes;
        qDebug()<<"actors:"<<m_pRenderer->GetActors()->GetNumberOfItems();
       m_pRenderer->RemoveActor(actor);
    }
    clickTimes++;
    vtkSmartPointer<vtkSphereSource> sphere =vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(clickTimes*20,0,0);   // ��������
    sphere->SetRadius(10);             // ���ð뾶
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
