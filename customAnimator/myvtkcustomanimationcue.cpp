#include "myvtkcustomanimationcue.h"


void MyVtkCustomAnimationCue::TickInternal(double currenttime, double deltatime, double clocktime){
    for(int i=0,j=motionList.size();i<j;i++){
        motionList.at(i)->onAnimationUpdate(currenttime,deltatime,clocktime);
    }
    RenWin->Render();//必须要刷新渲染管线
}


void MyVtkCustomAnimationCue::addMotion(Motion *motion){
    motionList.append(motion);
}

void MyVtkCustomAnimationCue::removeMotion(Motion *motion){
    if(motionList.contains(motion)){
        motionList.removeAt(motionList.indexOf(motion));
    }
}

//动画的结束消息由最后一个元操作发出信号表达
void MyVtkCustomAnimationCue::setOnAnimationFinishListener(AnimatorFinishListener *listener){
    if(motionList.size()>0){
        motionList.at(motionList.size()-1)->setOnAnimationFinishListener(listener);
    }
}
