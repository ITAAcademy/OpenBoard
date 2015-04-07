QT       += widgets core gui opengl quick widgets quickwidgets  #av avwidgets

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    settings.cpp \
    qmlwidget.cpp \
    unit.cpp \
    unitsumbol.cpp \
    unitcommand.cpp


HEADERS  += mainwindow.h \
    glwidget.h \
    settings.h \
    qmlwidget.h \
    unit.h \
    unitsumbol.h \
    unitcommand.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
    RC_FILE = myapp.rc


greaterThan(QT_MAJOR_VERSION, 4) {
    LIBS += -L../../libsQt5
} else {
    LIBS += -L../../libsQt4
}

unix {
    DEFINES += QTMEL_NOT_INSTALLED
    LIBS += -lpthread -lX11
    QMAKE_CXXFLAGS += -std=c++0x
}

INCLUDEPATH += ThirdPart/include
LIBS += "C:/Users/HOME/Downloads/libV2/libV2/*.dll"


OTHER_FILES += \
    boarFunc.js \
    draw.qml
