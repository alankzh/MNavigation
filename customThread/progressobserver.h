#ifndef PROGRESSOBSERVER_H
#define PROGRESSOBSERVER_H
#include <vtkCommand.h>
#include <vtkSmartPointer.h>
#include "progressemiter.h"
#include <vtkDICOMImageReader.h>

class ProgressObserver:public vtkCommand
{
public:
    ProgressObserver(ProgressEmiter *progressEmiter);
    ~ProgressObserver();
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);
private:
    ProgressEmiter *emiter;
};

#endif // PROGRESSOBSERVER_H
