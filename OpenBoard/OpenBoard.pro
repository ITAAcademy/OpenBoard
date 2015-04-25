QT       += widgets core multimedia gui opengl quick widgets quickwidgets network webkitwidgets#av avwidgets

SOURCES += main.cpp\
    mainwindow.cpp \
    settings.cpp \
    qmlwidget.cpp \
    parser\unit.cpp \
    parser\unitsumbol.cpp \
    parser\unitcommand.cpp \
    parser\parser.cpp \
    editWidget/mytextedit.cpp \
    youtube/logindialog.cpp \
    youtube/oauth2.cpp \
    youtube/youtubewrapper.cpp


HEADERS  += mainwindow.h \
    settings.h \
    qmlwidget.h \
    parser\unit.h \
    parser\unitsumbol.h \
    parser\unitcommand.h \
    parser\parser.h \
    editWidget/mytextedit.h \
    youtube/logindialog.h \
    youtube/oauth2.h \
    youtube/youtubewrapper.h

FORMS    += mainwindow.ui \
    youtube/logindialog.ui

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
LIBS += "F:/QA/QtMEL-master/libsQt5/*.dll"


OTHER_FILES += \
    boarFunc.js \
    draw.qml \
    icons/12video icon.png
