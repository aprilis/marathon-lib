TEMPLATE = app
CONFIG += console

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    CTcpFwd.cpp \
    Game.cpp \
    Info.cpp \
    PropertiesEditor.cpp \
    Test.cpp \
    wrapper.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    CTcpFwd.h \
    Game.h \
    Info.h \
    PropertiesEditor.h \
    Settings.h \
    Test.h \
    Config.h \
    wrapper.h

LIBS += -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

OTHER_FILES +=
