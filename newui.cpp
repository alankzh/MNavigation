#include "newui.h"
#include "CoordinateConverter.h"

NewUi::NewUi(QWidget *parent)
    : QWidget(parent)
{
    Q_UNUSED(parent);

    this->setWindowTitle(QString::fromLocal8Bit("�������������ϵͳ"));
    this->setWindowIcon(QIcon(":/resources/windowIcon.png"));
    init();
    connection();
    setWindowState(Qt::WindowMaximized);
//      resize(1600,880);
    //   setFixedSize(Constant::NORMAL_WIDTH,Constant::NORMAL_HEIGHT);
//        this->setStyleSheet(
//                    "background:#ffffff"
//                    );
    this->setFocus();
}

NewUi::~NewUi()
{
    if(dirListWidget!=NULL){
        delete dirListWidget;
        dirListWidget=NULL;
    }
    if(dicomInfoWidget!=NULL){
        delete dicomInfoWidget;
        dicomInfoWidget=NULL;
    }
    if(drawWidget!=NULL){
        delete drawWidget;
        drawWidget=NULL;
    }
}

void NewUi::init(){
    //������ ����title����(δ����) �������ܰ�ť���� ����ʵ�ֲ���
    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setMargin(0);
    //���ܰ�ť���� �������ֹ����԰�ť
    QHBoxLayout *funcLayout=new QHBoxLayout();
    funcLayout->setMargin(0);
    //ʵ�ֲ��� ���а��������Ϣ���֣��м���Ʋ��֣��ұ߹滮����
    QHBoxLayout *realizeLayout=new QHBoxLayout();
    realizeLayout->setContentsMargins(5,5,5,0);

    //������Ϣ���֣������ļ��б�ؼ����������Ϣ�ؼ�
    QVBoxLayout *informationLayout=new QVBoxLayout();
    informationLayout->setContentsMargins(0,0,0,0);
    informationLayout->setSpacing(5);
    dirListWidget=new DirListWidget();
    //����/usersets/loadHistory.txt �ļ�·���е�json�ַ���
    dirListWidget->loadPath();
    dicomInfoWidget=new DicomInfoWidget();

    informationLayout->addWidget(dirListWidget,0,Qt::AlignLeft|Qt::AlignTop);
    informationLayout->addWidget(dicomInfoWidget,1,Qt::AlignLeft|Qt::AlignTop);
    realizeLayout->addLayout(informationLayout,0);

    //�м���Ʋ���
    drawWidget=new DrawWidget();
    QVBoxLayout *drawLayout=new QVBoxLayout();
    drawLayout->addWidget(drawWidget);
    drawLayout->setContentsMargins(0,0,0,50);
    drawLayout->setAlignment(drawWidget,Qt::AlignTop|Qt::AlignLeft);
    drawWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    realizeLayout->addLayout(drawLayout,200);

    //�Ҳ�滮����
    QVBoxLayout *projectLayout=new QVBoxLayout();
    projectLayout->setSpacing(0);
    projectLayout->setContentsMargins(5,5,5,0);

    operationPlanWidget=new OperationPlanWidget();
    projectLayout->addWidget(operationPlanWidget,0,Qt::AlignRight|Qt::AlignTop);

    textureSelectWidget=new TextureSelectWidget();
    projectLayout->addWidget(textureSelectWidget,1,Qt::AlignLeft|Qt::AlignTop);

    //TODO ��ʱɾ���Ҳ಼��
   // realizeLayout->addLayout(projectLayout,0);


    mainLayout->addLayout(realizeLayout);
    mainLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    this->setLayout(mainLayout);



    progressBar=new ProgressBarWidget(ScreenTools::getComputerScreenWidth()/2,ScreenTools::getComputerScreenHeight()/2,this);
    observer=ProgressObserver::New();
    receive=new ProgressReceive();
    observer->setProgressReceiver(receive);
    this->setFocus();
}

void NewUi::connection(){
    //��ʷ�ļ����б��� �д�����Ϣ�����������ʷ�ļ���
    connect(dirListWidget,SIGNAL(loadThisPathData(QString,QString)),this,SLOT(loadVolumeData(QString,QString)));
    //����������ļ�
    connect(dirListWidget,SIGNAL(showLoadDialog()),this,SLOT(showLoadDialog()));
}

//�Թ̶�·���첽���������������
void NewUi::loadVolumeData(QString name,QString dirPath){
    //�첽��������
    if(DicomLoader::HasData()){
        DicomLoader::ReleaseData();
    }else{
    }
    this->dirPath=dirPath;
    DicomLoader::ErrorCode (*readerFuncPointer)(std::string,ProgressObserver::Pointer observer);
    readerFuncPointer=DicomLoader::ReadDicomData;
    threadHelper=new LoadThreadHelper(readerFuncPointer,dirPath,observer,progressBar,this,0);
    threadHelper->startThread();
}

//�����Ի���ѡ���ļ���
void NewUi::showLoadDialog(){
    QString dirPath=QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("����������ݴ洢�ļ���"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dirPath.isEmpty()==true) {
        return;
    }else{
        loadVolumeData(QString::fromLocal8Bit(""),dirPath);
    }
}

//���ݼ������
void NewUi::onDataLoadingDone(){
    if(DicomLoader::HasData()){
        //����json�ַ������浽�����ļ��У���ʶ��Ϊ��������·��Ϊ�ļ���·��
        dirListWidget->saveDirBean(QString::fromStdString(DicomLoader::GetDataInfo()->patient_name),
                                dirPath,
                                QString::fromStdString(DicomLoader::GetDataInfo()->study_date),
                                QString::fromStdString(DicomLoader::GetDataInfo()->study_time)
                                );
        dicomInfoWidget->setInfo(dirPath);
        drawWidget->loadDataToFourWidget();
        drawWidget->setInfo();
    }
}
