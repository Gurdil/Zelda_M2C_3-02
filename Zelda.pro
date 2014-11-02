#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T22:13:50
#
#-------------------------------------------------

QT       += core gui\
    xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zelda
TEMPLATE = app


SOURCES += main.cpp \
    controler.cpp \
    zscene.cpp \
    zanimator.cpp \
    zview.cpp \
    ZKeyRecorder.cpp \
    zobject.cpp \
    zmap.cpp \
    zavatar.cpp

HEADERS  += \
    controler.h \
    zscene.h \
    zanimator.h \
    zinit.h \
    zview.h \
    ZKeyRecorder.h \
    zobject.h \
    zmap.h \
    zavatar.h

OTHER_FILES +=

RESOURCES += \
    image.qrc
