CONFIG      += plugin
TARGET      = qcadsensors
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = *.h *.hpp

SOURCES     = *.cpp
DESTDIR     = ../../../plugins
LIBS += -lqcadcore -lqcadgui -lqcadecmaapi
