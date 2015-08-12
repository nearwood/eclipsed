#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T13:26:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eclipsed
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sector.cpp \
    startingsector.cpp \
    galacticcenter.cpp \
    ring1.cpp \
    ring2.cpp \
    ring3.cpp \
    planet.cpp \
    resource.cpp \
    sectorlink.cpp \
    player.cpp \
    ship.cpp \
    tech.cpp \
    shipblueprint.cpp

HEADERS  += mainwindow.h \
    sector.h \
    startingsector.h \
    galacticcenter.h \
    ring1.h \
    ring2.h \
    ring3.h \
    planet.h \
    resource.h \
    sectorlink.h \
    player.h \
    ship.h \
    tech.h \
    shipblueprint.h

FORMS    += mainwindow.ui
