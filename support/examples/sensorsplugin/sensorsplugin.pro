CONFIG      += plugin
TARGET      = qcadsensors
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = RSensorsPlugin.h \
    problem_data.h
SOURCES     = RSensorsPlugin.cpp \
    problem_data.cpp
DESTDIR     = ../../../plugins
LIBS += -lqcadcore -lqcadgui -lqcadecmaapi
