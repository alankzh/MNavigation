#include "operationplanwidget.h"

OperationPlanWidget::OperationPlanWidget(QWidget *parent):QWidget(parent)
{
    this->setStyleSheet(
                 "background:#f0f0f0"
                );

    QVBoxLayout *mainLayout=new QVBoxLayout();

    title=new QLabel(QString::fromLocal8Bit("手术方案"));
    title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    title->setStyleSheet(QLABEL_LITTLE_TITLE_STYLE);
    title->setPalette(Constant::getCommanFontColor());
    title->setFont(Constant::get12FontSize());
    title->setMinimumHeight(Constant::TITLE_MIN_HIGHT);

    mainLayout->addWidget(title);

    listView=new MyListView();
    for(int i=0;i<30;i++){
        planStrList.append(QString::fromLocal8Bit("测试用")+QString::number(i));
    }
    listView->loadHistoryDir(planStrList);

    mainLayout->addWidget(listView);

    QHBoxLayout *bottomLayout=new QHBoxLayout();
    playButton=new QPushButton(QString::fromLocal8Bit("播放"));
    playButton->setFont(Constant::get12FontSize());
    playButton->setPalette(Constant::getCommanFontColor());
    playButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    playButton->setIcon(QIcon(":/resources/play.png"));
    playButton->resize(QPUSHBUTTON_ICON_PRE_SIZE);
    playButton->setMinimumSize(QPUSHBUTTON_ICON_PRE_SIZE);
    playButton->setMaximumSize(QPUSHBUTTON_ICON_PRE_SIZE);

    creatButton=new QPushButton(QString::fromLocal8Bit("创建手术方案"));
    creatButton->setFont(Constant::get12FontSize());
    creatButton->setPalette(Constant::getCommanFontColor());
    creatButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    creatButton->resize(QPUSHBUTTON_LONG_SIZE);
    creatButton->setMinimumSize(QPUSHBUTTON_LONG_SIZE);
    creatButton->setMaximumSize(QPUSHBUTTON_LONG_SIZE);

    deleteButton=new QPushButton();
    deleteButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    deleteButton->resize(QPUSHBUTTON_SHORT_SIZE);
    deleteButton->setMinimumSize(QPUSHBUTTON_SHORT_SIZE);
    deleteButton->setMaximumSize(QPUSHBUTTON_SHORT_SIZE);
    deleteButton->setIcon(QIcon(":/resources/delete.png"));

    bottomLayout->setContentsMargins(5,8,5,8);
    bottomLayout->setSpacing(5);
    bottomLayout->addWidget(playButton);

    bottomLayout->addWidget(creatButton,0,Qt::AlignRight|Qt::AlignVCenter);
    bottomLayout->addWidget(deleteButton);

    mainLayout->addLayout(bottomLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);

    connect(playButton,SIGNAL(clicked()),this,SLOT(playClicked()));
    connect(creatButton,SIGNAL(clicked()),this,SLOT(creatClicked()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteClicked()));
}

//播放按钮点击
void OperationPlanWidget::playClicked(){

}

//创建按钮点击
void OperationPlanWidget::creatClicked(){
    //TODO 弹出方案编辑选择框

}

//删除按钮点击
void OperationPlanWidget::deleteClicked(){

}
