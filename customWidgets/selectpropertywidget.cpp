#include "selectpropertywidget.h"

SelectPropertyWidget::SelectPropertyWidget(QWidget *parent):QWidget(parent)
{
    this->parent=parent;
    QVBoxLayout *layout=new QVBoxLayout();
    QPushButton *quitButton=new QPushButton(QString::fromLocal8Bit("close"));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(disAppear()));
    groupBox=new QGroupBox(QString::fromLocal8Bit("Ñ¡Ôñ²ÄÖÊ"));
    boxLayout=new QVBoxLayout();
    layout->addWidget(groupBox);
    layout->addWidget(quitButton);
    setLayout(layout);
    setWindowFlags(Qt::SplashScreen);
    setWindowModality(Qt::WindowModal);
}

void SelectPropertyWidget::disPlaySlot(){
    disPlay();
}

void SelectPropertyWidget::disPlay(){
    QPoint pos=parent->pos();
    move(pos.x()+1200,pos.y()+46);
    loadProperty();
    show();
}

void SelectPropertyWidget::loadProperty(){
    if(boxLayout->count()!=0){
        removeWidget();
    }
    std::vector<std::string> pSets=RenderPropertyGenerator::GetAllAvaiblePresetsName();
    for(std::string str:pSets){
        EmitButton *button=new EmitButton(QString::fromStdString(str));
        connect(button,SIGNAL(sendText(QString)),this,SLOT(setPro(QString)));
        boxLayout->addWidget(button);
    }
    if(groupBox->layout()!=NULL){
    }else{
       groupBox->setLayout(boxLayout);
    }
}

void SelectPropertyWidget::removeWidget(){
    int count=boxLayout->layout()->count();
    qDebug()<<"cout:"<<count;
    for(int i=count-1;i>=0;i--){
    QLayoutItem *item=boxLayout->layout()->takeAt(i);
        if(item->widget()){
       //     boxLayout->removeWidget(item);
            delete item->widget();
        }
    }
}

void SelectPropertyWidget::disAppear(){
    this->close();
}

void SelectPropertyWidget::setPro(QString proName){
    emit sendProName(proName.toStdString());
}
