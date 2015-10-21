TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11
QMAKE_CXXFLAGS += "-std=c++11"

SOURCES += main.cpp \
    promptercontroll.cpp \
    prompteritem.cpp

RESOURCES += \
    qml_prompter.qrc

DISTFILES += \
    Block/Block.qml

HEADERS += \
    promptercontroll.h \
    prompteritem.h

RCC_DIR = ./
