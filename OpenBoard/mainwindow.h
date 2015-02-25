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

#include <QDebug>

#include "glwidget.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

//    board
    void on_action_Show_triggered();
    void on_action_Hide_triggered();

//    settings
    void on_action_Font_triggered();
    void on_action_Color_triggered();
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
    void on_delayBtn_clicked();
    void on_backBtn_clicked();
    void on_animationBtn_clicked();
    void on_crossBtn_clicked();
    void on_colorBtn_clicked();
    void on_clearBtn_clicked();

//    longpress on button
    void on_delayBtn_pressed();
    void on_delayBtn_released();
    void show_pause_menu();


private:

    Ui::MainWindow  *ui;

    GLWidget        *mpGLWidget;

    QString         curFile;
    pSettings       mSettings;
    QTimer          *mTimer;


    bool saveFile();
    bool maybeSave();
};

#endif // MAINWINDOW_H
