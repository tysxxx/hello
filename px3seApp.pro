#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T11:27:32
#
#-------------------------------------------------

QT       += core gui serialport network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += STM32F072_gesture_Library.lib
TARGET = px3seApp
TEMPLATE = app


INCLUDEPATH +=$$PWD main
include(main/main.pri)



FORMS    += mainwidget.ui
