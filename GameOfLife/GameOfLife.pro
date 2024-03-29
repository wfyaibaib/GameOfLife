#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T22:51:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamemapmodel.cpp \
    cellwidget.cpp \
    gamemapview.cpp

HEADERS  += mainwindow.h \
    gamemapmodel.h \
    cellwidget.h \
    gamemapview.h

FORMS    += mainwindow.ui
