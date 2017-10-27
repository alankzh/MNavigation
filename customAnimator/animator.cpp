#include "animator.h"


Animator::Animator(vtkSmartPointer<vtkRenderWindow> r,vtkSmartPointer<vtkActor> actor_p,Motion::MOTIONS f,double angle_p,double x,double y,double z){
    actor=actor_p;
    beginMatrix4x4=actor_p->GetMatrix();
    init();
    motion=new Motion(actor_p,f);
    motion->setOnAnimationFinishListener(this);
    motion->setEndAngle(angle_p);
    motion->setRotationAxis(x,y,z);
    animationCue->addMotion(motion);
    this->renWin=r;
}

Animator::Animator(vtkSmartPointer<vtkRenderWindow> r,vtkSmartPointer<vtkActor> actor_p,Motion::MOTIONS f,double x=0,double y=0,double z=0){
    actor=actor_p;
    beginMatrix4x4=actor_p->GetMatrix();
    init();
    motion=new Motion(actor_p,f);
    motion->setOnAnimationFinishListener(this);
    motion->setEndPosition(x,y,z);
    animationCue->addMotion(motion);
    this->renWin=r;
}

Animator::Animator(vtkSmartPointer<vtkRenderWindow> r,vtkSmartPointer<vtkActor> actor_p,Motion::MOTIONS f,double angle){
    actor=actor_p;
    beginMatrix4x4=actor_p->GetMatrix();
    init();
    motion=new Motion(actor_p,f);
    motion->setOnAnimationFinishListener(this);
    motion->setEndAngle(angle);
    animationCue->addMotion(motion);
    this->renWin=r;
}

void Animator::init(){
    animationCue=vtkSmartPointer<MyVtkCustomAnimationCue>::New();
    animationCue->SetTimeModeToNormalized();
    animationCue->SetStartTime(0);
    animationCue->SetEndTime(1.0);
    animationCue->RenWin=getRenderWindow();
}

Animator::~Animator(){
    if(motion!=NULL){
        delete motion;
        motion=NULL;
    }
}

vtkSmartPointer<vtkRenderWindow> Animator::getRenderWindow(){
    return renWin;
}

void Animator::start(){
    if(animationScene!=NULL){
        qDebug()<<"beginMatrix4x4:";
        outMatrix4x4(beginMatrix4x4);
        animationScene->Play();
        animationScene->Stop();
    }
}

//�������ó���ʱ��ʱ����ʾ����һ����һ����,������һ��animatorSet�е�����
void Animator::setDuration(double d){
    animationScene=vtkSmartPointer<vtkAnimationScene>::New();
    //����ʱ��Ϊ��ʵʱ�䣬֡����ÿһ֡��Ⱦ����ʱ�䲻ͬ����ͬ
    animationScene->SetTimeModeToRelative();
    animationScene->SetPlayMode(vtkAnimationScene::PLAYMODE_REALTIME);
    animationScene->SetStartTime(0);
    duration=d;
    animationScene->SetEndTime(d/1000);
    animationScene->AddCue(animationCue);
}

double Animator::getDuration(){
    return duration;
}

Motion* Animator::getMotion(){
    return motion;
}

//��������
void Animator::onAnimatorFinish(){
    qDebug()<<"endMatrix4x4:";
    endMatrix4x4=actor->GetMatrix();
    outMatrix4x4(endMatrix4x4);
}

void Animator::outMatrix4x4(vtkSmartPointer<vtkMatrix4x4> m){
    for(int i=0;i<4;i++){
        double d[4]={};
        for(int j=0;j<4;j++){
            d[j]=m->GetElement(i,j);
        }
        qDebug()<<"{"<<d[0]<<","<<d[1]<<","<<d[2]<<","<<d[3]<<"}";
    }
}
