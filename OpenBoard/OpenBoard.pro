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

INCLUDEPATH += G:/havok/cv/opencv/build/include
LIBS += "G:/havok/cv/opencv/build/x86/vc10/bin/*.dll"


INCLUDEPATH += F:/QA/QtMEL-master/include
LIBS += "F:/QA/QtMEL-master/libsQt5/*.dll"



OTHER_FILES += \
    boarFunc.js \
    draw.qml
