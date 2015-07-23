QT -= declarative sensors multimedia multimediawidgets printsupport

QT       += qml widgets multimedia quick quickwidgets network webkitwidgets concurrent opengl

CONFIG += c++11
QMAKE_CXXFLAGS += "-std=c++11"
#CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
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
    openglwidget.cpp \
    ../TimeLine/listcontroll.cpp \
    drawSystem/drawelement.cpp \
    drawSystem/drawtext.cpp \
    ../Brush/brushcontroll.cpp \
    ../Brush/brushpainter.cpp \
    drawSystem/drawimage.cpp


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
    openglwidget.h \
    ../TimeLine/listcontroll.h \
    drawSystem/drawelement.h \
    drawSystem/drawtext.h \
    drawSystem/drawsystem.h \
    ../Brush/brushcontroll.h \
    ../Brush/brushpainter.h \
    drawSystem/drawimage.h

FORMS    += mainwindow.ui \
    youtube/logindialog.ui

RESOURCES += \
    icons.qrc \
    ../TimeLine/icons_timeLine.qrc \
    ../TimeLine/qml_timeLine.qrc \
    ../Brush/qml_brush.qrc
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
#   @ROMA
#
# LIBS += -lopengl32
#win32:CONFIG(release, debug|release): LIBS += -LC:/Users/roma/Documents/OpenBoad/OpenBoard/ThirdPart/lib/lib/ -lqtmel1
#else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Users/roma/Documents/OpenBoad/OpenBoard/ThirdPart/lib/lib/ -lqtmel1
#win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/Qt5.5.0/5.5/mingw492_32/bin/
#
#   @NICO
win32:CONFIG(release, debug|release): LIBS += -LF:/QA/QtMEL-master/libsQt5/ -lqtmel1
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/QA/QtMEL-master/libsQt5/ -lqtmeld1
#
VERSION = 0.4.0.0
QMAKE_TARGET_COMPANY = ITA
QMAKE_TARGET_PRODUCT = OpenBoard
QMAKE_TARGET_DESCRIPTION = Good program
QMAKE_TARGET_COPYRIGHT = @@@

DISTFILES +=
