TEMPLATE = app
CONFIG += console

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    Game.cpp \
    Info.cpp \
    StreamWindow.cpp \
    GameState.cpp \
    Common.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    Game.h \
    Info.h \
    Config.h \
    StreamWindow.h \
    GameState.h \
    Common.h

LIBS += -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
