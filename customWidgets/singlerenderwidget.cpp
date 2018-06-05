#include "singlerenderwidget.h"

SingleRenderWidget::SingleRenderWidget(QString t,QWidget *parent):QWidget(parent)
{
 //   qvtkContentWidget=content;
    tag=t;

    QVBoxLayout *mainLayout=new QVBoxLayout();
    TrapzoidTag *tagIcon=new TrapzoidTag(t);
    mainLayout->addWidget(tagIcon,1);

    QSizePolicy sizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    sizePolicy.setHeightForWidth(1);

    if(tag==QString::fromLocal8Bit("main")){
        qvtkContentWidget=new myVolumeWidget();
    }else{
        qvtkContentWidget=new mySlicerWidget();
    }
    qvtkContentWidget->setSizePolicy(sizePolicy);
    this->setSizePolicy(QSIZEPOLICY_EXPANDING_ALL);
 //   qvtkContentWidget->setMinimumSize(RENDER_WINDOW_MIN_SIZE);
//   qvtkContentWidget->resize(RENDER_WINDOW_MIN_SIZE);
//   qvtkContentWidget->setFixedSize(RENDER_WINDOW_MIN_SIZE);

    qvtkContentWidget->resize(780,330);
    qvtkContentWidget->setFixedSize(780,330);
//    qvtkContentWidget->setFixedSize(RENDER_WINDOW_MIN_SIZE);

    mainLayout->addWidget(qvtkContentWidget,20);

    QHBoxLayout *sliderLayout=new QHBoxLayout();

    BackgroundButton *sliderIcon=new BackgroundButton();
    sliderIcon->setBackground(":/resources/depth.png","png");
    sliderIcon->needClickEffect(false);
    sliderLayout->addWidget(sliderIcon);

    sliderMean=new QLabel();
    if(tag==QString::fromLocal8Bit("main")){
        sliderMean->setText(QString::fromLocal8Bit("Texture"));
    }else{
        sliderMean->setText(QString::fromLocal8Bit("Slice Depth"));
    }
    sliderMean->setStyleSheet(
                "QLabel"
                "{"
                "padding-left:5px;"
                "padding-right:5px;"
                "}"
                );
    sliderMean->setFont(Constant::get12FontSize());
    sliderMean->setPalette(Constant::getCommanFontColor());
    sliderMean->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    sliderLayout->addWidget(sliderMean);

    slider=new QSlider();
    slider->setOrientation(Qt::Horizontal);
    slider->setStyleSheet(
                "QSlider"
                "{"
                "padding-left:5px;"
                "padding-right:5px;"
                "border-color:#bcbcbc;"
                "}"
                "QSlider::groove:horizontal"
                "{"
                "background:#bcb9b9;"
                "boder:1px"
                "hight:5px;"
                "margin-top:0px;"
                "margin-bottom:0px;"
                "margin-left:0px;"
                "margin-right:0px;"
                "padding-left:5px"
                "}"
                "QSlider::handle:horizontal"
                "{"
                "border:9px;"
                "border-image:url(:/resources/sliderHandle.png);"
                "background-image:url(:/resources/sliderHandle.png);"
                "border-radius:9px"
                "margin-top:-9px;"
                "margin-bottom:-9px;"
                "margin-left:-9px;"
                "margin-right:-9px;"
                "}"
                );

    sliderLayout->addWidget(slider);

    sliderNum=new QLabel();
    sliderNum->setText(QString::fromLocal8Bit("      "));
    sliderNum->setAlignment(Qt::AlignVCenter|Qt::AlignVCenter);
    sliderNum->setFont(Constant::get12FontSize());
    sliderNum->setPalette(Constant::getCommanFontColor());
    sliderNum->setStyleSheet(
                "QLabel"
                "{"
                "padding-left:5px;"
                "padding-right:5px;"
                "}"
                );
    sliderLayout->addWidget(sliderNum);

    sliderLayout->setSpacing(5);
    sliderLayout->setContentsMargins(0,9,0,9);

    mainLayout->addLayout(sliderLayout,1);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(onSliderValueChanged(int)));
    connect(this,SIGNAL(sliderValueChanged(int)),qvtkContentWidget,SLOT(onSliderValueChanged(int)));
    if(tag==QString::fromLocal8Bit("main")){
        //材质变换，通知值归零
        connect(qvtkContentWidget,SIGNAL(propertyChanged()),this,SLOT(setSliderValueInit()));
    }
}

SingleRenderWidget::~SingleRenderWidget(){
    if(qvtkContentWidget!=NULL){
        delete qvtkContentWidget;
        qvtkContentWidget=NULL;
    }
}

//返回包含的容器
QVTKWidget* SingleRenderWidget::getContentWidget(){
    return qvtkContentWidget;
}

//设置滑动条范围
void SingleRenderWidget::setSliderRange(int min,int max){
    this->min=min;
    this->max=max;
    slider->setRange(min,max);
}

//设置滑动条值
void SingleRenderWidget::setSliderValue(int value){
    slider->setValue(value);
    QString str;
    QString num=QString::number(value);
    if(value<10){
        str=QString::fromLocal8Bit("  ")+num+QString::fromLocal8Bit(" ");
    }else if(value<100&&value>=10){
        str=QString::fromLocal8Bit(" ")+num+QString::fromLocal8Bit(" ");
    }else if(value>=100){
        str=num;
    }
    str=num;
    sliderNum->setText(str);
}

//滑动条值放置在中心处
void SingleRenderWidget::setSliderValueInit(){
    if(tag==QString::fromLocal8Bit("main")){
        setSliderValue((max-min)/2);
    }
}

//当滑动条值改变的信号
void SingleRenderWidget::onSliderValueChanged(int value){
    emit sliderValueChanged(value);
    QString str(QString::number(100));
    QString num=QString::number(value);
    //字符长度匹配
    if(value<10){
        str=QString::fromLocal8Bit("  ")+num+QString::fromLocal8Bit(" ");
    }else if(value<100&&value>=10){
        str=QString::fromLocal8Bit(" ")+num+QString::fromLocal8Bit(" ");
    }else if(value>=100){
        str=num;
    }
//    while(str.size()>num.size()){
//        qDebug()<<"str size"<<str.size();
//        qDebug()<<"num size"<<num.size();
//        num.insert(0," ");
//    }
//    str=num;
    sliderNum->setText(str);
}

void SingleRenderWidget::loadData(){
    if(tag==QString::fromLocal8Bit("main")){
        (static_cast<myVolumeWidget*>(qvtkContentWidget))->loadData(DicomLoader::GetData());
    }else {
        mySlicerWidget* slicerWidget=   (static_cast<mySlicerWidget*>(qvtkContentWidget));
        if(tag==QString::fromLocal8Bit("sagital")){
            slicerWidget->loadSlicerData(DicomLoader::GetData(),mySlicerWidget::ORIENTATION::XY);
        }else if(tag==QString::fromLocal8Bit("axial")){
            slicerWidget->loadSlicerData(DicomLoader::GetData(),mySlicerWidget::ORIENTATION::XZ);

        }else if(tag==QString::fromLocal8Bit("coronal")){
            slicerWidget->loadSlicerData(DicomLoader::GetData(),mySlicerWidget::ORIENTATION::YZ);
        }
        this->setSliderRange(slicerWidget->getSlicerMin(),slicerWidget->getSlicerMax());
        this->setSliderValue(slicerWidget->getSlicerMax()/2);
    }

}
