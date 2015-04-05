#-------------------------------------------------
#
# Project created by QtCreator 2015-04-04T14:58:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = benchmark
CONFIG   += console
CONFIG   -= app_bundle
CONFIG+=debug

TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG -= -O1
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG -= -O3

QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE -= O1


SOURCES += main.cpp \
    benchmarkframework.cpp

HEADERS += \
    benchmarkframework.h
