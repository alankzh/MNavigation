 #-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T10:02:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(windowsKits.pri)
include(vtk.pri)
include(itk.pri)

TARGET = widgetproject
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    myvolumewidget.cpp \
    vtkcustomtransformanimationcue.cpp \
    myslicerwidget.cpp \
    stlmanager.cpp \
    actormanager.cpp \
    CoordinateConverter.cpp \
    MarkerCreator.cpp \
    customWidgets/backgroundbutton.cpp \
    customWidgets/greenbutton.cpp \
    customWidgets/mygridlayout.cpp \
    customWidgets/mypushbutton.cpp \
    customWidgets/mydialog.cpp \
    customAnimator/animator.cpp \
    customAnimator/animatorset.cpp \
    customAnimator/motion.cpp \
    customAnimator/myvtkcustomanimationcue.cpp \
    customWidgets/markbutton.cpp \
    customWidgets/threebackgroundbutton.cpp \
    tools/screentools.cpp \
    tools/constant.cpp \
    RenderPropertyGenerator.cpp \
    customWidgets/selectpropertywidget.cpp\
    customWidgets/emitbutton.cpp \
    customThread/progressbarwidget.cpp \
    customThread/progressobserver.cpp \
    DicomLoader.cpp \
    Scene.cpp \
    customThread/loadthreadhelper.cpp \
    customWidgets/dirlistwidget.cpp \
    customWidgets/mylistview.cpp \
    customModel/dirbean.cpp \
    newui.cpp \
    customWidgets/dicominfowidget.cpp \
    customWidgets/drawwidget.cpp \
    customWidgets/singlerenderwidget.cpp \
    customWidgets/trapzoidtag.cpp \
    customWidgets/operationplanwidget.cpp \
    customWidgets/textureselectwidget.cpp \
    customWidgets/dirlistitemwidget.cpp \
    customWidgets/mylistwidget.cpp \
    customWidgets/projectpop.cpp

HEADERS  +=     mainwindow.h \
    vtks.h \
    myvolumewidget.h \
    vtkcustomtransformanimationcue.h \
    myslicerwidget.h \
    qts.h \
    stlmanager.h \
    actormanager.h \
    CoordinateConverter.h \
    MarkerCreator.h \
    customWidgets/backgroundbutton.h \
    customWidgets/greenbutton.h \
    customWidgets/mydialog.h \
    customWidgets/myGridLayout.h \
    customWidgets/mypushbutton.h \
    customAnimator/animator.h \
    customAnimator/animatorfinisherlistener.h \
    customAnimator/animatorset.h \
    customAnimator/motion.h \
    customAnimator/myvtkcustomanimationcue.h \
    customWidgets/markbutton.h \
    customWidgets/threebackgroundbutton.h \
    tools/screentools.h \
    tools/constant.h \
    RenderPropertyGenerator.h \
    customWidgets/selectpropertywidget.h \
    customWidgets/emitbutton.h \
    customThread/progressbarwidget.h \
    customThread/progressobserver.h \
    Creator.h \
    DicomLoader.h \
    Scene.h \
    customThread/progressreceive.h \
    customThread/loadthreadhelper.h \
    customWidgets/dirlistwidget.h \
    customWidgets/mylistview.h \
    customModel/dirbean.h \
    newui.h \
    customWidgets/dicominfowidget.h \
    customWidgets/drawwidget.h \
    customWidgets/singlerenderwidget.h \
    customWidgets/trapzoidtag.h \
    customWidgets/operationplanwidget.h \
    customWidgets/textureselectwidget.h \
    customWidgets/dirlistitemwidget.h \
    customWidgets/mylistwidget.h \
    customWidgets/projectpop.h


FORMS    += widget.ui

RESOURCES += \
    resources.qrc

RC_FILE+=exeicon.rc
