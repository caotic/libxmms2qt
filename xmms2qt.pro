######################################################################
# Automatically generated by qmake (2.01a) lör sep 1 15:53:42 2007
######################################################################

TEMPLATE = lib
TARGET = xmms2qt
DEPENDPATH += .
INCLUDEPATH += . /opt/local/include/xmms2
CONFIG -= app_bundle
QT += network

CONFIG += link_pkgconfig
PKGCONFIG += xmms2-plugin

MOC_DIR     = .moc
OBJECTS_DIR = .obj

# Input
HEADERS += bindata.h \
           client.h \
           config.h \
           medialib.h \
           message.h \
           playback.h \
           playlist.h \
           result.h \
           object.h \
           propdict.h

SOURCES += bindata.cpp \
           client.cpp \
           config.cpp \
           medialib.cpp \
           message.cpp \
           playback.cpp \
           playlist.cpp \
           result.cpp \
