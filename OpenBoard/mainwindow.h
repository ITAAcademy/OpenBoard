#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    GLWidget *mpGLWidget;
};

#endif // MAINWINDOW_H
