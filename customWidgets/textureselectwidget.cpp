#include "textureselectwidget.h"

TextureSelectWidget::TextureSelectWidget(QWidget *parent):QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout();

    title=new QLabel(QString::fromLocal8Bit("材质"));
    title->setFont(Constant::get12FontSize());
    title->setPalette(Constant::getCommanFontColor());
    title->setStyleSheet(QLABEL_LITTLE_TITLE_STYLE);
    title->setMinimumHeight(Constant::TITLE_MIN_HIGHT);
    title->setMaximumHeight(Constant::TITLE_MIN_HIGHT);

    mainLayout->addWidget(title);

    QHBoxLayout *bottomLayout=new QHBoxLayout();

    putIntoButton=new QPushButton(QString::fromLocal8Bit("应用材质"));
    putIntoButton->setFont(Constant::get12FontSize());
    putIntoButton->setPalette(Constant::getCommanFontColor());
    putIntoButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    putIntoButton->resize(QPUSHBUTTON_LONG_SIZE);
    putIntoButton->setMinimumSize(QPUSHBUTTON_LONG_SIZE);
    putIntoButton->setMaximumSize(QPUSHBUTTON_LONG_SIZE);

    saveButton=new QPushButton(QString::fromLocal8Bit("保存当前材质"));
    saveButton->setFont(Constant::get12FontSize());
    saveButton->setPalette(Constant::getCommanFontColor());
    saveButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    saveButton->resize(QPUSHBUTTON_LONG_SIZE);
    saveButton->setMinimumSize(QPUSHBUTTON_LONG_SIZE);
    saveButton->setMaximumSize(QPUSHBUTTON_LONG_SIZE);

    deleteButton=new QPushButton();
    deleteButton->setFont(Constant::get12FontSize());
    deleteButton->setPalette(Constant::getCommanFontColor());
    deleteButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    deleteButton->resize(QPUSHBUTTON_SHORT_SIZE);
    deleteButton->setMinimumSize(QPUSHBUTTON_SHORT_SIZE);
    deleteButton->setMaximumSize(QPUSHBUTTON_SHORT_SIZE);
    deleteButton->setIcon(QIcon(":/resources/delete.png"));

    bottomLayout->addWidget(putIntoButton);
    bottomLayout->addWidget(saveButton,0,Qt::AlignRight|Qt::AlignVCenter);
    bottomLayout->addWidget(deleteButton);

    mainLayout->addLayout(bottomLayout);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    connect(putIntoButton,SIGNAL(clicked()),this,SLOT(putIntoClicked()));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveClicked()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteClicked()));
}

//应用选中材质按钮点击
void TextureSelectWidget::putIntoClicked(){

}

//保存当前材质按钮点击
void TextureSelectWidget::saveClicked(){

}

//删除按钮点击
void TextureSelectWidget::deleteClicked(){

}
