QT       += qml core widgets multimedia quick quickwidgets network webkitwidgets concurrent opengl

CONFIG += c++11
QMAKE_CXXFLAGS += "-std=c++11"

TEMPLATE = app

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
    ../TimeLine/imageprovider.cpp \
    drawSystem/drawimage.cpp \
    ../Brush/imageclone.cpp \
    drawSystem/drawbrush.cpp \
    ../NewProject/projectcreator.cpp \
    encoder/videodecoder.cpp \
    encoder/ffmpeghelp.cpp \
    drawSystem/drawvideo.cpp \
    encoder/audiodecoder.cpp \
    shaderprogramwrapper.cpp \
    shadereffect.cpp \
    shadertest.cpp \
    editWidget/codeeditor.cpp \
    drawSystem/drawaudio.cpp\
    GLWidget/grid.cpp\
    ../TimeLine/group.cpp \
    ../FileManager/filecontroll.cpp \
    ../FileManager/filepainter.cpp \
    ../Effects/effect.cpp \
    ../Effects/effectscontroll.cpp \
    ../Prompter/prompteritem.cpp    \
    ../Prompter/promptercontroll.cpp \
    ../Prompter/audiorecorder.cpp




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
    ../TimeLine/imageprovider.h \
    drawSystem/drawimage.h \
    ../Brush/imageclone.h \
    ../NewProject/projectcreator.h \
    encoder/videodecoder.h \
    encoder/ffmpeg.h \
    encoder/ffmpeghelp.h \
    drawSystem/drawvideo.h \
    encoder/audiodecoder.h \
    shaderprogramwrapper.h \
    shadereffect.h \
    shadertest.h \
    editWidget/codeeditor.h \
    drawSystem/drawbrush.h\
    drawSystem/drawaudio.h\
    GLWidget/grid.h\
    ../TimeLine/group.h \
    ../FileManager/filecontroll.h \
    ../FileManager/filepainter.h \
    ../Effects/effect.h \
    ../Effects/effectscontroll.h \
    ../Prompter/prompteritem.h  \
    ../Prompter/promptercontroll.h \
    ../Prompter/audiorecorder.h

FORMS    += mainwindow.ui \
    youtube/logindialog.ui \
    shadertest.ui

RESOURCES += \
    icons.qrc \
    ../TimeLine/icons_timeLine.qrc \
    ../TimeLine/qml_timeLine.qrc \
    ../Brush/qml_brush.qrc \
    ../NewProject/qml_new_project.qrc \
    shaders.qrc \
    ../FileManager/qml_filemanager.qrc \
    ../Effects/qml_effects.qrc \
    ../Prompter/qml_prompter.qrc
    RC_FILE = myapp.rc

#unix {
#    DEFINES += QTMEL_NOT_INSTALLED
#    LIBS += -lpthread -lX11
#    QMAKE_CXXFLAGS += -std=c++0x
#}

OTHER_FILES += \
    boarFunc.js \
    draw.qml \
    icons/12video icon.png
#   @ROMA
#
 LIBS += -lopengl32

#win32:CONFIG(release, debug|release): LIBS += -LC:/Users/roma/Documents/OpenBoad/OpenBoard/ThirdPart/lib/lib/ -lqtmel1
#else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Users/roma/Documents/OpenBoad/OpenBoard/ThirdPart/lib/lib/ -lqtmel1
#win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/Qt5.5.0/5.5/mingw492_32/bin/
#
#   @NICO
#win32:CONFIG(release, debug|release): LIBS += -LF:/QA/QtMEL-master/libsQt5/ -lqtmel1
#else:win32:CONFIG(debug, debug|release): LIBS += -LF:/QA/QtMEL-master/libsQt5/ -lqtmeld1
#
#   @GLOBAL
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ThirdPart/lib/ -lqtmel1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ThirdPart/lib/ -lqtmeld1

VERSION = 0.4.0.0
QMAKE_TARGET_COMPANY = ITA
QMAKE_TARGET_PRODUCT = OpenBoard
QMAKE_TARGET_DESCRIPTION = Good program
QMAKE_TARGET_COPYRIGHT = @@@

INCLUDEPATH += $$PWD/ThirdPart/include
DEPENDPATH += $$PWD/ThirdPart/include

INCLUDEPATH += $$PWD\include
LIBS += "$$PWD/bin/*.dll"

RCC_DIR = ../

DISTFILES += \
    frag_alpha.fsh \
    frag_alpha.frag \
    alpha.frag \
    alpha.vert \
    spin.frag \
    spin.vert \
    cross.frag \
    cross.vert \
    ../FileManager/main_filemanager.qml \
    ../Effects/Content/Thumbs.db \
    ../Effects/MainForm.ui.qml \
    ../Effects/Content/test.jpg \
    ../Effects/Content/arrow_right_24.png \
    ../Effects/Content/brush_skeen.png \
    ../Effects/Content/cancel_32.png \
    ../Effects/Content/plus_button_32.png \
    ../Effects/Preset/Brushes/standart.PNG \
    ../Effects/Content/BrushSettingPages/DoubleSlider.qml \
    ../Effects/Content/BrushSettingPages/EffectAlpha.qml \
    ../Effects/Content/BrushSettingPages/FullSlider.qml \
    ../Effects/Content/Button.qml \
    ../Effects/Content/FullSlider.qml \
    ../Effects/Content/Separator.qml \
    ../Effects/Listbox.qml \
    ../Effects/ListboxControl.qml \
    ../Effects/mainEffectWindow.qml \
    ../Prompter/EffectsManager.pro.user \
    ../Prompter/Prompter.pro.user \
    ../Prompter/mainWindow.qml \
    ../Prompter/WindowDragingMouseArea.qml

SUBDIRS += \
    ../Effects/EffectsManager.pro \
    ../Prompter/Prompter.pro
