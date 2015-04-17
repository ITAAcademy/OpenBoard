<<<<<<< HEAD
QT       += widgets core multimedia gui opengl quick widgets quickwidgets network webkitwidgets#av avwidgets
=======
QT       += widgets core gui opengl quick widgets quickwidgets network webkitwidgets#av avwidgets
>>>>>>> origin/yuriy

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
<<<<<<< HEAD

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
=======

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

#INCLUDEPATH += ThirdPart/include
#LIBS += "F:/QA/QtMEL-master/libsQt5/*.dll"

INCLUDEPATH += E:/Qt/QtMEL__/include
LIBS += "E:/Qt/QtMEL__/libsQt5/*.dll"

>>>>>>> origin/yuriy


OTHER_FILES += \
    boarFunc.js \
    draw.qml \
    icons/12video icon.png
