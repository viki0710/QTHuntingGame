QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    huntingmodel2.cpp \
    huntingmodeltest.cpp \
    huntingpersistence2.cpp \
    huntingpersistencemock.cpp

HEADERS += \
    huntingmodel2.h \
    huntingmodeltest.h \
    huntingpersistence2.h \
    huntingpersistencemock.h \
    huntingsave2.h \
    states2.h
