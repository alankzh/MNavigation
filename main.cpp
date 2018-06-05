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
#include "RenderPropertyGenerator.h"
#include "newui.h"
#include <vtkOutputWindow.h>
#include <QDesktopWidget>
#include <QDebug>
#include "customWidgets/dirlistitemwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vtkOutputWindow::GlobalWarningDisplayOff();

    RenderPropertyGenerator::LoadPresets();
    RenderPropertyGenerator::SavePresetsToLocal();

   // MainWindow w;
   // w.show();
   NewUi u;
    u.show();

//    DirListItemWidget d(1);
//    DirBean bean(QString::fromLocal8Bit("namssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssse"),QString::fromLocal8Bit("path"),QString::fromLocal8Bit("date"),QString::fromLocal8Bit("time"));
//    d.loadData(bean);
//    d.show();


    return a.exec();
}
