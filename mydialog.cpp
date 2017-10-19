#include "mydialog.h"

MyDialog::MyDialog(QWidget *parent):QDialog(parent)
{
    vLayout=new QVBoxLayout();

    myGrid=new MyGridLayout();
    hint=new QLabel(QString::fromLocal8Bit("��ѡ�����.stlģ��"));
    hint->setAlignment(Qt::AlignTop);
    vLayout->addWidget(hint);
    vLayout->addLayout(myGrid);

    QPushButton *closeButton=new QPushButton(QString::fromLocal8Bit("ȡ��"));
    vLayout->addWidget(closeButton);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(activeQuit()));
    setWindowFlags(Qt::CustomizeWindowHint);
    setLayout(vLayout);

    setMaximumHeight(200);
    setMaximumWidth(200);
    //����Ϊ������������������ڵ��¼��޷�����(��ť�޷������)
    setModal(true);
}

/**
 * @brief MyDialog::mouseReleaseEvent
 * ���gridLayout�����ڵİ�ť�ᷢ���¼�onItemClicked
 * @param event
 */
void MyDialog::mouseReleaseEvent(QMouseEvent *event){
    int x=event->pos().x()-myGrid->getXPos();
    int y=event->pos().y()-myGrid->getYPos();
    int width=myGrid->getWidth();
    int height=myGrid->getHeight();
    int columnCount=myGrid->getColumnCount();
    int rowCount=myGrid->getRowCount();

    //���0�������ݵ������
    if(rowCount==0){
        return ;
    }
    //�¼������Ƿ���gridLayout������
    if(x >= 0 && x <= width && y >= 0 && y <= height){
        //������,0��ͷ
        int column=x/(width/columnCount);
        //�����У�0��ͷ
        int row=y/(height/rowCount);

        //�ж��Ƿ������ǰ�ť�������һ��ֻ��һ����ť�������һ�е����״���������ᷢ�͵���ź�
        QString buttonName=myGrid->getItemName(row,column);
        if(buttonName!=NULL){
            //���͵���ź�
            qDebug()<<"emit!!!"<<"  buttonName:"<<buttonName<<"  row:"<<row<<"  column"<<column;
            int index=row*columnCount+column;
            emit this->onItemClicked(buttonName,index);
            this->close();
        }
    }
    update();
}

/**
 * @brief MyDialog::showEvent
 * ��showEvent�¼�������ʱ���ؼ�����ȷ�ߴ����ڵõ�����
 * @param event
 */
void MyDialog::showEvent(QShowEvent *event){
    myGrid->updateGeometry();
}

/**
 * @brief MyDialog::setGridTexts
 * ��������ť������
 * @param list
 */
void MyDialog::setGridTexts(QList<QString> list){
  //  myGrid->setTexts(list);
    myGrid->setTexts(list);
}

/**
 * @brief MyDialog::setLocation
 * setGeometry������������MyDialog�����꣬�����װһ�㣬�Ա��������ܵĲ���
 * TODO ������������Ƿ���Ҫɾ��
 * @param x
 * @param y
 * @param w
 * @param h
 */
void MyDialog::setLocation(int x, int y, int w, int h){
    setGeometry(x,y,w,h);
}

void MyDialog::setHint(QString str){
    hint->setText(str);
}

void MyDialog::activeQuit(){
    this->close();
}
