TEMPLATE = app

QT += qml quick widgets multimedia
CONFIG += c++11
QMAKE_CXXFLAGS += "-std=c++11"

SOURCES += main.cpp \
    filecontroll.cpp \
    imagefileclone.cpp \
    filepainter.cpp

RESOURCES += qml_brush.qrc \
    icons.qrc

DISTFILES += \
    Block/Block.qml\

HEADERS += \
    filecontroll.h \
    fileimageclone.h \
    filepainter.h

RCC_DIR = ./
