#-------------------------------------------------
#
# Project created by QtCreator 2014-06-13T15:04:45
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_rtreetest
CONFIG   += console
CONFIG   -= app_bundle

#QMAKE_CXXFLAGS += -Wall -Werror

TEMPLATE = app


SOURCES += tst_rtreetest.cpp \
    range_tree.cpp \
    interval.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    range_tree.h \
    interval.h
