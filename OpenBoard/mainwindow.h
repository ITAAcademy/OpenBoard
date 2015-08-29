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

#include <QDebug>
#include "settings.h"
#include "parser/parser.h"
#include "editWidget/mytextedit.h"
#include "youtube/youtubewrapper.h"
#include "editWidget/keyloggertextedit.h"
#include "drawSystem/drawsystem.h"
#include "../NewProject/projectcreator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setViewState(VIEW_STATE state);
public slots:
    bool openFile(QString fileName);
    void doUndoRedoStart();
    void onCommandFocusSet();
    void onCommandFocusLost();
    void on_actionClear_drawing_triggered();
    void on_actionClear_drawingBuffer_triggered();

    void doUndoRedoEnd();
//    board
    void closeEvent(QCloseEvent* event);
    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
    void focusInEvent(QFocusEvent * event);
    bool event(QEvent *e);
    void on_action_Show_triggered();
    void on_action_Hide_triggered();
    void on_action_Play_triggered();
    void on_action_Pause_triggered();
    void on_action_Stop_triggered();
    void on_action_youTube_triggered();
    void on_action_Clear_TextEdit_triggered();
    void onTextChanged();
    void updateTextEditFromBlock(QPoint point);
    void updateVisibleTextEdit( bool state);

//    settings
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

    bool on_action_Save_Project_triggered();
    void on_action_Open_Project_triggered();
    void on_action_New_Project_triggered();

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
    void on_action_Record_to_file_triggered();
    void on_action_About_triggered();
    void updateCurrentTxt(); // not need
    void onStopShowLastDrawing();

    void on_speedBtn_pressed();
    void on_slider_speedTB_valueChanged(int value);
    void hideBoardSettings();
    void showBoardSettings();
    void setEnabledToolBar( bool status );
    void on_actionShow_last_drawing_triggered();

    void on_actionSave_drawing_triggered();

    void on_actionLoad_drawing_temp_triggered();

    void on_actionHide_editBox_triggered();

    void on_slider_speedTB_sliderReleased();
    void on_block_text_buttons_toolbar(bool tt);
    void on_blockRightToolbar_exceptPlayPauseStop(bool tt);
    void enablingBoardFontColor(QPoint);
    void setEnabledBoardFontColor(bool);


private:
    bool may_to_enable_BoardFontColor;
      bool firstNewProjectCreating = true;
    bool isRecordToFile = false;
    bool changeone;
   QString directory;
QAction *a_play,*a_clear_textedit,*a_pause,*a_stop,*a_font_canvas,*a_color_canvas,
*a_record_to_file,*a_undo,*a_redo,*a_show,*a_hide,*a_clear_drawing,*a_clear_drawingBuffer,
*a_show_last_drawing,*a_save_drawing ,*a_open_project,*a_new_project, *a_save_project,*a_exit,
*a_cut,*a_copy,*a_paste,*a_select_all,*a_search,*a_send_to_youtube;
    Ui::MainWindow  *ui;
QMessageBox messAbout;
 //   GLWidget        *mpGLWidget;
    OGLWidget       *mpOGLWidget;
    YouTubeWrapper *youtube;
    QToolBar *toolBar;
    QToolBar *toolBarBoard;
    Parser          mParser;
    MyTextEdit       *textEdit = NULL;
    KeyloggerTE *commandTextEdit = NULL;
    QTimer onTextChangeUpdateTimer;
   // ListControll timeLine;
    QList <DrawElement*> drawElements;

    int drawCounter;
    bool isCommandTextEditFocused = false;
    QString         curFile;
    QString         curProjectFile;
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

    volatile bool isActive = true; // active main windows?
    ProjectStartupSetting curentState;
    void updateEditWidgets(bool forceEnabled = false);
public slots:
    ProjectStartupSetting getCurentState();
    Q_INVOKABLE void setCurentState(ProjectStartupSetting state);
    void keyEventSlot(QKeyEvent *event);

private slots:
    void updateBlockFromTextEdit();
    void on_actionAbout_Qt_triggered();
};

#endif // MAINWINDOW_H
