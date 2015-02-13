#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //fixed toolBar
    ui->mainToolBar->setMovable(false);
    //enable to hide toolBar (rightMouseClick)
    ui->mainToolBar->setContextMenuPolicy(Qt::CustomContextMenu);

    sliderTB = new QSlider(Qt::Horizontal, this);
    spinBoxTB = new QSpinBox(this);
    connect(spinBoxTB, SIGNAL(valueChanged(int)), sliderTB, SLOT(setValue(int)));
    connect(sliderTB, SIGNAL(valueChanged(int)), spinBoxTB, SLOT(setValue(int)));

    //sliderTB->setRange(0,400);
    //sliderTB->setTickInterval(1);
    ui->mainToolBar->addWidget(sliderTB);
    ui->mainToolBar->addWidget(spinBoxTB);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Font_triggered()
{   //call QtFontDialog & setFont to all elements (this)
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, QFont( "Times", 10 ), this);
    if (!ok)
        return;
    setFont(font);
}

void MainWindow::on_action_Reset_default_triggered()
{   //set font to menuBar: Times, 8 pt, normal
    ui->menuBar->setFont(QFont("Times",8,1,false));
}

void MainWindow::on_action_Color_triggered()
{   //call QtColorDialog
    QColor colorm;
    colorm = QColorDialog::getColor();
}

void MainWindow::on_action_delayTB_triggered()
{

}
