#include "progressobserver.h"

ProgressObserver::ProgressObserver(ProgressEmiter *progressEmiter)
{
    emiter=progressEmiter;
}

ProgressObserver::~ProgressObserver(){
    //emiter往往是监听者的父类，这里不要delete
    emiter=NULL;
}

void ProgressObserver::Execute(vtkObject *caller, unsigned long eventId, void *callData){
    vtkSmartPointer<vtkDICOMImageReader> reader =   reinterpret_cast<vtkDICOMImageReader*>(caller);
    if(emiter!=NULL){
        emiter->emitProgress(reader->GetProgress()*100);
    }

}

