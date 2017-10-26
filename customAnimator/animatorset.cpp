#include "animatorset.h"

AnimatorSet::AnimatorSet()
{
    animationCue=vtkSmartPointer<MyVtkCustomAnimationCue>::New();
    animationCue->SetTimeModeToNormalized();
    animationCue->SetStartTime(0);
    animationCue->SetEndTime(1.0);
}

AnimatorSet::~AnimatorSet(){

}

void AnimatorSet::setDuration(double d){
    duration=d;
    animationScene=vtkSmartPointer<vtkAnimationScene>::New();
    animationScene->SetTimeModeToRelative();
    animationScene->SetPlayMode(vtkAnimationScene::PLAYMODE_REALTIME);
    animationScene->SetStartTime(0);
    animationScene->SetEndTime(d/1000);
}

void AnimatorSet::addAnimator(Animator *animator){
    if(animator->getDuration()!=0){
      qDebug()<<"has duration single animator can add animatorSet";
    }
    animationCue->addMotion(animator->getMotion());
    animationCue->RenWin=animator->getRenderWindow();
}

void AnimatorSet::start(){
    if(animationScene!=NULL){
        animationCue->setOnAnimationFinishListener(this);
        animationScene->AddCue(animationCue);
        animationScene->Play();
        animationScene->Stop();
    }
}

void AnimatorSet::onAnimatorFinish(){
    qDebug()<<"AnimatorSet::onAnimatorFinish";
}
