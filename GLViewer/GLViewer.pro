#-------------------------------------------------
#
# Project created by QtCreator 2016-10-01T08:31:46
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLViewer
TEMPLATE = app

win32:LIBS += -lopengl32
 unix:LIBS += -lGL

SOURCES += main.cpp\
        mainwindow.cpp \
    mopenglwidget.cpp

HEADERS  += mainwindow.h \
    mopenglwidget.h

FORMS    += mainwindow.ui
