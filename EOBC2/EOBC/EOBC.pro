#-------------------------------------------------
#
# Project created by QtCreator 2011-03-11T09:22:42
#
#-------------------------------------------------

QT       += core gui

TARGET = EOBC
TEMPLATE = app


SOURCES +=\
    src/DisplayMap/displaymapcontrol.cpp \
    src/main.cpp \
    src/Model/area.cpp \
    src/Model/patient.cpp \
    src/Model/inpatient.cpp \
    src/Model/bed.cpp \
    src/Model/facility.cpp \
    src/Model/ltc_facility.cpp \
    src/Model/waitinglist.cpp \
    src/DisplayMap/mapvectors.cpp \
    src/DisplayMap/maparea.cpp \
    src/DisplayMap/map.cpp

HEADERS  += \
    src/DisplayMap/displaymapcontrol.h \
    src/Model/area.h \
    src/Model/patient.h \
    src/Model/inpatient.h \
    src/Model/bed.h \
    src/Model/facility.h \
    src/Model/ltc_facility.h \
    src/Model/waitinglist.h \
    src/DisplayMap/mapvectors.h \
    src/DisplayMap/maparea.h \
    src/DisplayMap/map.h

RESOURCES += \
    Resources.qrc
