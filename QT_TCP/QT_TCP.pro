#-------------------------------------------------
#
# Project created by QtCreator 2022-01-11T18:05:39
#
#-------------------------------------------------

unix:QMAKE_CFLAGS_WARN_ON += -Wno-deprecated-copy
unix:QMAKE_CXXFLAGS_WARN_ON += -Wno-deprecated-copy
QT       += core gui
QT       += network
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_TCP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    Function/function.cpp \
    PDS_protocol/pdsPalletCoordinateClass.cpp \
    PDS_protocol/pdsPalletRequestClass.cpp \
    PDS_protocol/pdsPalletResponseClass.cpp \
    PDS_protocol/pdsProtocol.cpp \
    PDS_protocol/pdsRackCoordinateClass.cpp \
    clientPDS.cpp \
        main.cpp \
        serverwidget.cpp \
    clientwidget.cpp \
    AGVMessage/AGV_Message.cpp \
    Spline/ExternalPathCoordinateSet.cpp \
    AGVMessage/CoordinateClass.cpp \
    AGVMessage/RequestExternalClass.cpp \
    AGVMessage/AgvExternalPara.cpp \
    AGVMessage/CommunicationClass.cpp \
    Math/UserMatrix.cpp \
    PDS_protocol/pdsNoopclass.cpp \
    PDS_protocol/pdssavereferenceforkrequestclass.cpp



HEADERS += \
    Function/function.h \
    PDS_protocol/pdsEnumCode.h \
    PDS_protocol/pdsErrorCode.h \
    PDS_protocol/pdsPalletCoordinateClass.h \
    PDS_protocol/pdsPalletRequestClass.h \
    PDS_protocol/pdsPalletResponseClass.h \
    PDS_protocol/pdsProtocol.h \
    PDS_protocol/pdsRackCoordinateClass.h \
    PDS_protocol/pdsStruct.h \
    clientPDS.h \
        serverwidget.h \
    clientwidget.h \
    AGVMessage/AGV_Struct.h \
    AGVMessage/AGV_Message.h \
    Spline/ExternalPathCoordinateSet.h \
    AGVMessage/RequestExternalClass.h \
    AGVMessage/AgvExternalPara.h \
    AGVMessage/CommunicationClass.h \
    Math/UserMatrix.h \
    AGVMessage/CoordinateClass.h \
    main.h \
    PDS_protocol/pdsNoopclass.h \
    PDS_protocol/pdssavereferenceforkrequestclass.h




FORMS += \
    clientPDS.ui \
        serverwidget.ui \
    clientwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#ros
INCLUDEPATH += /opt/ros/noetic/include

LIBS += -L/opt/ros/noetic/lib -lroscpp -lpthread -lrosconsole\
         -lroscpp_serialization -lrostime  -lcpp_common \
        -lroslib -ltf  -lboost_system \
        -ltf2 -lxmlrpcpp -lrosconsole -lrosconsole_backend_interface -lrosconsole_log4cxx

#VTK
INCLUDEPATH += /usr/include/vtk-7.1

#PCL
INCLUDEPATH += /usr/include/pcl-1.10\
               /usr/include/eigen3


LIBS += /usr/lib/x86_64-linux-gnu/libpcl*

#boost
LIBS += /usr/lib/x86_64-linux-gnu/libvtk*.so

LIBS += /usr/lib/x86_64-linux-gnu/libboost*

LIBS += /usr/lib/x86_64-linux-gnu/libpthread*

DISTFILES += \
    record_20220818 \
    record_20220819 \
    record_20220822 \
    record_20220823








