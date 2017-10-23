#include "rendersetting.h"
/**
 * @brief RenderSetting::RenderSetting
 * author 张殊峰
 */
RenderSetting::RenderSetting()
{
        qDebug()<<"RenderSetting begin";
        args=new RenderArgs();
        args->property = vtkSmartPointer<vtkVolumeProperty>::New();
        args->colorFun = vtkSmartPointer<vtkColorTransferFunction>::New();
        args->opacityFun = vtkSmartPointer<vtkPiecewiseFunction>::New();
        args->gradientOpacityFun = vtkSmartPointer<vtkPiecewiseFunction>::New();
        isMax=false;
        isMin=false;
        qDebug()<<"RenderSetting end";
}
RenderSetting::~RenderSetting()
{
    delete args;
}

void RenderSetting::SetRenderType(RenderType rendertype, RenderSetting::RenderArgs *args) {
    vtkVolumeProperty* property = args->property;
    vtkColorTransferFunction* colorFun = args->colorFun;
    vtkPiecewiseFunction* opacityFun = args->opacityFun;
    vtkPiecewiseFunction* gradientOpacityFun = args->gradientOpacityFun;
    switch (rendertype)
    {
    case CT_Normal:
        opacityFun->RemoveAllPoints();
        colorFun->RemoveAllPoints();
        gradientOpacityFun->RemoveAllPoints();
        gradientOpacityFun->AddPoint(0, 1);
        gradientOpacityFun->AddPoint(255, 1);
        colorFun->AddRGBSegment(0, 0, 0, 0, 4096, 1, 1, 1);
        opacityFun->AddSegment(0, 0, 4096, 1);
        property->ShadeOff();
        property->SetInterpolationTypeToLinear();
        break;
    case CT_Bone:
        opacityFun->RemoveAllPoints();
        colorFun->RemoveAllPoints();
        gradientOpacityFun->RemoveAllPoints();
        gradientOpacityFun->AddPoint(0, 1);
        gradientOpacityFun->AddPoint(255, 1);
        {
            double* RGBpoint = new double[16]{ -3024, 0, 0, 0, -16.4458, 0.729412, 0.254902, 0.301961, 641.385, 0.905882, 0.815686, 0.552941, 3071, 1, 1, 1 };
            colorFun->FillFromDataPointer(4, RGBpoint);
            delete[] RGBpoint;
            double* opacityPoint = new double[8]{ -3024, 0, -16.4458, 0, 641.385, 0.715686, 3071, 0.705882 };
            opacityFun->FillFromDataPointer(4, opacityPoint);
            delete[] opacityPoint;
        }
        property->ShadeOn();
        property->SetSpecularPower(10);
        property->SetSpecular(0.2);
        property->SetAmbient(0.1);
        property->SetDiffuse(0.9);
        property->SetInterpolationTypeToLinear();
        break;
    case CT_AAA:
        opacityFun->RemoveAllPoints();
        colorFun->RemoveAllPoints();
        gradientOpacityFun->RemoveAllPoints();
        gradientOpacityFun->AddPoint(0, 1);
        gradientOpacityFun->AddPoint(255, 1);
        {
        //TODO delete x
            float x=0.2;
            double* RGBpoint = new double[24]{ -3024, 0, 0, 0, 143.556, 0.615686, 0.356863, 0.184314, 166.222, 0.882353, 0.603922, 0.290196, 214.389, 1, 1, 1, 419.736, 1, 0.937033, 0.954531, 3071, 0.827451, 0.658824, 1 };
            colorFun->FillFromDataPointer(6, RGBpoint);
            delete[] RGBpoint;
            double* opacityPoint = new double[12]{ -3024, 0, 143.556, 0, 166.222, 0.686275*x, 214.389, 0.696078*x, 419.736, 0.833333*x, 3071, 0.803922*x };
            opacityFun->FillFromDataPointer(6, opacityPoint);
            delete[] opacityPoint;
        }
        property->ShadeOn();
        property->SetSpecularPower(10);
        property->SetSpecular(0.2);
        property->SetAmbient(0.1);
        property->SetDiffuse(0.9);
        property->SetInterpolationTypeToLinear();
        break;
    case CT_Liver_Vasculature:
        opacityFun->RemoveAllPoints();
        colorFun->RemoveAllPoints();
        gradientOpacityFun->RemoveAllPoints();
        gradientOpacityFun->AddPoint(0, 1);
        gradientOpacityFun->AddPoint(255, 1);
        {
            double* RGBpoint = new double[28]{ -2048, 0, 0, 0, 149.113, 0, 0, 0, 157.884, 0.501961, 0.25098, 0, 339.96, 0.695386, 0.59603, 0.36886, 388.526, 0.854902, 0.85098, 0.827451, 1197.95, 1, 1, 1, 3661, 1, 1, 1 };
            colorFun->FillFromDataPointer(7, RGBpoint);
            delete[] RGBpoint;
            double* opacityPoint = new double[14]{ -2048, 0, 149.113, 0, 157.884, 0.482143, 339.96, 0.660714, 388.526, 0.830357, 1197.95, 0.839286, 3661, 0.848214 };
            opacityFun->FillFromDataPointer(7, opacityPoint);
            delete[] opacityPoint;
        }
        property->ShadeOff();
        property->SetSpecularPower(1);
        property->SetSpecular(0);
        property->SetAmbient(0.2);
        property->SetDiffuse(1);
        property->SetInterpolationTypeToLinear();
        break;
    case CT_Lung:
        opacityFun->RemoveAllPoints();
        colorFun->RemoveAllPoints();
        gradientOpacityFun->RemoveAllPoints();
        gradientOpacityFun->AddPoint(0, 1);
        gradientOpacityFun->AddPoint(985.12, 1);
        gradientOpacityFun->AddPoint(988, 1);
        {
            double* RGBpoint = new double[24]{ -1000, 0.3, 0.3, 1, -600, 0, 0, 1, -530, 0.134704, 0.781726, 0.0724558, -460, 0.929244, 1, 0.109473, -400, 0.888889, 0.254949, 0.0240258, 2952, 1, 0.3, 0.3 };
            colorFun->FillFromDataPointer(6, RGBpoint);
            delete[] RGBpoint;
            double* opacityPoint = new double[12]{ -1000, 0, -600, 0, -599, 0.15, -400, 0.15, -399, 0, 2952, 0 };
            opacityFun->FillFromDataPointer(6, opacityPoint);
            delete[] opacityPoint;
        }
        property->ShadeOn();
        property->SetSpecularPower(1);
        property->SetSpecular(0);
        property->SetAmbient(0.2);
        property->SetDiffuse(1);
        property->SetInterpolationTypeToLinear();
        break;
    case MR_Default:
        opacityFun->RemoveAllPoints();
        colorFun->RemoveAllPoints();
        gradientOpacityFun->RemoveAllPoints();
        gradientOpacityFun->AddPoint(0, 1);
        gradientOpacityFun->AddPoint(255, 1);
        {
            double* RGBpoint = new double[24]{ 0, 0, 0, 0, 20, 0.168627, 0, 0, 40, 0.403922, 0.145098, 0.0784314, 120, 0.780392, 0.607843, 0.380392, 220, 0.847059, 0.835294, 0.788235, 1024, 1, 1, 1 };
            colorFun->FillFromDataPointer(6, RGBpoint);
            delete[] RGBpoint;
            double* opacityPoint = new double[12]{ 0, 0, 20, 0, 40, 0.15, 120, 0.3, 220, 0.375, 1024, 0.5 };
            opacityFun->FillFromDataPointer(6, opacityPoint);
            delete[] opacityPoint;
        }
        property->ShadeOn();
        property->SetSpecularPower(1);
        property->SetSpecular(0);
        property->SetAmbient(0.2);
        property->SetDiffuse(1);
        property->SetInterpolationTypeToLinear();
        break;
    case MR_Brain:
        opacityFun->RemoveAllPoints();
        colorFun->RemoveAllPoints();
        gradientOpacityFun->RemoveAllPoints();
        gradientOpacityFun->AddPoint(0, 1);
        gradientOpacityFun->AddPoint(160.25, 1);
        {
            double* RGBpoint = new double[16]{ 0, 0, 0, 0, 98.7223, 0.956863, 0.839216, 0.192157, 412.406, 0, 0.592157, 0.807843, 641, 1, 1, 1 };
            colorFun->FillFromDataPointer(4, RGBpoint);
            delete[] RGBpoint;
            double* opacityPoint = new double[10]{ 0, 0, 36.05, 0, 218.302, 0.171429, 412.406, 1, 641, 1 };
            opacityFun->FillFromDataPointer(5, opacityPoint);
            delete[] opacityPoint;
        }
        property->ShadeOn();
        property->SetSpecularPower(40);
        property->SetSpecular(0.5);
        property->SetAmbient(0.3);
        property->SetDiffuse(0.6);
        property->SetInterpolationTypeToLinear();
        break;
    default:
        break;
    }
}

