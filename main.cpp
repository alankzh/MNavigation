#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL)
VTK_MODULE_INIT(vtkRenderingFreeType)
#endif

#include <QApplication>
#include "mainwindow.h"
#include <QFile>


#include "tools/constant.h"
#include "tools/screentools.h"

#include "RenderPropertyGenerator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vtkOutputWindow::GlobalWarningDisplayOff();

	RenderPropertyGenerator::LoadPresets();
	RenderPropertyGenerator::SavePresetsToLocal();

    MainWindow w;
    w.show();
    if(argv[1]!=NULL){
        //重启后读取文件路径，加载dicom
        w.onRestart(argv[1]);
    }
    return a.exec();
}
