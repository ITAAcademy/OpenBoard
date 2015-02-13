#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

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
    void on_action_Font_triggered();

    void on_action_Reset_default_triggered();

    void on_action_Color_triggered();

    void on_action_delayTB_triggered();

private:
    Ui::MainWindow  *ui;
    QSlider         *sliderTB;
    QSpinBox        *spinBoxTB;
};

#endif // MAINWINDOW_H
