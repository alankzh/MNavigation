#include "newui.h"
#include "CoordinateConverter.h"

NewUi::NewUi(QWidget *parent)
    : QWidget(parent)
{
    Q_UNUSED(parent);

    this->setWindowTitle(QString::fromLocal8Bit("豆町脊柱手术导航系统"));
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
    //主布局 包括title布局(未定义) 包括功能按钮布局 包括实现布局
    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setMargin(0);
    //功能按钮布局 包括各种功能性按钮
    QHBoxLayout *funcLayout=new QHBoxLayout();
    funcLayout->setMargin(0);
    //实现布局 其中包括左边信息布局，中间绘制布局，右边规划布局
    QHBoxLayout *realizeLayout=new QHBoxLayout();
    realizeLayout->setContentsMargins(5,5,5,0);

    //左侧的信息布局，包括文件列表控件，体绘制信息控件
    QVBoxLayout *informationLayout=new QVBoxLayout();
    informationLayout->setContentsMargins(0,0,0,0);
    informationLayout->setSpacing(5);
    dirListWidget=new DirListWidget();
    //加载/usersets/loadHistory.txt 文件路径中的json字符串
    dirListWidget->loadPath();
    dicomInfoWidget=new DicomInfoWidget();

    informationLayout->addWidget(dirListWidget,0,Qt::AlignLeft|Qt::AlignTop);
    informationLayout->addWidget(dicomInfoWidget,1,Qt::AlignLeft|Qt::AlignTop);
    realizeLayout->addLayout(informationLayout,0);

    //中间绘制布局
    drawWidget=new DrawWidget();
    QVBoxLayout *drawLayout=new QVBoxLayout();
    drawLayout->addWidget(drawWidget);
    drawLayout->setContentsMargins(0,0,0,50);
    drawLayout->setAlignment(drawWidget,Qt::AlignTop|Qt::AlignLeft);
    drawWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    realizeLayout->addLayout(drawLayout,200);

    //右侧规划布局
    QVBoxLayout *projectLayout=new QVBoxLayout();
    projectLayout->setSpacing(0);
    projectLayout->setContentsMargins(5,5,5,0);

    operationPlanWidget=new OperationPlanWidget();
    projectLayout->addWidget(operationPlanWidget,0,Qt::AlignRight|Qt::AlignTop);

    textureSelectWidget=new TextureSelectWidget();
    projectLayout->addWidget(textureSelectWidget,1,Qt::AlignLeft|Qt::AlignTop);

    //TODO 暂时删掉右侧布局
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
    //历史文件夹列表窗口 中传来消息，请求加载历史文件夹
    connect(dirListWidget,SIGNAL(loadThisPathData(QString,QString)),this,SLOT(loadVolumeData(QString,QString)));
    //请求加载新文件
    connect(dirListWidget,SIGNAL(showLoadDialog()),this,SLOT(showLoadDialog()));
}

//以固定路径异步加载新体绘制数据
void NewUi::loadVolumeData(QString name,QString dirPath){
    //异步加载数据
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

//弹出对话框选择文件夹
void NewUi::showLoadDialog(){
    QString dirPath=QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("打开体绘制数据存储文件夹"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dirPath.isEmpty()==true) {
        return;
    }else{
        loadVolumeData(QString::fromLocal8Bit(""),dirPath);
    }
}

//数据加载完毕
void NewUi::onDataLoadingDone(){
    if(DicomLoader::HasData()){
        //生成json字符串保存到本地文件中，标识名为病人名，路径为文件夹路径
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
