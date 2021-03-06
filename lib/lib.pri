######################################################################
# Automatically generated by qmake (2.01a) lör sep 1 15:53:42 2007
######################################################################

TEMPLATE = lib
TARGET = xmmsclientqt
VERSION = 0.0.0
DEPENDPATH += .
INCLUDEPATH += .
CONFIG -= app_bundle
QT -= gui
QT += network

# TODO: detect automatically
#DEFINES += HAVE_XMMSV

CONFIG += link_pkgconfig
PKGCONFIG += xmms2-plugin

MOC_DIR     = .moc

# Input
HEADERS += bindata.h \
           client.h \
           config.h \
           medialib.h \
           message.h \
           playback.h \
           playlist.h \
           result.h \
           stats.h \
           xform.h \
           object.h \
           propdict.h \
		   coll.h \
		   collection.h \
		   typedefs.h

SOURCES += bindata.cpp \
           client.cpp \
           config.cpp \
           medialib.cpp \
           message.cpp \
           playback.cpp \
           playlist.cpp \
           result.cpp \
           stats.cpp \
           xform.cpp \
           propdict.cpp \
		   coll.cpp \
		   collection.cpp
