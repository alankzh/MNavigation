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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vtkOutputWindow::GlobalWarningDisplayOff();//关闭伴随的vtkOutputWindow
    Widget w;
    w.setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint);
   // MainWindow w;
    w.show();
    return a.exec();
}
