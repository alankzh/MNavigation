#include "dirlistitemwidget.h"

DirListItemWidget::DirListItemWidget(int index,QWidget *parent):QWidget(parent)
{
    this->index=index;
    setMinimumHeight(26);
    setMaximumHeight(26);
    setMaximumWidth(200);
    resize(200,26);
    setFixedSize(200,26);
    QGridLayout *mainLayout=new QGridLayout();

    patientName=new QLabel();
    patientName->setFont(Constant::get12FontSize());
    patientName->setPalette(Constant::getCommanFontColor());
    patientName->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    patientName->setMinimumHeight(26);
    patientName->setMaximumHeight(26);
    patientName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    dirSubPath=new QLabel();
    dirSubPath->setFont(Constant::get12FontSize());
    dirSubPath->setPalette(Constant::getLittleFontColor());
    dirSubPath->setStyleSheet(QLABEL_JUST_PADDING_RIGHT_5PX);
    dirSubPath->setMinimumHeight(26);
    dirSubPath->setMaximumHeight(26);
    dirSubPath->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    mainLayout->addWidget(dirSubPath,0,0);
    mainLayout->addWidget(patientName,0,1);


    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);
//    setStyleSheet(
//                "background:#ffffff;"
//                );
}

//装载数据
void DirListItemWidget::loadData(DirBean dirBean){
    qDebug()<<"DirListItemWidget::loadData";
    patientName->setText(dirBean.getName());
    dirSubPath->setText(dirBean.getRealPath());

    patientName->setToolTip(dirBean.getName());
    dirSubPath->setToolTip(dirBean.getRealPath());
}

void DirListItemWidget::showEvent(QShowEvent *event){
    qDebug()<<"DirListItemWidget::showEvent";
    Q_UNUSED(event)
    dirSubPath->resize(this->width()/2,this->height());
    patientName->resize(this->width()/2,this->height());
    QString realPath=dirSubPath->text();
    QString path2=realPath.mid(realPath.lastIndexOf("/"));
    dirSubPath->setText(path2);

    setElidedText(patientName);
    setElidedText(dirSubPath);
}

//外部弹窗改变标识符
void DirListItemWidget::setTagStr(QString name){
    patientName->setText(name);
    setElidedText(patientName);
}

//用省略号代替太长的字符
void DirListItemWidget::setElidedText(QLabel *label)
{
    QFontMetrics fontWidth(label->font());
    QString hint=label->text();
    int width = fontWidth.width(hint);  //计算字符串宽度
    if(width>=label->width()-10)  //当字符串宽度大于标签宽度时(左右间距各5px)
    {
        hint = fontWidth.elidedText(hint,Qt::ElideRight,label->width()-10);  //右部显示省略号
    }
    //并赋值给QLabel
    label->setText(hint);
    label->update();
}

void DirListItemWidget::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event);
    if(event->button()==Qt::LeftButton){
        emit fatherImBePressed(index);
    }
}

//双击
void DirListItemWidget::mouseDoubleClickEvent(QMouseEvent *event){
    Q_UNUSED(event);
    //双击很快，所以不用检测鼠标是否在控件内,所以只查看事件是否是鼠标左键点击
    if(event->button()==Qt::LeftButton){
        emit itemDoubleClicked(index);
    }
}

void DirListItemWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    //当按下时，绘制一层蓝色蒙版
    if(isPressed){
        QPainter painter(this);
        QBrush brush;
        brush.setColor(QColor(8,136,255,150));
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawRect(QRect(0,0,this->width(),this->height()));
    }
}

/**
 * @brief DirListItemWidget::setIndex
 * 尽量不要使用这个方法，因为id应该在初始化时就设置好
 * 如果你使用了这个方法，可能是因为你正在变动列表
 * @param index
 */
void DirListItemWidget::setIndex(int index){
    this->index=index;
}

int DirListItemWidget::getIndex(){
    return index;
}

/**
 * @brief DirListItemWidget::setIsPressed
 * 你的列表父类，恩准你被选中了！
 * 或者收回恩准！
 * @param isPressed
 */
void DirListItemWidget::setIsPressed(bool isPressed){
    this->isPressed=isPressed;
}

bool DirListItemWidget::getIsPressed(){
    return isPressed;
}
