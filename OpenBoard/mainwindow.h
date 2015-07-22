#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QColor>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QSettings>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QMenu>
#include <QAction>
#include "openglwidget.h"
#include "../TimeLine/listcontroll.h"

#include <QDebug>
#include "settings.h"
#include "parser/parser.h"
#include "editWidget/mytextedit.h"
#include "youtube/youtubewrapper.h"
#include "editWidget/keyloggertextedit.h"
#include "drawSystem/drawsystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    bool openFile(QString fileName);
    void doUndoRedoStart();
    void onCommandFocusSet();
    void onCommandFocusLost();
 void doUndoRedoEnd();
//    board
    void closeEvent(QCloseEvent* event);
    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
    void on_action_Show_triggered();
    void on_action_Hide_triggered();
    void on_action_Play_triggered();
    void on_action_Pause_triggered();
    void on_action_Stop_triggered();
    void on_action_youTube_triggered();

    void onTextChanged();

//    settings
    void a_record_to_file_triggered();
    void on_action_Font_triggered();
    void on_action_Color_triggered();
    void on_action_Board_Font_triggered();
    void on_action_Board_Color_triggered();
    void on_action_Reset_default_triggered();

//    edit
    void on_action_Undo_triggered();
    void on_action_Redo_triggered();
    void on_action_Cut_triggered();
    void on_action_Copy_triggered();
    void on_action_Paste_triggered();
    void on_action_Select_all_triggered();
    void on_action_Find_triggered();
        void search();

//    file
    void on_action_Exit_triggered();
    bool on_action_Save_as_triggered();
    bool on_action_Save_triggered();
    void on_action_Open_triggered();
    void on_action_New_triggered();

//    toolbar
    void on_backBtn_clicked();
    void on_animationBtn_clicked();
    void on_crossBtn_clicked();
    void on_clearBtn_clicked();

//    press on button delay
    void on_delayBtn_pressed();
    void delay_released();
    void show_pause_menu();

//    press on button color
    void on_colorBtn_pressed();
    void on_colorBtn_released();
    void on_colorBtn_clicked();
    void show_color_dialog();

private slots:
    void on_actionRecord_to_file_triggered();
    void on_action_About_triggered();

    void on_speedBtn_pressed();
    void on_slider_speedTB_valueChanged(int value);
    void hideBoardSettings();
    void showBoardSettings();
    void setEnabledToolBar( bool status );
private:
    bool changeone;
   QString directory;
QAction *a_play,*a_pause,*a_stop,*a_font_canvas,*a_color_canvas,*a_record_to_file,*a_undo,*a_redo,*a_show,*a_hide;
    Ui::MainWindow  *ui;
QMessageBox messAbout;
 //   GLWidget        *mpGLWidget;
    OGLWidget       *mpOGLWidget;
    YouTubeWrapper *youtube;
    QToolBar *toolBar;
    Parser          mParser;
    MyTextEdit       *textEdit;
    KeyloggerTE *commandTextEdit;
    ListControll timeLine;
    QList <DrawElement*> drawElements;

    int drawCounter;
    bool isCommandTextEditFocused = false;
    QString         curFile;
    pSettings       mSettings;
    QTimer          *mTimer;
    QTimer          *mTimerClr;
    QString         textColorName;
    QColor          colorPkr;
    QString         inputText;
    int lastInpuDelay;
    QList <Unit*>mUnitList;
//    QThread drawThread;
    bool saveFile();
    bool maybeSave();

    bool play = false;


};

#endif // MAINWINDOW_H
