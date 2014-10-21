#-------------------------------------------------
#
# Project created by QtCreator 2014-10-07T11:03:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = task3
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    myfunction.cpp \
    equidistantinterpolation.cpp \
    equationsolver.cpp

HEADERS  += widget.h \
    myfunction.h \
    equidistantinterpolation.h \
    equationsolver.h

FORMS    += widget.ui
