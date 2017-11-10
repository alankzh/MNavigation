#include "progressobserver.h"

ProgressObserver::ProgressObserver(ProgressEmiter *progressEmiter)
{
    emiter=progressEmiter;
}

ProgressObserver::~ProgressObserver(){
    //emiter�����Ǽ����ߵĸ��࣬���ﲻҪdelete
    emiter=NULL;
}

void ProgressObserver::Execute(vtkObject *caller, unsigned long eventId, void *callData){
    vtkSmartPointer<vtkDICOMImageReader> reader =   reinterpret_cast<vtkDICOMImageReader*>(caller);
    if(emiter!=NULL){
        emiter->emitProgress(reader->GetProgress()*100);
    }

}

