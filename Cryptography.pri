## This software is in the public domain, furnished "as is", without technical
## support, and with no warranty, express or implied, as to its usefulness for
## any purpose.
##
## Author: Ali Mashatan
## Email : ali.mashatan@gmail.com
## Source: https://github.com/Mashatan

TEMPLATE = app
TARGET = Cryptography
QMAKE_PROJECT_NAME = Cryptography
DESTDIR = bin

ARCHITECTURE = x86-64
QT_CONFIG += x64 

QT += widgets

CONFIG += qt
CONFIG += warn_on
CONFIG += console
CONFIG += thread 

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

QMAKE_CXXFLAGS_DEBUG   += -openmp -Zi -Od -MP8
QMAKE_LFLAGS_DEBUG += /DEBUG
#QMAKE_CXXFLAGS += -std=c++11 

CONFIG(debug, debug|release) {
    win32: TARGET = $$join(TARGET,,,_d)
}

QMAKE_LIBDIR += lib/64
LIBS += libeay32.lib
LIBS += ssleay32.lib
LIBS += zlib1.lib

Release:OBJECTS_DIR = build/release/.obj
Release:MOC_DIR     = build/release/.moc
Release:RCC_DIR     = build/release/.rcc
Release:UI_DIR      = build/release/.ui
Release:INCLUDEPATH += build/release/.ui

Debug:OBJECTS_DIR = build/debug/.obj
Debug:MOC_DIR     = build/debug/.moc
Debug:RCC_DIR     = build/debug/.rcc
Debug:UI_DIR      = build/debug/.ui
Debug:INCLUDEPATH += build/debug/.ui

INCLUDEPATH += .
INCLUDEPATH += inc/
INCLUDEPATH += inc/zlib

SOURCES += src/main.cpp
SOURCES += src/AMCipherAes128Ofb.cpp
SOURCES += src/AMCipherBase.cpp
SOURCES += src/AMEstimatedTime.cpp
SOURCES += src/AMGlobal.cpp

HEADERS += inc/AMCipherAes128Ofb.h
HEADERS += inc/AMCipherBase.h
HEADERS += inc/AMEstimatedTime.h
HEADERS += inc/AMGlobal.h

RESOURCES += 

