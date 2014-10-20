#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T22:13:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zelda
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    controler.cpp \
    zscene.cpp \
    zanimator.cpp \
    zinit.cpp

HEADERS  += \
    mainwindow.h \
    controler.h \
    zscene.h \
    zanimator.h \
    zinit.h

OTHER_FILES +=

RESOURCES += \
    image.qrc
