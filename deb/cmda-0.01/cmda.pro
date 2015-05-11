TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    colorize.cpp \
    sheets.cpp

HEADERS += \
    colorize.h \
    debug.h \
    sheets.h

