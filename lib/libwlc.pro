TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    colorize.cpp \
    linuxutility.cpp \
    value.cpp \
    version.cpp

HEADERS += \
    colorize.h \
    debug.h \
    libwlc.h \
    linuxutility.h \
    value.h \
    version.h

