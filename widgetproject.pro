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
    customWidgets/dirpathwidget.cpp \
    DicomLoader.cpp \
    Scene.cpp \
    customThread/loadthreadhelper.cpp

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
    customWidgets/dirpathwidget.h \
    Creator.h \
    DicomLoader.h \
    Scene.h \
    customThread/progressreceive.h \
    customThread/loadthreadhelper.h


FORMS    += widget.ui

RESOURCES += \
    resources.qrc
