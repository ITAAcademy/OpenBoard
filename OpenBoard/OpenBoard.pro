QT -= declarative sensors multimedia multimediawidgets printsupport

QT       += widgets multimedia quick quickwidgets network webkitwidgets concurrent opengl
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
SOURCES += main.cpp\
    mainwindow.cpp \
    settings.cpp \
    parser\unit.cpp \
    parser\unitsumbol.cpp \
    parser\unitcommand.cpp \
    parser\parser.cpp \
    editWidget/mytextedit.cpp \
    youtube/logindialog.cpp \
    youtube/oauth2.cpp \
    youtube/youtubewrapper.cpp \
    encoder/videorencoder.cpp \
    editWidget/keyloggertextedit.cpp \
    openglwidget.cpp


HEADERS  += mainwindow.h \
    settings.h \
    parser\unit.h \
    parser\unitsumbol.h \
    parser\unitcommand.h \
    parser\parser.h \
    editWidget/mytextedit.h \
    youtube/logindialog.h \
    youtube/oauth2.h \
    youtube/youtubewrapper.h \
    encoder/videorencoder.h \
    editWidget/keyloggertextedit.h \
    openglwidget.h

FORMS    += mainwindow.ui \
    youtube/logindialog.ui

RESOURCES += \
    icons.qrc
    RC_FILE = myapp.rc

#unix {
#    DEFINES += QTMEL_NOT_INSTALLED
#    LIBS += -lpthread -lX11
#    QMAKE_CXXFLAGS += -std=c++0x
#}

INCLUDEPATH += ThirdPart/include
#LIBS += "F:/QA/QtMEL-master/libsQt5/*.dll"


OTHER_FILES += \
    boarFunc.js \
    draw.qml \
    icons/12video icon.png

win32:CONFIG(release, debug|release): LIBS += -LC:/Users/roma/Downloads/OpenDeploy_v0.26/OpenDeploy_v0.26/ -lqtmel1
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Users/roma/Downloads/OpenDeploy_v0.26/OpenDeploy_v0.26/ -lqtmel1


VERSION = 0.4.0.0
QMAKE_TARGET_COMPANY = ITA
QMAKE_TARGET_PRODUCT = OpenBoard
QMAKE_TARGET_DESCRIPTION = Good program
QMAKE_TARGET_COPYRIGHT = @@@
