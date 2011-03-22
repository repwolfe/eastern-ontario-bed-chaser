#-------------------------------------------------
#
# Project created by QtCreator 2011-03-11T09:22:42
#
#-------------------------------------------------

QT       += core gui

TARGET = EOBCapplication
TEMPLATE = app

OBJECTS_DIR = bin/
MOC_DIR = bin/


SOURCES +=\
    src/DisplayMap/displaymapcontrol.cpp \
    src/main.cpp \
    src/Model/area.cpp \
    src/Model/patient.cpp \
    src/Model/facility.cpp \
    src/Model/ltc_facility.cpp \
    src/DisplayMap/mapvectors.cpp \
    src/DisplayMap/maparea.cpp \
    src/DisplayMap/map.cpp \
    src/GetData/getdatacontrol.cpp \
    src/ChangeData/changedatacontrol.cpp \
    src/ChangeData/facilityinformationform.cpp \
    src/ChangeData/createuserform.cpp \
    src/ChangeData/updatewaitinglistform.cpp \
    src/ChangeData/redirectpatientform.cpp \
    src/LogOn/logoncontrol.cpp \
    src/LogOn/logonwindow.cpp \
    src/Common/logger.cpp \
    src/Common/convenience.cpp


HEADERS  += \
    src/DisplayMap/displaymapcontrol.h \
    src/Model/area.h \
    src/Model/patient.h \
    src/Model/facility.h \
    src/Model/ltc_facility.h \
    src/DisplayMap/mapvectors.h \
    src/DisplayMap/maparea.h \
    src/DisplayMap/map.h \
    src/Model/modelcommon.h \
    src/GetData/getdatacontrol.h \
    src/ChangeData/changedatacontrol.h \
    src/ChangeData/facilityinformationform.h \
    src/ChangeData/createuserform.h \
    src/ChangeData/updatewaitinglistform.h \
    src/ChangeData/redirectpatientform.h \
    src/Model/modelcontainer.h \
    src/LogOn/logoncontrol.h \
    src/LogOn/logonwindow.h \
    src/Common/logger.h \
    src/Common/convenience.h

RESOURCES += \
    Resources.qrc
