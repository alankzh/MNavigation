#ifndef SCREENTOOLS_H
#define SCREENTOOLS_H

#include <QApplication>
#include <QDesktopWidget>

class ScreenTools
{
public:
    ScreenTools();
    static int getComputerScreenWidth();
    static int getComputerScreenHeight();
};

#endif // SCREENTOOLS_H
