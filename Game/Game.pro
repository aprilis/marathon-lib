TEMPLATE = app
CONFIG += console

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    lib/CTcpFwd.cpp \
    lib/Game.cpp \
    lib/Info.cpp \
    lib/PropertiesEditor.cpp \
    lib/HexMap.cpp \
    lib/Log.cpp \
    lib/StreamWindow.cpp \
    lib/GameState.cpp \
    lib/Wrapper.cpp \
    lib/Common.cpp \
    examples/Maze.cpp \
    examples/HexMapExample.cpp \
    examples/EditorExample.cpp \
    examples/GeneralExample.cpp \
    MyGame.cpp \
    lib/StdinLog.cpp \
    lib/Console.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    lib/CTcpFwd.h \
    lib/Game.h \
    lib/Info.h \
    lib/PropertiesEditor.h \
    lib/Settings.h \
    lib/Config.h \
    lib/HexMap.h \
    lib/Log.h \
    lib/StreamWindow.h \
    lib/GameState.h \
    examples/Maze.h \
    lib/Wrapper.h \
    lib/Common.h \
    examples/HexMapExample.h \
    examples/EditorExample.h \
    examples/GeneralExample.h \
    MyGame.h \
    lib/StdinLog.h \
    lib/Console.h

LIBS += -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lgcc_s -lgcc
