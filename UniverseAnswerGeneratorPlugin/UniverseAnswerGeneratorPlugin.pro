#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T09:38:08
#
#-------------------------------------------------

QT       -= gui
QT += core
TARGET = UniverseAnswerGeneratorPlugin
CONFIG += plugin
TEMPLATE = lib

DEFINES += NUMBERGENERATOR_LIBRARY

SOURCES += \
    universeanswergeneratorimpl.cpp \
    universeanswergeneratorplugin.cpp

HEADERS += \
    universeanswergeneratorimpl.h \
    universeanswergeneratorplugin.h \
    universeAnswergenerator_global.h


INCLUDEPATH += $$PWD/../PluginManager/

DESTDIR  = ../plugins

unix {
    target.path = /usr/lib
    INSTALLS += target
}
