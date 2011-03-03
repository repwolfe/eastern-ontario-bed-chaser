#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T14:09:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT      += network
QT	+= testlib

TARGET = sockets
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    client.cpp

HEADERS += \
    server.h \
    client.h
