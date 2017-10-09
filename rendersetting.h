#ifndef RENDERSETTING_H
#define RENDERSETTING_H

#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkSmartPointer.h>
#include <QDebug>

class RenderSetting
{
public:
    bool isMax;
    bool isMin;
    enum RenderType
        {
            CT_Normal = 0,
            CT_Bone = 1,
            CT_AAA = 2,
            CT_Liver_Vasculature = 3,
            CT_Lung = 4,
            MR_Default = 5,
            MR_Brain = 6
        };

        struct RenderArgs {
            vtkSmartPointer<vtkVolumeProperty> property;
              vtkSmartPointer<vtkColorTransferFunction> colorFun;
              vtkSmartPointer<vtkPiecewiseFunction> opacityFun;
             vtkSmartPointer<vtkPiecewiseFunction> gradientOpacityFun;
        };

          void SetRenderType(RenderType  rendertype);

         void SetRenderType(RenderType  rendertype, RenderArgs *arg);



         void ShiftRenderFunction(double shift, vtkColorTransferFunction * colorFun);

         void ShiftRenderFunction(double shift, vtkPiecewiseFunction * opacityFun);

         void ShiftRenderFunction(double shift,int choose);

        RenderArgs *args;
        RenderSetting();

        ~RenderSetting();
protected:

private:

};

#endif // RENDERSETTING_H
