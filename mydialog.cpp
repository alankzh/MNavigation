#include "mydialog.h"

MyDialog::MyDialog(QWidget *parent):QDialog(parent)
{
    vLayout=new QVBoxLayout();

    myGrid=new MyGridLayout();
    hint=new QLabel(QString::fromLocal8Bit(“选择要导入的模型”);
    hint->setAlignment(Qt::AlignTop);
    vLayout->addWidget(hint);
    vLayout->addLayout(myGrid);

    QPushButton *closeButton=new QPushButton(QString::fromLocal8Bit("取消"));
    vLayout->addWidget(closeButton);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(activeQuit()));
    setWindowFlags(Qt::CustomizeWindowHint);
    setLayout(vLayout);

    setMaximumSize(200,200);
    setMinimumSize(200,200);
    
    setModal(true);
}


void MyDialog::mouseReleaseEvent(QMouseEvent *event){
    int x=event->pos().x()-myGrid->getXPos();
    int y=event->pos().y()-myGrid->getYPos();
    int width=myGrid->getWidth();
    int height=myGrid->getHeight();
    int columnCount=myGrid->getColumnCount();
    int rowCount=myGrid->getRowCount();

    
    if(rowCount==0){
        return ;
    }
    
    if(x >= 0 && x <= width && y >= 0 && y <= height){
       
        int column=x/(width/columnCount);
        
        int row=y/(height/rowCount);

        QString buttonName=myGrid->getItemName(row,column);
        if(buttonName!=NULL){
            
            qDebug()<<"emit!!!"<<"  buttonName:"<<buttonName<<"  row:"<<row<<"  column"<<column;
            int index=row*columnCount+column;
            emit this->onItemClicked(buttonName,index);
            this->close();
        }
    }
    update();
}


void MyDialog::showEvent(QShowEvent *event){
    myGrid->updateGeometry();
}


void MyDialog::setGridTexts(QList<QString> list){
  //  myGrid->setTexts(list);
    myGrid->setTexts(list);
    update();
}


void MyDialog::setLocation(int x, int y, int w, int h){
    setGeometry(x,y,w,h);
}

void MyDialog::setHint(QString str){
    hint->setText(str);
}

void MyDialog::activeQuit(){
    this->close();
}

