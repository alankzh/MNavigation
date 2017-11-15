#ifndef PROGRESSOBSERVER_H
#define PROGRESSOBSERVER_H

#include <itkCommand.h>
#include <itkRegularStepGradientDescentOptimizer.h>
#include "progressreceive.h"
#include <itkEventObject.h>
#include <QDebug>
#include <itkProcessObject.h>

class ProgressObserver:public itk::Command
{
public:
    typedef  ProgressObserver   Self;
    typedef  itk::Command             Superclass;
    typedef itk::SmartPointer<Self>  Pointer;

    //itkNewMacro: 该宏包装了 New() 方法的所有代码
    itkNewMacro( Self )

    typedef itk::RegularStepGradientDescentOptimizer     OptimizerType;
    typedef   const OptimizerType   *    OptimizerPointer;

    void Execute(itk::Object *caller, const itk::EventObject & event);

    //object: 指向激活事件的对象；event: 需要被激活的事件
    void Execute(const itk::Object * object, const itk::EventObject & event);

    void setProgressReceiver(ProgressReceive *e);

    ProgressReceive* getProgressReceiver();
protected:
    ProgressObserver();
    ~ProgressObserver();
private:
    ProgressReceive *receiver=NULL;
};

#endif // PROGRESSOBSERVER_H
