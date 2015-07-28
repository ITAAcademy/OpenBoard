TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11
QMAKE_CXXFLAGS += "-std=c++11"

SOURCES += main.cpp \
    brushpainter.cpp \
    brushcontroll.cpp \
    imageclone.cpp

RESOURCES += qml_brush.qrc

DISTFILES += \
    Block/Block.qml\

HEADERS += \
    brushpainter.h \
    brushcontroll.h \
    imageclone.h

RCC_DIR = ./
