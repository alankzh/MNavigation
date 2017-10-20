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

//程序入口
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vtkOutputWindow::GlobalWarningDisplayOff();//关闭伴随的vtkOutputWindow
    //测试功能用窗口
//    Widget w;
 //   w.setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint);

    //主窗口，稳定。
    MainWindow w;

    w.show();
    return a.exec();
}
