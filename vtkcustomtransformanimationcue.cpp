#include "vtkcustomtransformanimationcue.h"


void vtkCustomTransformAnimationCue::TickInternal(double currenttime, double deltatime, double clocktime){
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("ss.zzz ");
    qDebug()<<"time:"<<current_date;
    qDebug()<<"currenttime:"<<currenttime;
    qDebug()<<"deltatime:"<<deltatime;
    qDebug()<<"clocktime:"<<clocktime;
    //  double new_st = currenttime * 180;
    // since the cue is in normalizedmode, the currenttime will be in the
    // range[0,1], where 0 is start ofthe cue and 1 is end of the cue.
    //  this->Sphere->SetStartTheta(new_st);
    transform->Translate(currenttime*5,0,0);
    this->RenWin->Render();//必须要刷新渲染管线
}
