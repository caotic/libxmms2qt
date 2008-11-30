TEMPLATE = lib
TARGET = xmmsqt_highlevel
VERSION = 0.0.1
DEPENDPATH += . ../lib
INCLUDEPATH += . ../lib
CONFIG -= app_bundle
QT += network

CONFIG += link_pkgconfig
PKGCONFIG += xmms2-plugin

MOC_DIR     = .moc
OBJ_DIR	    = .obj

# Input
HEADERS += cache.h \
           playlistmodel.h

SOURCES += cache.cpp \
           playlistmodel.cpp
