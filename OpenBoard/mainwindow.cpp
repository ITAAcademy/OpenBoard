#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mpGLWidget = new GLWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_menu_Board_triggered()
{

}
void MainWindow::on_action_Show_triggered()
{
    mpGLWidget->setFixedSize(450,450);

    mpGLWidget->move(pos().x() + width(), pos().y());

    mpGLWidget->show();
}
void MainWindow::on_action_Hide_triggered()
{
    mpGLWidget->hide();
}
