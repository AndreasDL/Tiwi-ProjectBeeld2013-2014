#-------------------------------------------------
#
# Project created by QtCreator 2014-05-07T13:21:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = projectBeeld
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = app


SOURCES += \
    ../example.cpp
INCLUDEPATH += C://Users//Cedric//opencv//release//install//include
LIBS += C://Users//Cedric//opencv//release//lib//*

HEADERS += \
    ../Harris.h \
    ../LineDetection.h \
    ../Canny.h \
    ../Squares.h
