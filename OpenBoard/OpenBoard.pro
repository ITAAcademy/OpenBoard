QT       += widgets core gui opengl quick widgets quickwidgets  #av avwidgets

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    settings.cpp \
    qmlwidget.cpp


HEADERS  += mainwindow.h \
    glwidget.h \
    settings.h \
    qmlwidget.h

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
LIBS += "C:/Projects/OpenBoard/OpenBoard/ThirdPart/*.dll"


OTHER_FILES += \
    boarFunc.js \
    draw.qml
