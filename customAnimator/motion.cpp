#include "motion.h"

//基本操作单元
Motion::Motion(vtkSmartPointer<vtkActor> a,Motion::MOTIONS f)
{
    actor=a;
    actor->GetPosition(beginPosition);
    actor->GetScale(beginScale);
    flag=f;
    lastA=0;
}
Motion::~Motion(){
    if(listener!=NULL){
        //监听着动画结束的对象，往往是这个motion的持有者，故不必去删除自己的持有者
        //  delete listener;
    }
}

void Motion::setOnAnimationFinishListener(AnimatorFinishListener *listener){
    this->listener=listener;
}

void Motion::setEndAngle(double a){
    this->angle=a;
}

void Motion::setRotationAxis(double x, double y, double z){
    this->axis[0]=x;
    this->axis[1]=y;
    this->axis[2]=z;
}

void Motion::setEndPosition(double x, double y, double z){
    this->x=x;
    this->y=y;
    this->z=z;
}

void Motion::onAnimationUpdate(double currenttime, double deltatime, double clocktime){
    // onTranformArithmetic();
    //TODO
    //检验结束的方法是 当前时间+上一帧的时间大于1的话说明不会有下一帧，判断结束
    //这样做的错误是   用上一帧的时间替代了当前帧
    //导致 1.  提前结束，但他还有下一帧
    //    2.  没有判断到结束，他已经没有下一帧了，但是currenttime+deltatime是小于1的
    //这里加了一个校准值0.02，先保证不出画面上的大纰漏
    //后面重写动画系统时，这里需要注意
    if(currenttime+deltatime>1-0.02){
        switch(flag){
        case translate:
            linearMotion(x,y,z);
            break;
        case scale:
            scaleMotion(x,y,z);
            break;
        case rotate:
            rotateMotion((this->angle)-lastA,axis[0],axis[1],axis[2]);
            lastA=(this->angle)*currenttime;
            break;
        case rotateX:
            rotateXMotion((this->angle)-lastA);
            lastA=(this->angle)*currenttime;
            break;
        case rotateY:
            rotateYMotion((this->angle)-lastA);
            lastA=(this->angle)*currenttime;
            break;
        case rotateZ:
            rotateZMotion((this->angle)-lastA);
            lastA=(this->angle)*currenttime;
            break;
        }
        if(listener!=NULL){
            //动画结束，发送消息
            listener->onAnimatorFinish();
        }
        //非最后一帧
    }else{
        switch(flag){
        case translate:
            linearMotion(beginPosition[0]+(x-beginPosition[0])*currenttime,
                    beginPosition[1]+(y-beginPosition[1])*currenttime,
                    beginPosition[2]+(z-beginPosition[2])*currenttime);
            break;
        case scale:
            scaleMotion(beginScale[0]+(x-beginScale[0])*currenttime,
                    beginScale[1]+(y-beginScale[1])*currenttime,
                    beginScale[2]+(z-beginScale[2])*currenttime);
            break;
        case rotate:
            rotateMotion((this->angle)*currenttime-lastA,axis[0],axis[1],axis[2]);
            lastA=(this->angle)*currenttime;
            break;
        case rotateX:
            rotateXMotion((this->angle)*currenttime-lastA);
            lastA=(this->angle)*currenttime;
            break;
        case rotateY:
            rotateYMotion((this->angle)*currenttime-lastA);
            lastA=(this->angle)*currenttime;
            break;
        case rotateZ:
            rotateZMotion((this->angle)*currenttime-lastA);
            lastA=(this->angle)*currenttime;
            break;
        }
    }
}