void RenderSetting::SetRenderType(RenderType rendertype){
    SetRenderType(rendertype,args);
}

void RenderSetting::ShiftRenderFunction(double shift, vtkColorTransferFunction* colorFun) {

    int n = colorFun->GetSize();
    if (n <= 2) {
        return;
    }
    //printf("color shift");
    double* data = colorFun->GetDataPointer();
    double min = data[0];
    double max = data[4 * (n - 1)];
    double Range = max - min;
    double minShift = min - data[4];
    double maxShift = max - data[4 * (n - 2)];
    double offset = Range * shift;
    if (offset < minShift) {
        offset = minShift;
    }
    if (offset > maxShift) {
        offset = maxShift;
    }
    for (int i = 1; i < n - 1; i++) {
        data[4 * i] += offset;
    }


    colorFun->FillFromDataPointer(n, data);
}

void RenderSetting::ShiftRenderFunction(double shift, vtkPiecewiseFunction* opacityFun) {

    int n = opacityFun->GetSize();
    if (n <= 2) {
        return;
    }
    //printf("opacity shift");
    double* data = opacityFun->GetDataPointer();
    double min = data[0];
    double max = data[2 * (n - 1)];
    double Range = max - min;
    double minShift = min - data[2];
    double maxShift = max - data[2* (n - 2)];
    double offset = Range * shift;
    if (offset < minShift) {
        offset = minShift;
    }
    if (offset > maxShift) {
        offset = maxShift;
    }
    for (int i = 1; i < n - 1; i++) {
        data[2 * i] += offset;
    }
    opacityFun->FillFromDataPointer(n, data);
}

void RenderSetting::ShiftRenderFunction(double shift,int choose){
    qDebug()<<"ShiftRenderFunction";
    switch(choose){
    case 1:
        ShiftRenderFunction(shift,this->args->opacityFun);
        break;
    case 2:
        ShiftRenderFunction(shift,this->args->colorFun);
        break;
    }
}
