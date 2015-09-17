TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11
QMAKE_CXXFLAGS += "-std=c++11"

SOURCES += main.cpp \
    effectscontroll.cpp \
    effect.cpp

RESOURCES += \
    qml_effects.qrc

DISTFILES += \
    Block/Block.qml\

HEADERS += \
    effectscontroll.h \
    effect.h

RCC_DIR = ./
