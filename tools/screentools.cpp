#include "screentools.h"

ScreenTools::ScreenTools()
{

}

int ScreenTools::getComputerScreenWidth(){
    QDesktopWidget *des=QApplication::desktop();
    return des->screenGeometry().width();
}

int ScreenTools::getComputerScreenHeight(){
    QDesktopWidget *des=QApplication::desktop();
    return des->screenGeometry().height();
}
