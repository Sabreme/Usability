#-------------------------------------------------
#
# Project created by QtCreator 2015-05-19T11:58:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Usability
TEMPLATE = app


SOURCES += main.cpp \
    UserTesting.cpp

HEADERS  += \
    UserTesing.h

FORMS    += \
    UserTesting.ui

QMAKE_CXXFLAGS_DEBUG += -g  -std=c++0x

OTHER_FILES += \
    counterbalance.txt

DESTDIR = $$PWD
