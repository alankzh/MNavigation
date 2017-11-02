#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL)
#endif

#include <QApplication>
#include "widget.h"
#include "mainwindow.h"
#include <QFile>

#include "RenderPropertyGenerator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vtkOutputWindow::GlobalWarningDisplayOff();
    
   /* Widget w;
    w.setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint);*/

	RenderPropertyGenerator::LoadPresets();
	RenderPropertyGenerator::SavePresetsToLocal();

    MainWindow w;

    w.show();
    return a.exec();
}
