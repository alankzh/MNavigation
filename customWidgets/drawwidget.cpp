#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent):QWidget(parent)
{
    //    setMaximumWidth(1000);
    //    setMinimumWidth(1000);

//    QSizePolicy sizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    setSizePolicy(sizePolicy);

    QSizePolicy sizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);

    QVBoxLayout *mainLayout=new QVBoxLayout();
    title=new QLabel(QString::fromLocal8Bit("视图"));
    title->setStyleSheet(QLABEL_LITTLE_TITLE_STYLE);
    title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    title->setPalette(Constant::getCommanFontColor());
    title->setFont(Constant::get12FontSize());
    title->setMaximumHeight(26);
    title->setMinimumHeight(26);

    mainLayout->addWidget(title);

    QHBoxLayout *infoLayout=new QHBoxLayout();
    BackgroundButton *iconButton=new BackgroundButton();
    iconButton->setBackground(":/resources/page.png","png");
    iconButton->needClickEffect(false);
    infoLayout->addWidget(iconButton);

    studyID=new QLabel();
    studyID->setFont(Constant::get30FontSize());
    studyID->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    studyID->setPalette(Constant::getDeepFontColor());
    infoLayout->addWidget(studyID);

    patientName=new QLabel();
    patientName->setFont(Constant::get18FontSize());
    patientName->setPalette(Constant::getCommanFontColor());
    patientName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    infoLayout->addWidget(patientName);

    normalSizeButton=new ThreeBackgroundButton();
    normalSizeButton->setBackgroundFront(":/resources/normalSize.png","png");
    normalSizeButton->setBackgroundReverse(":/resources/normalSizeClicked.png","png");
    normalSizeButton->setClickStatus(true);
    infoLayout->addWidget(normalSizeButton);

    blowSizeButton=new ThreeBackgroundButton();
    blowSizeButton->setBackgroundFront(":/resources/blowSize.png","png");
    blowSizeButton->setBackgroundReverse(":/resources/blowSizeClicked.png","png");
    infoLayout->addWidget(blowSizeButton);

    infoLayout->setSpacing(5);
    infoLayout->setContentsMargins(5,10,5,10);
    mainLayout->addLayout(infoLayout);

    QHBoxLayout *firstRowQvtkLayout=new QHBoxLayout();

    volumeWidgetRendow=new SingleRenderWidget(QString::fromLocal8Bit("main"));
    volumeWidgetRendow->setSliderRange(0,240);
    firstRowQvtkLayout->addWidget(volumeWidgetRendow,1);

    sagitalWidgetRendow=new SingleRenderWidget(QString::fromLocal8Bit("sagital"));
    //设定一个初始值，否则会出现 空指针错误
    sagitalWidgetRendow->setSliderRange(0,100);
    firstRowQvtkLayout->addWidget(sagitalWidgetRendow,1);

    firstRowQvtkLayout->setContentsMargins(5,0,5,0);
    firstRowQvtkLayout->setSpacing(10);
    mainLayout->addLayout(firstRowQvtkLayout,1);

    QHBoxLayout *volumeInfoLayout=new QHBoxLayout();

    BackgroundButton *scaleIcon=new BackgroundButton();
    scaleIcon->needClickEffect(false);
    scaleIcon->setBackground(":/resources/scaleSin.png","png");
    volumeInfoLayout->addWidget(scaleIcon);

    QLabel *volumeScalePre=new QLabel(QString::fromLocal8Bit("Scale"));
    volumeScalePre->setFont(Constant::get12FontSize());
    volumeScalePre->setPalette(Constant::getCommanFontColor());
    volumeScalePre->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    volumeScalePre->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    volumeInfoLayout->addWidget(volumeScalePre);

    volumeScale=new QLabel("   ");
    volumeScale->setFont(Constant::get12FontSize());
    volumeScale->setPalette(Constant::getCommanFontColor());
    volumeScale->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    volumeScale->setStyleSheet(
                "QLabel"
                "{"
                "padding-left:5px;"
                "padding-right:25px;"
                "}"
                );
    volumeInfoLayout->addWidget(volumeScale);

    BackgroundButton *rotationIcon=new BackgroundButton();
    rotationIcon->setBackground(":/resources/rotationSin.png","png");
    rotationIcon->needClickEffect(false);

    volumeInfoLayout->addWidget(rotationIcon);

    QLabel *volumeRotationPre=new QLabel(QString::fromLocal8Bit("Rotation"));
    volumeRotationPre->setFont(Constant::get12FontSize());
    volumeRotationPre->setPalette(Constant::getCommanFontColor());
    volumeRotationPre->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    volumeRotationPre->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    volumeInfoLayout->addWidget(volumeRotationPre);

    volumeRotation=new QLabel("   ");
    volumeRotation->setFont(Constant::get12FontSize());
    volumeRotation->setPalette(Constant::getCommanFontColor());
    volumeRotation->setStyleSheet(
                "QLabel"
                "{"
                "padding-left:5px;"
                "}"
                );
    volumeInfoLayout->addWidget(volumeRotation,1);

    volumeInfoLayout->setSpacing(5);
    volumeInfoLayout->setContentsMargins(5,10,5,30);
    mainLayout->addLayout(volumeInfoLayout);

    QHBoxLayout *secondRowQvtkLayout=new QHBoxLayout();

    coronalWidgetRendow=new SingleRenderWidget(QString::fromLocal8Bit("coronal"));
    //初始值，让用户滑着玩，然而没什么卵用
    coronalWidgetRendow->setSliderRange(0,100);
    secondRowQvtkLayout->addWidget(coronalWidgetRendow,1);

    axialWidgetRendow=new SingleRenderWidget(QString::fromLocal8Bit("axial"));
    //初始值，让用户滑着玩，然而没什么卵用
    axialWidgetRendow->setSliderRange(0,100);
    secondRowQvtkLayout->addWidget(axialWidgetRendow,1);

    secondRowQvtkLayout->setContentsMargins(5,0,5,0);
    secondRowQvtkLayout->setSpacing(10);
    mainLayout->addLayout(secondRowQvtkLayout,1);

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    //体绘制窗口回复正常大小
    connect(normalSizeButton,SIGNAL(clicked()),this,SLOT(normalClicked()));
    //体绘制窗口爆炸大小
    connect(blowSizeButton,SIGNAL(clicked()),this,SLOT(blowClicked()));
}

void DrawWidget::normalClicked(){
    changeSize(false);
}
void DrawWidget::blowClicked(){
    changeSize(true);
}
void DrawWidget::changeSize(bool setBlowSize){
    if(setBlowSize){
        normalSizeButton->setClickStatus(false);
        blowSizeButton->setClickStatus(true);
    }else{
        normalSizeButton->setClickStatus(true);
        blowSizeButton->setClickStatus(false);
    }
    if(sizeIsBlow!=setBlowSize){
        emit sizeChanged(setBlowSize);
        sizeIsBlow=setBlowSize;
    }else{

    }
}

//为四个窗口装载数据
void DrawWidget::loadDataToFourWidget(){
    volumeWidgetRendow->loadData();
    volumeWidgetRendow->setSliderValue(120);

    //sagittal为xy方向截面
    sagitalWidgetRendow->loadData();

    //axial为xz截面
    axialWidgetRendow->loadData();

    //coronal为yz截面
    coronalWidgetRendow->loadData();
}

//设置界面数据
void DrawWidget::setInfo(){
    studyID->setText(QString::fromStdString(DicomLoader::GetDataInfo()->study_ID));
    patientName->setText(QString::fromStdString(DicomLoader::GetDataInfo()->patient_name));
}
