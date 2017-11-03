#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL)
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
    return a.exec();
}
