#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>

#include "glwidget.h"

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

    void on_menu_Board_triggered();
    void on_action_Show_triggered();
    void on_action_Hide_triggered();
    void on_action_Font_triggered();

    void on_action_Reset_default_triggered();

    void on_action_Color_triggered();

private:
    Ui::MainWindow *ui;
    GLWidget *mpGLWidget;
};

#endif // MAINWINDOW_H