void Motion::onTranformArithmetic(){
    //    qDebug()<<"currenttime"<<currenttime;
    //    double a=0;
    //    double x=0;
    //    double y=0;
    //    double z=0;
    //    //最后一帧
    //    if(currenttime+deltatime>1){
    //        switch(flag){
    //        case translate:
    //            x=(this->x)-lastX;
    //            y=(this->y)-lastY;
    //            z=(this->z)-lastZ;
    //            lastX=(this->x);
    //            lastY=(this->y);
    //            lastZ=(this->z);
    //            linearMotion(x,y,z);
    //            break;
    //        case scale:
    //            //TODO
    //            x=(1+(this->x-1))/lastX;
    //            y=(1+(this->y-1))/lastY;
    //            z=(1+(this->z-1))/lastZ;
    //            lastX=(1+(this->x-1));
    //            lastY=(1+(this->y-1));
    //            lastZ=(1+(this->y-1));
    //            scaleMotion(x,y,z);
    //            break;
    //        case rotate:
    //            a=(this->angle)-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateMotion(a,this->x,this->y,this->z);
    //            break;
    //        case rotateX:
    //            a=(this->angle)-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateXMotion(a);
    //            break;
    //        case rotateY:
    //            a=(this->angle)-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateYMotion(a);
    //            break;
    //        case rotateZ:
    //            a=(this->angle)-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateZMotion(a);
    //            break;
    //        }
    //        if(listener!=NULL){
    //            //动画结束，发送消息
    //            listener->onAnimatorFinish();
    //        }
    //        //非最后一帧
    //    }else{
    //        switch(flag){
    //        case translate:
    //            x=(this->x)*currenttime-lastX;
    //            y=(this->y)*currenttime-lastY;
    //            z=(this->z)*currenttime-lastZ;
    //            lastX=(this->x)*currenttime;
    //            lastY=(this->y)*currenttime;
    //            lastZ=(this->z)*currenttime;
    //            linearMotion(x,y,z);
    //            break;
    //        case scale:
    //            if(lastX==0){
    //                lastX=1;
    //                lastY=1;
    //                lastZ=1;
    //            }
    //            x=(1+(this->x-1)*currenttime)/lastX;
    //            y=(1+(this->y-1)*currenttime)/lastY;
    //            z=(1+(this->z-1)*currenttime)/lastZ;
    //            lastX=(1+(this->x-1)*currenttime);
    //            lastY=(1+(this->y-1)*currenttime);
    //            lastZ=(1+(this->y-1)*currenttime);
    //            scaleMotion(x,y,z);
    //            break;
    //        case rotate:
    //            a=(this->angle)*currenttime-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateMotion(a,this->x,this->y,this->z);
    //            break;
    //        case rotateX:
    //            a=(this->angle)*currenttime-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateXMotion(a);
    //            break;
    //        case rotateY:
    //            a=(this->angle)*currenttime-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateYMotion(a);
    //            break;
    //        case rotateZ:
    //            a=(this->angle)*currenttime-lastA;
    //            lastA=(this->angle)*currenttime;
    //            rotateZMotion(a);
    //            break;
    //        }
    //    }
    //    qDebug()<<"lastX"<<lastX;
    //    qDebug()<<"x"<<x;
    //    qDebug()<<"lastY"<<lastY;
    //    qDebug()<<"y"<<y;
    //    qDebug()<<"lastZ"<<lastZ;
    //    qDebug()<<"z"<<z;
    //    qDebug()<<"lastA"<<lastA;
    //    qDebug()<<"a"<<a;
}

void Motion::linearMotion(double x, double y, double z){
    actor->SetPosition(x,y,z);
    //  transform->Translate(x,y,z);
}

void Motion::scaleMotion(double x,double y,double z){
    actor->SetScale(x,y,z);
    //   transform->Scale(x,y,z);
}

void Motion::rotateMotion(double angle,double x,double y,double z){
    actor->RotateWXYZ(angle,x,y,z);
    //  transform->RotateWXYZ(angle,x,y,z);
}

void Motion::rotateXMotion(double angle){
    actor->RotateX(angle);
    // transform->RotateX(angle);
}
void Motion::rotateYMotion(double angle){
    actor->RotateY(angle);
    // transform->RotateY(angle);
}
void Motion::rotateZMotion(double angle){
    actor->RotateZ(angle);
    // transform->RotateZ(angle);
}
