#-------------------------------------------------
#
# Project created by QtCreator 2011-03-11T09:22:42
#
#-------------------------------------------------

QT       += core gui
QT       += xml

TARGET = EOBCapplication
TEMPLATE = app

OBJECTS_DIR = bin/
MOC_DIR = bin/

INCLUDEPATH +=\
    src/ChangeData \
    src/Common \
    src/DisplayMap \
    src/GetData \
    src/LogOn \
    src/Model \
    src/Storage


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
    src/ChangeData/addfacilityform.cpp \
    src/ChangeData/createuserform.cpp \
    src/ChangeData/updatewaitinglistform.cpp \
    src/LogOn/logoncontrol.cpp \
    src/LogOn/logonwindow.cpp \
    src/Common/logger.cpp \
    src/Common/convenience.cpp \
    src/Storage/storageHandler.cpp \
    src/DisplayMap/facilityicon.cpp \
    src/DisplayMap/mapitem.cpp \
    src/ChangeData/movepatientform.cpp \
    src/ChangeData/addpatientform.cpp \
    src/ChangeData/updatebedsform.cpp



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
    src/ChangeData/addfacilityform.h \
    src/ChangeData/createuserform.h \
    src/ChangeData/updatewaitinglistform.h \
    src/LogOn/logoncontrol.h \
    src/LogOn/logonwindow.h \
    src/Common/logger.h \
    src/Common/convenience.h \
    src/Storage/storageHandler.h \
    src/DisplayMap/facilityicon.h \
    src/DisplayMap/mapitem.h \
    src/ChangeData/movepatientform.h \
    src/ChangeData/addpatientform.h \
    src/ChangeData/updatebedsform.h


RESOURCES += \
    Resources.qrc
