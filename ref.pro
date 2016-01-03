TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = ref
#DEFINES += DEBUG

SOURCES += \
    src/main.cpp \
    lib/colorize.cpp \
    lib/linuxutility.cpp \
    lib/value.cpp \
    lib/version.cpp \
    src/setting.cpp \
    src/help.cpp \
    src/core.cpp

HEADERS += \
    src/debug.h \
    src/default.h \
    src/setting.h \
    lib/colorize.h \
    lib/debug.h \
    lib/libwlc.h \
    lib/linuxutility.h \
    lib/value.h \
    lib/version.h \
    src/help.h \
    src/core.h

