#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T22:09:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = physics
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    molecule.cpp \
    brownianparticle.cpp \
    graphicsview.cpp

HEADERS  += mainwidget.h \
    molecule.h \
    brownianparticle.h \
    graphicsview.h

FORMS    += mainwidget.ui

QMAKE_CXXFLAGS += -std=c++11
