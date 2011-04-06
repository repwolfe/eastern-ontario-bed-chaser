#-------------------------------------------------
#
# Project created by QtCreator 2011-03-11T09:22:42
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += network
QT	 += testlib

TARGET = EOBCapplication
TEMPLATE = app

OBJECTS_DIR = bin/
MOC_DIR = bin/moc/

INCLUDEPATH +=\
    src/ChangeData \
    src/ChangeData/View \
    src/ChangeData/Control \
    src/Common \
    src/DisplayMap \
    src/GetData \
    src/LogOn \
    src/Model \
    src/Storage \
    src/Reporting \
    src/Communication \
    src/Send \
    src/Receive

DEPENDPATH += INCLUDEPATH


SOURCES +=\
    src/DisplayMap/displaymapcontrol.cpp \
    src/main.cpp \
    src/Model/area.cpp \
    src/Model/patient.cpp \
    src/Model/facility.cpp \
    src/DisplayMap/mapvectors.cpp \
    src/DisplayMap/maparea.cpp \
    src/DisplayMap/map.cpp \
    src/GetData/getdatacontrol.cpp \
    src/ChangeData/changedatacontrol.cpp \
    src/ChangeData/View/addfacilityform.cpp \
    src/ChangeData/View/createuserform.cpp \
    src/ChangeData/View/updatewaitinglistform.cpp \
    src/LogOn/logoncontrol.cpp \
    src/LogOn/logonwindow.cpp \
    src/Common/logger.cpp \
    src/Common/convenience.cpp \
    src/Storage/storageHandler.cpp \
    src/DisplayMap/facilityicon.cpp \
    src/DisplayMap/mapitem.cpp \
    src/ChangeData/View/movepatientform.cpp \
    src/ChangeData/View/addpatientform.cpp \
    src/ChangeData/View/updatebedsform.cpp \
    src/ChangeData/Control/movepatientcontrol.cpp \
    src/ChangeData/Control/addfacilitycontrol.cpp \
    src/ChangeData/Control/addpatientcontrol.cpp \
    src/DisplayMap/mapmarker.cpp \
    src/Reporting/reportingcontrol.cpp \
    src/ChangeData/Control/createusercontrol.cpp \
    src/ChangeData/Control/updatebedscontrol.cpp \
    src/ChangeData/Control/updatewaitinglistcontrol.cpp \
    src/Reporting/generatereportwindow.cpp \
    src/Reporting/viewallreportswindow.cpp \
    src/Reporting/viewreportwindow.cpp \
    src/Reporting/report.cpp \
    src/Reporting/reportbars.cpp \
    src/Communication/channelin.cpp \
    src/Communication/channelout.cpp \
    src/GetData/getdatachangedatainterface.cpp \
    src/GetData/getdatadisplaymapinterface.cpp \
    src/GetData/getdatareportinginterface.cpp \
    src/Send/sendmessagecontrol.cpp \
    src/Receive/ReceiveMessageControl.cpp \
    src/Communication/communicationsendinterface.cpp \
    src/Send/sendchangedatainterface.cpp \
    src/Communication/communicationreceiveinterface.cpp \
    src/ChangeData/changedatareceiveinterface.cpp \
    src/Storage/storagewrite.cpp \
    src/Storage/storageread.cpp




HEADERS  += \
    src/DisplayMap/displaymapcontrol.h \
    src/Model/area.h \
    src/Model/patient.h \
    src/Model/facility.h \
    src/DisplayMap/mapvectors.h \
    src/DisplayMap/maparea.h \
    src/DisplayMap/map.h \
    src/Model/modelcommon.h \
    src/GetData/getdatacontrol.h \
    src/ChangeData/changedatacontrol.h \
    src/ChangeData/View/addfacilityform.h \
    src/ChangeData/View/createuserform.h \
    src/ChangeData/View/updatewaitinglistform.h \
    src/LogOn/logoncontrol.h \
    src/LogOn/logonwindow.h \
    src/Common/logger.h \
    src/Common/convenience.h \
    src/Storage/storageHandler.h \
    src/DisplayMap/facilityicon.h \
    src/DisplayMap/mapitem.h \
    src/ChangeData/View/movepatientform.h \
    src/ChangeData/View/addpatientform.h \
    src/ChangeData/View/updatebedsform.h \
    src/ChangeData/Control/movepatientcontrol.h \
    src/ChangeData/Control/addfacilitycontrol.h \
    src/ChangeData/Control/addpatientcontrol.h \
    src/DisplayMap/mapmarker.h \
    src/Reporting/reportingcontrol.h \
    src/ChangeData/Control/createusercontrol.h \
    src/ChangeData/Control/updatebedscontrol.h \
    src/ChangeData/Control/updatewaitinglistcontrol.h \
    src/Reporting/generatereportwindow.h \
    src/Reporting/viewallreportswindow.h \
    src/Reporting/viewreportwindow.h \
    src/Reporting/report.h \
    src/Reporting/reportbars.h \
    src/Communication/channelin.h \
    src/Communication/channelout.h \
    src/GetData/getdatachangedatainterface.h \
    src/GetData/getdatadisplaymapinterface.h \
    src/GetData/getdatareportinginterface.h \
    src/Send/sendmessagecontrol.h \
    src/Receive/ReceiveMessageControl.h \
    src/Communication/communicationsendinterface.h \
    src/Send/sendchangedatainterface.h \
    src/Communication/communicationreceiveinterface.h \ 
    src/ChangeData/changedatareceiveinterface.h \
    src/Storage/storagewrite.h \
    src/Storage/storageread.h



RESOURCES += \
    Resources.qrc
