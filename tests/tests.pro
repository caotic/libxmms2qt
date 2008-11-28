######################################################################
# Automatically generated by qmake (2.01a) Sat Mar 1 21:24:40 2008
######################################################################

QT += testlib network
CONFIG += qtestlib
CONFIG -= app_bundle
TEMPLATE = app
TARGET = 
DEPENDPATH += . ../lib
INCLUDEPATH += . ../lib
PRE_TARGETDEPS += ../lib/libxmmsclientqt.a
LIBS += ../lib/libxmmsclientqt.a
LIBPATH += ../lib
MOC_DIR     = .moc
OBJECTS_DIR = .obj

# workaround broken qmake
#LIBS += -lQtTest
#QMAKE_LFLAGS += -Wl,-rpath,..

CONFIG += link_pkgconfig
PKGCONFIG += xmms2-plugin xmms2-client
DEFINES += HAVE_CBINDINGS


# Input
HEADERS += test_url.h \
           test_playlist.h \
           test_bindata.h \
		   test_common.h \
		   test_class.h \
		   test_error.h \
		   test_coll.h

SOURCES += main.cpp \
           test_url.cpp \
           test_playlist.cpp \
           test_bindata.cpp \
		   test_error.cpp \
		   test_coll.cpp
