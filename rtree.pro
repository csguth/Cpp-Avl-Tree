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

TEMPLATE = app


SOURCES += tst_rtreetest.cpp \
    range_tree.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    range_tree.h
