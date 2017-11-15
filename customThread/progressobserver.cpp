#include "progressobserver.h"

ProgressObserver::ProgressObserver()
{

}

ProgressObserver::~ProgressObserver(){
    if(receiver!=NULL){
        delete receiver;
        receiver=NULL;
    }
}

void ProgressObserver::setProgressReceiver(ProgressReceive *e){
    receiver=e;
}

ProgressReceive* ProgressObserver::getProgressReceiver(){
    if(receiver!=NULL){
        return receiver;
    }
}

void ProgressObserver::Execute(itk::Object *caller, const itk::EventObject &event){
    Execute( (const itk::Object *)caller, event);
}

void ProgressObserver::Execute(const itk::Object *object, const itk::EventObject &event){
    const itk::ProcessObject * filter = static_cast< const itk::ProcessObject * >( object );
        if( ! itk::ProgressEvent().CheckEvent( &event ) )
          {
          return;
          }
        std::cout << filter->GetProgress() << std::endl;

    if(receiver!=NULL){
       receiver->updateProgress(filter->GetProgress()*100);
    }
}
