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
    wrapper.cpp \
    HexMap.cpp \
    Log.cpp \
    StreamWindow.cpp \
    GameState.cpp \
    Maze.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    CTcpFwd.h \
    Game.h \
    Info.h \
    PropertiesEditor.h \
    Settings.h \
    Test.h \
    Config.h \
    wrapper.h \
    HexMap.h \
    Log.h \
    StreamWindow.h \
    GameState.h \
    Maze.h

LIBS += -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lgcc_s -lgcc
