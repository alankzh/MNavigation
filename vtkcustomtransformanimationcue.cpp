#include "vtkcustomtransformanimationcue.h"


void vtkCustomTransformAnimationCue::TickInternal(double currenttime, double deltatime, double clocktime){
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("ss.zzz ");
    qDebug()<<"time:"<<current_date;
    qDebug()<<"currenttime:"<<currenttime;
    qDebug()<<"deltatime:"<<deltatime;
    qDebug()<<"clocktime:"<<clocktime;


    transform->Translate(currenttime*5,0,0);
    this->RenWin->Render();//必须要刷新渲染管线
}
