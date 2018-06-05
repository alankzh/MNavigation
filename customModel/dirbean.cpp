#include "dirbean.h"

DirBean::DirBean(){
}

DirBean::DirBean(QString name, QString realPath,QString studyDate,QString studyTime){
    this->name=name;
    this->realPath=realPath;
    this->studyDate=studyDate;
    this->studyTime=studyTime;
}

void DirBean::setName(QString name){
    this->name=name;
}

QString DirBean::getName(){
    return this->name;
}

void DirBean::setRealPath(QString realPath){
    this->realPath=realPath;
}

QString DirBean::getRealPath(){
    return this->realPath;
}

void DirBean::setStudyDate(QString studyDate){
    this->studyDate=studyDate;
}

QString DirBean::getStudyDate(){
    return studyDate;
}

void DirBean::setStudyTime(QString studyTime){
    this->studyTime=studyTime;
}

QString DirBean::getStudyTime(){
    return studyTime;
}
