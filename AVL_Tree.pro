#-------------------------------------------------
#
# Project created by QtCreator 2014-06-13T15:04:45
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_avltree
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -Wall -Werror

TEMPLATE = app


SOURCES += \
    interval.cpp \
    tst_avltree.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    interval.h \
    avl_tree.h
