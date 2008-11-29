TEMPLATE=subdirs
CONFIG+=ordered
SUBDIRS=lib lib_static highlevel tests

lib_static.file = lib/libstatic.pro
lib_static.makefile = Makefile.static
