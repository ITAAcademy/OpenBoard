#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TIMER_VALUE         300
#define GLWIDGET_SIZE       640,480
#define WINDOW_POS          80,100,760,560
#define WINDOW_MARGING          20
                   //CENTER 335,100,760,558

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //drawThread.start();

//    connect(&drawThread, SIGNAL(started()), this, SLOT(myfunction())); //cant have parameter sorry, when using connect

    mpQmlWidget = new QmlWidget();
   // mpQmlWidget->moveToThread(&drawThread);
    textEdit = new MyTextEdit(QColor("#000000"), QColor("#FF0000"), ui->centralWidget);
    textEdit->setObjectName(QStringLiteral("textEdit"));
    textEdit->setEnabled(true);

    ui->verticalLayout->addWidget(textEdit,-1);
    connect(ui->button_Delay, SIGNAL(pressed()), this, SLOT(delay_released()));
    //connect(QColorDialog, SIGNAL(finished()), this, SLOT(on_colorBtn_released()));
    connect(ui->button_Find, SIGNAL(pressed()), this, SLOT(search()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    connect(ui->actionSend_to_youTube, SIGNAL( triggered()), this, SLOT (on_action_youTube_triggered()));

    ui->widget_Find->setVisible(false);
    ui->widget_delayTB->setVisible(false);
    lastInpuDelay = ui->slider_speedTB->value();
  //  drawWidget->setVisible(false);
  //  on_action_Show_triggered();

    ui->action_Board_Color->setEnabled(false);
    ui->action_Board_Font->setEnabled(false);

    if(mSettings.FirstRun())
        {
        setGeometry(QRect(WINDOW_POS));
        setFont(QFont("Tahoma",10,1,false));

        mSettings.setMainWindowRect(geometry());
        mSettings.setMainWindowTitle(windowTitle());
        mSettings.setMainWindowFont(font());
        mSettings.setMainWindowColor(this->textEdit->textColor());
        QColor col (255,255,255);
        mSettings.setBoardFontColor(QColor(255,255,255));


        QFont sfont("Tahoma", 10);
        mSettings.setBoardFont(QFont("Tahoma",20,1,false));
        mSettings.saveSettings();
    }

       setWindowTitle(mSettings.getMainWindowTitle());
       setGeometry(mSettings.getMainWindowRect());
       this->textEdit->setColOrigin(mSettings.getMainWindowColor());
       this->textEdit->setFont(mSettings.getMainWindowFont());

       toolBar= new QToolBar;
       toolBar->addAction(QPixmap(":/icons/new-file-icon.png").scaled(QSize(16, 16)), "New", this, SLOT(on_action_New_triggered()));
       toolBar->addAction(QPixmap(":/icons/open-file-icon.png").scaled(QSize(16, 16)), "Open", this, SLOT(on_action_Open_triggered()));
       toolBar->addAction(QPixmap(":/icons/Save-icon.png").scaled(QSize(16, 16)), "Save", this, SLOT(on_action_Save_triggered()));
       toolBar->addAction(QPixmap(":/icons/Save-as-icon.png").scaled(QSize(16, 16)), "Save as", this, SLOT(on_action_Save_as_triggered()));
       toolBar->addAction(QPixmap(":/icons/Close-2-icon.png").scaled(QSize(16, 16)), "Exit", this, SLOT(on_action_Exit_triggered()));
       toolBar->addSeparator();



       a_undo = new QAction(this);
       a_undo->setEnabled(true);
       a_undo->setIcon(QPixmap(":/icons/undo-icon.png").scaled(QSize(16, 16)));
       a_undo->setStatusTip(tr("Undo"));
       connect(a_undo,SIGNAL(triggered()),this,  SLOT(on_action_Undo_triggered()));
       toolBar->addAction(a_undo);
              //toolBar->addAction(QPixmap(":/icons/undo-icon.png").scaled(QSize(16, 16)), "Undo", this, SLOT(on_action_Undo_triggered()));
       a_redo = new QAction(this);
       a_redo->setEnabled(true);
       a_redo->setIcon(QPixmap(":/icons/redo-icon.png").scaled(QSize(16, 16)));
       a_redo->setStatusTip(tr("Redo"));
       connect(a_redo,SIGNAL(triggered()),this,  SLOT(on_action_Redo_triggered()));
       toolBar->addAction(a_redo);
   //    toolBar->addAction(QPixmap(":/icons/redo-icon.png").scaled(QSize(16, 16)), "Redo", this, SLOT(on_action_Redo_triggered()));




       toolBar->addAction(QPixmap(":/icons/cut-icon.png").scaled(QSize(16, 16)), "Cut", this, SLOT(on_action_Cut_triggered()));
       toolBar->addAction(QPixmap(":/icons/Copy-icon.png").scaled(QSize(16, 16)), "Copy", this, SLOT(on_action_Copy_triggered()));
       toolBar->addAction(QPixmap(":/icons/Paste-icon.png").scaled(QSize(16, 16)), "Paste", this, SLOT(on_action_Paste_triggered()));
       toolBar->addAction(QPixmap(":/icons/select_all.png").scaled(QSize(16, 16)), "Select all", this, SLOT(on_action_Select_all_triggered()));
       toolBar->addAction(QPixmap(":/icons/search-icon.png").scaled(QSize(16, 16)), "Search", this, SLOT(on_action_Find_triggered()));
       toolBar->addSeparator();

       toolBar->addAction(QPixmap(":/icons/font-x-generic-icon.png").scaled(QSize(16, 16)), "Font text area", this, SLOT(on_action_Font_triggered()));
       toolBar->addAction(QPixmap(":/icons/colors-icon.png").scaled(QSize(16, 16)), "Color text area", this, SLOT(on_action_Color_triggered()));

       a_font_canvas = new QAction(this);
       a_font_canvas->setEnabled(false);
       a_font_canvas->setIcon(QPixmap(":/icons/font-x-generic-icon.png").scaled(QSize(16, 16)));
       a_font_canvas->setStatusTip(tr("Font canvas"));
       connect(a_font_canvas,SIGNAL(triggered()),this,  SLOT(on_action_Board_Font_triggered()));
       toolBar->addAction(a_font_canvas);

       a_color_canvas = new QAction(this);
       a_color_canvas->setEnabled(false);
       a_color_canvas->setIcon(QPixmap(":/icons/colors-icon.png").scaled(QSize(16, 16)));
       a_color_canvas->setStatusTip(tr("Font canvas"));
       connect(a_color_canvas,SIGNAL(triggered()),this,  SLOT(on_action_Board_Color_triggered()));
       toolBar->addAction(a_color_canvas);

       toolBar->addAction(QPixmap(":/icons/default_programs.png").scaled(QSize(16, 16)), "Reset default", this, SLOT(on_action_Reset_default_triggered()));
       toolBar->addSeparator();

       a_show = new QAction(this);
       a_show->setEnabled(true);
       a_show->setIcon(QPixmap(":/icons/gnome_show_desktop.png").scaled(QSize(16, 16)));
       a_show->setStatusTip(tr("Show canvas"));
       connect(a_show,SIGNAL(triggered()),this,  SLOT(on_action_Show_triggered()));
       toolBar->addAction(a_show);
      // toolBar->addAction(QPixmap(":/icons/gnome_show_desktop.png").scaled(QSize(16, 16)), "Show canvas", this, SLOT(on_action_Show_triggered()));


               a_hide = new QAction(this);
               a_hide->setEnabled(false);
               a_hide->setIcon(QPixmap(":/icons/hide_icon.png").scaled(QSize(16, 16)));
               a_hide->setStatusTip(tr("Show canvas"));
               connect(a_hide,SIGNAL(triggered()),this,  SLOT(on_action_Hide_triggered()));
               toolBar->addAction(a_hide);
      // toolBar->addAction(QPixmap(":/icons/hide_icon.png").scaled(QSize(16, 16)), "Hide canvas", this, SLOT(on_action_Hide_triggered()));

       a_play = new QAction(this);
       a_play->setEnabled(false);
       a_play->setIcon(QPixmap(":/icons/play-8-icon.png").scaled(QSize(16, 16)));
       a_play->setStatusTip(tr("Play"));
       connect(a_play,SIGNAL(triggered()),this,  SLOT(on_action_Play_triggered()));
       toolBar->addAction(a_play);

       a_pause = new QAction(this);
       a_pause->setEnabled(false);
       a_pause->setIcon(QPixmap(":/icons/pause-icon.png").scaled(QSize(16, 16)));
       a_pause->setStatusTip(tr("Pause"));
       connect(a_pause,SIGNAL(triggered()),this,  SLOT(on_action_Pause_triggered()));
       toolBar->addAction(a_pause);

       a_stop = new QAction(this);
       a_stop->setEnabled(false);
       a_stop->setIcon(QPixmap(":/icons/stop_icon.png").scaled(QSize(16, 16)));
       a_stop->setStatusTip(tr("Stop"));
       connect(a_stop,SIGNAL(triggered()),this,  SLOT(on_action_Stop_triggered()));
       toolBar->addAction(a_stop);

       a_record_to_file = new QAction(this);
       a_record_to_file->setEnabled(false);
       a_record_to_file->setIcon(QPixmap(":/icons/12video icon.png").scaled(QSize(16, 16)));
       a_record_to_file->setStatusTip(tr("Record in file"));
       a_record_to_file->setCheckable(true);
       a_record_to_file->setChecked(false);
       connect(a_record_to_file,SIGNAL(triggered()),this,  SLOT(a_record_to_file_triggered()));
       toolBar->addAction(a_record_to_file);

      // toolBar->addAction(QPixmap(":/icons/12video icon.png").scaled(QSize(16, 16)), "Record in file", this, SLOT(on_actionRecord_to_file_triggered()));  //yvguj vgju ftu
       toolBar->addAction(QPixmap(":/icons/youtube_icon.png").scaled(QSize(16, 16)), "Send to YouTube", this, SLOT(on_action_youTube_triggered()));
       toolBar->addAction(QPixmap(":/icons/info.png").scaled(QSize(16, 16)), "About", this, SLOT(on_action_About_triggered()));
       toolBar->setMovable(false);
//toolBar->setAllowedAreas(Qt::BottomToolBarArea);

        addToolBar(Qt::TopToolBarArea, toolBar);
     // toolBar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{
    mSettings.setMainWindowRect(geometry());
    //drawThread.quit();
    if(toolBar != NULL)
        delete toolBar;

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent*)
{
   // mpGLWidget->close();
    if(mpQmlWidget != NULL)
    {
      //  mpQmlWidget->stopAnimated();
        mpQmlWidget->close();
        while( mpQmlWidget->status() != QmlWidget::STOP )
            qApp->processEvents();
        //mpQmlWidget->abor
        delete mpQmlWidget;
    }
    qDebug() << "Close drawWidget";
    //delete mpGLWidget;
}

void MainWindow::on_action_Show_triggered()
{
    showBoardSettings();
    a_show->setEnabled(false);
    ui->action_Show->setEnabled(false);
    a_hide->setEnabled(true);
    ui->action_Hide->setEnabled(true);

/*
 * QML
*/
    if(mpQmlWidget != 0)
        delete mpQmlWidget;
    mpQmlWidget = new QmlWidget();
    mpQmlWidget->show();
    mpQmlWidget->setDelay(1000/lastInpuDelay);
    mpQmlWidget->setFixedSize(GLWIDGET_SIZE);
    mpQmlWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
    ui->action_Pause->setEnabled(true);
    ui->action_Play->setEnabled(true);
    ui->action_Stop->setEnabled(true);
    //mpQmlWidget.create();
    mpQmlWidget->setDrawText(textEdit->toPlainText());
    /*
     * init
     */

    mpQmlWidget->setTextFont(mSettings.getBoardFont());
    mpQmlWidget->setMainFillColor(mSettings.getBoardFontColor());

    emit mpQmlWidget->drawTextChanged();

/*
    mpGLWidget->setFixedSize(GLWIDGET_SIZE);
    mpGLWidget->move(pos().x() + width(), pos().y());
    mpGLWidget->show();
*/
    a_play->setEnabled(true);
    a_pause->setEnabled(true);
    a_stop->setEnabled(true);
    a_font_canvas->setEnabled(true);
    a_color_canvas->setEnabled(true);
    a_record_to_file->setEnabled(true);
    a_undo->setEnabled(true);
    a_redo->setEnabled(true);

    ui->action_Pause->setEnabled(false);
    a_pause->setEnabled(false);
}

void MainWindow::on_action_Hide_triggered()
{
    if(mpQmlWidget->getStatus() == mpQmlWidget->PLAY || mpQmlWidget->getStatus() == mpQmlWidget->PAUSE)
      //  mpQmlWidget->stopAnimated();
    emit   on_action_Stop_triggered();
    mpQmlWidget->hide();
    mpQmlWidget->close();
    // delete mpQmlWidget;
    ui->action_Pause->setEnabled(false);
    ui->action_Play->setEnabled(false);
    ui->action_Stop->setEnabled(false);
    hideBoardSettings();

    a_hide->setEnabled(false);
    ui->action_Hide->setEnabled(false);
    a_show->setEnabled(true);
    ui->action_Show->setEnabled(true);
    a_play->setEnabled(false);
    a_pause->setEnabled(false);
    a_stop->setEnabled(false);
    a_font_canvas->setEnabled(false);
    a_color_canvas->setEnabled(false);
    a_record_to_file->setEnabled(false);
    a_undo->setEnabled(false);
   a_redo->setEnabled(false);
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    mpQmlWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    mpQmlWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
}

void MainWindow::on_action_Font_triggered()
{   //call QtFontDialog & setFont to all elements (this)
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, QFont( "Times", 10 ), this);
    if (!ok)
        return;
  // setFont(font);
    textEdit->setFont(font);

    mSettings.setMainWindowFont(font);
    ///!!!!!!!!!
    /*// bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, QFont("Tahoma",10,1,false), this);
    if (!ok)
        return;

    QString qmlFont;
    QFontInfo fontInf(font);
    qmlFont = QString::number(fontInf.pointSize()) + "pt \"" + font.family() + "\"";
    mpQmlWidget.setFont(qmlFont);   */
}

//!!!!!!!!!!!!!!!!!!
//!
void MainWindow::on_action_Board_Font_triggered()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, QFont("Tahoma",10,1,false), this);
    if (!ok)
        return;

 /*   QString qmlFont;
    QFontInfo fontInf(font);
    qmlFont = QString::number(fontInf.pointSize()) + "pt \"" + font.family() + "\"";*/
    mpQmlWidget->setTextFont(font);
   // mSettings.setBoardFont(font);
   mSettings.setBoardFont(font);
}

void MainWindow::on_action_Reset_default_triggered()
{
    QFont font = (QFont("Tahoma",10,1,false));
        ui->menuBar->setFont(font);
        textEdit->setFont(font);
        textEdit->setTextColor("#000000");
        QString temp = textEdit->toPlainText();
        textEdit->clear();
        textEdit->insertPlainText(temp);

        ui->action_Show->setEnabled(false);
        a_show->setEnabled(false);
       // setFont(font);
}

void MainWindow::on_action_Color_triggered()
{   //call QtColorDialog
    QColor colorm;
    colorm = QColorDialog::getColor();
    //!!!!!!!!!!!
    QString col = colorm.name();
        textEdit->setTextColor(col);
        textEdit->setColOrigin(colorm);
        QString temp = textEdit->toPlainText();
        textEdit->clear();
        textEdit->insertPlainText(temp);

      mSettings.setMainWindowColor(colorm);
      a_show->setEnabled(false);
      ui->action_Show->setEnabled(false);
}

//!!!!!!!!!!!!!
//!
 void MainWindow::on_action_Board_Color_triggered()
{
    QColor colorm;
    colorm = QColorDialog::getColor();
   // QString col = colorm.name();
    mpQmlWidget->setMainFillColor(colorm);
    mSettings.setBoardFontColor(colorm);


}

void MainWindow::on_action_Undo_triggered()
{
    textEdit->undo();
}

void MainWindow::on_action_Redo_triggered()
{
    textEdit->redo();
}

void MainWindow::on_action_Cut_triggered()
{
    textEdit->cut();
}

void MainWindow::on_action_Copy_triggered()
{
    textEdit->copy();
}

void MainWindow::on_action_Paste_triggered()
{
    textEdit->paste();
}


void MainWindow::on_action_Select_all_triggered()
{
    if(textEdit->hasFocus()) {
        textEdit->selectAll();
    }
    if(ui->lineEdit_Find->hasFocus()) {
        ui->lineEdit_Find->selectAll();
    }
}

void MainWindow::on_action_Find_triggered()
{
//    a temporary solution
//    ui->widget_delayTB->setVisible(!ui->widget_delayTB->isVisible());
//    a temporary solution

    ui->widget_Find->setVisible(!ui->widget_Find->isVisible());
    if(ui->widget_Find->isVisible()) {
        ui->lineEdit_Find->setFocus();
      //  ui->lineEdit_Find->selectAll();
     //   ui->lineEdit_Find->setSelection(0,100);
    }
    else {

        textEdit->setFocus();

        QString str = ui->lineEdit_Find->text();
            QList<QTextEdit::ExtraSelection> extraSelections;
            textEdit->moveCursor(QTextCursor::Start);
            QColor color = QColor(Qt::white).lighter(130);
           while(textEdit->find(str))
                {
                    QTextEdit::ExtraSelection extra;
                    extra.format.setBackground(color);

                    extra.cursor = textEdit->textCursor();
                    extraSelections.append(extra);
                }
               textEdit->setExtraSelections(extraSelections);
    }
}

void MainWindow::on_action_Exit_triggered()
{
    if(maybeSave())
    {
        this->close();
    }
}

bool MainWindow::saveFile()
{

    QFile file(curFile);
    if(file.open(QFile::WriteOnly))
    {
        file.write(textEdit->toPlainText().toUtf8());
        return true;
    }
    else
    {
        QMessageBox::warning(this, "Error",
                             tr("Ощибка записи файла") //щ
                             .arg(curFile)
                             .arg(file.errorString()));
        return false;
    }
}

bool MainWindow::maybeSave()
{
    if(textEdit->document()->isModified())
    {
        QMessageBox::StandardButton ret =
                QMessageBox::warning(
                    this,
                    "File",
                    tr("The document has been changed, save?"),
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (ret == QMessageBox::Yes)
        {
          return on_action_Save_triggered();
        }
        else  if(ret == QMessageBox::Cancel)
           return false;

    }
    return true;
}

void MainWindow::search()
{
    QString str = ui->lineEdit_Find->text();

    QList<QTextEdit::ExtraSelection> extraSelections;

    textEdit->moveCursor(QTextCursor::Start);
    QColor color = QColor(Qt::yellow).lighter(130);

    if(ui->check_case_sensitive->isChecked() == false
            && ui->check_whole_words->isChecked() == false)
    {
        while(textEdit->find(str))
        {
            QTextEdit::ExtraSelection extra;
            extra.format.setBackground(color);

            extra.cursor = textEdit->textCursor();
            extraSelections.append(extra);
        }
    }

    else if(ui->check_case_sensitive->isChecked() == true
            && ui->check_whole_words->isChecked() == false)
    {
        while(textEdit->find(str, QTextDocument::FindCaseSensitively))
        {
            QTextEdit::ExtraSelection extra;
            extra.format.setBackground(color);

            extra.cursor = textEdit->textCursor();
            extraSelections.append(extra);
        }
    }

    else if(ui->check_case_sensitive->isChecked() == false
            && ui->check_whole_words->isChecked() == true)
    {
        while(textEdit->find(str, QTextDocument::FindWholeWords))
        {
            QTextEdit::ExtraSelection extra;
            extra.format.setBackground(color);

            extra.cursor = textEdit->textCursor();
            extraSelections.append(extra);
        }
    }

    else if (ui->check_case_sensitive->isChecked() == true
            && ui->check_whole_words->isChecked() == true)
    {
        while(textEdit->find(str, QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively))
        {
            QTextEdit::ExtraSelection extra;
            extra.format.setBackground(color);

            extra.cursor = textEdit->textCursor();
            extraSelections.append(extra);
        }
    }

    textEdit->setExtraSelections(extraSelections);
}

bool MainWindow::on_action_Save_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "D:/",
                                                    tr("Text Files (*.txt);;All Files (*.*)"));

    if(!fileName.isEmpty())
    {
      curFile = fileName;
      return saveFile();
    }
    return false;
}

bool MainWindow::on_action_Save_triggered()
{
    if (curFile.isEmpty())
        return on_action_Save_as_triggered();
    else
        return saveFile();
}

void MainWindow::on_action_Open_triggered()
{
    if (maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "D:/",
                                                              tr("Text Files (*.txt);;All Files (*.*)"));
        if(!fileName.isEmpty())
        {
            QFile file(fileName);
            if(file.open(QFile::ReadOnly))
            {
                textEdit->setPlainText(file.readAll());
            }
            else
            {
                QMessageBox::warning(this, "Error",tr("Ошыбка открытия файла")); //щ
            }
        }
    }
}

void MainWindow::on_action_New_triggered()
{
    if (maybeSave())
    {
        textEdit->clear();
    }

}

void MainWindow::on_delayBtn_pressed()
{
    show_pause_menu();
}

void MainWindow::delay_released()
{
    QString text = ui->action_delayTB->text();
    text += QString::number(ui->spinBox_delayTB->value());

    textEdit->insertPlainText(text);
}

void MainWindow::show_pause_menu()
{
    ui->widget_delayTB->setVisible(!ui->widget_delayTB->isVisible());
}

void MainWindow::on_backBtn_clicked()
{
    QString text = ui->action_backTB->text();
    textEdit->insertPlainText(text);
}

void MainWindow::on_animationBtn_clicked()
{
    QString text = ui->action_animatedTB->text();
    textEdit->insertPlainText(text);
}

void MainWindow::on_crossBtn_clicked()
{
    QString text = ui->action_crossTB->text();
    textEdit->insertPlainText(text);
}

void MainWindow::on_colorBtn_pressed()
{
    show_color_dialog();
}

void MainWindow::on_colorBtn_released()
{
    QString text = ui->action_colorTB->text();
    textColorName = colorPkr.name();
    text += textColorName;
    text.remove(2,1);
    textEdit->insertPlainText(text);
}

void MainWindow::show_color_dialog()
{
    colorPkr = QColorDialog::getColor();

    if(colorPkr.isValid())
        on_colorBtn_released();
}

void MainWindow::on_colorBtn_clicked()
{  //!!!!!!!!!!!!!!!!
    if(mTimerClr->isActive()) {
            mTimerClr->stop();

            QString text = ui->action_colorTB->text();
            textColorName = colorPkr.name();
            text += textColorName;
            text.remove(2,1);
            textEdit->insertPlainText(text);
        }
//    QString text = ui->action_colorTB->text();
//    text += textColorName;
//    text.remove(2,1);
//    textEdit->insertPlainText(text);
}

void MainWindow::on_clearBtn_clicked()
{
    QString text = ui->action_clearTB->text();
    textEdit->insertPlainText(text);
}
void MainWindow::onTextChanged()
{
    //qDebug() << "onTextChanged";
    QString str = textEdit->toPlainText();
    int status = mParser.ParsingLine(mUnitList, str);
    textEdit->textColorSet(status);
    if(mpQmlWidget->isVisible() && textEdit->toPlainText().length() != 0)
        //mpQmlWidget->drawWrapText(textEdit->toPlainText().at(textEdit->toPlainText().length() - 1));
    {
        if(status != -1)
        {
            ui->action_Play->setEnabled(false);
            a_play->setEnabled(false);
            ui->action_Stop->setEnabled(false);
            a_stop->setEnabled(false);
            ui->statusBar->showMessage("Misstake in input data, you cannot play on board", 5000);
        }
        else
        {
            ui->action_Play->setEnabled(true);
            a_play->setEnabled(true);
            ui->action_Stop->setEnabled(true);
            a_stop->setEnabled(true);
        }
    }
    else
    {
        if(status != -1)
        {
            ui->action_Show->setEnabled(false);
            a_show->setEnabled(false);
            ui->statusBar->showMessage("Misstake in input data, you cannot create board", 5000);
        }
        else
        {
            ui->action_Show->setEnabled(true);
            a_show->setEnabled(true);
        }
    }
    /*
    // DrawData temp = mpQmlWidget.getDrawData();
     /*if(!textEdit->toPlainText().isEmpty())
         this->inputText += textEdit->toPlainText().at(textEdit->toPlainText().size() - 1);
     mpQmlWidget.setDrawText(inputText);*/
     /*mpQmlWidget->setDrawText(textEdit->toPlainText());
     emit mpQmlWidget->drawTextChanged();*/
    //mpQmlWidget.Encode(mpQmlWidget.grabFramebuffer());
    /*mpGLWidget->textArray.clear();
    mpGLWidget->textArray.append(str);
    mpGLWidget->updateGL();
   if (mpGLWidget->mIsAnimatedStart){
      mpGLWidget->pauseAnimated();
   }*/
}

void MainWindow::on_action_Play_triggered()
{
    hideBoardSettings();
    ui->action_Play->setEnabled(false);
    a_play->setEnabled(false);
    ui->action_Pause->setEnabled(true);
    a_pause->setEnabled(true);
    ui->action_Undo->setEnabled(false);
    ui->action_Redo->setEnabled(false);
    a_undo->setEnabled(false);
    a_redo->setEnabled(false);
    if(mpQmlWidget->getStatus() == QmlWidget::PAUSE)
        ui->action_Play->setText("Play");
    else
    {
        mpQmlWidget->clearCanvas();
        mpQmlWidget->setFillColor(mpQmlWidget->getMainFillColor());
        drawCounter = 0;
    }
    mpQmlWidget->drawAnimated(ui->actionRecord_to_file->isChecked());
    textEdit->setEnabled(false);

    onTextChanged();
  //  qDebug() << mUnitList.size();
   // QString name = this->windowTitle();
    while( drawCounter < mUnitList.size() && mpQmlWidget != 0 && mpQmlWidget->getStatus() != QmlWidget::STOP)
    {
        //while(mpQmlWidget->getStatus() == QmlWidget::PAUSE)
        if( mpQmlWidget->getStatus() != QmlWidget::PAUSE )
        {
            mUnitList.at(drawCounter++)->draw(mpQmlWidget);
            int temp = (int)((float)((float)drawCounter/mUnitList.size()*100));
            ui->statusBar->showMessage("Progress status:    " + QString::number(temp) + "%");
        }
        else
            qApp->processEvents();
    }
 //   setWindowTitle(name);
    if(mpQmlWidget != NULL)
        mpQmlWidget->drawWrapText(" ");
    on_action_Stop_triggered();
}

void MainWindow::on_action_Stop_triggered()
{
    mpQmlWidget->stopAnimated();
    textEdit->setEnabled(true);
    ui->action_Undo->setEnabled(true);
    ui->action_Redo->setEnabled(true);
    a_undo->setEnabled(true);
    a_redo->setEnabled(true);

    if(mpQmlWidget->isVisible())
    {
        ui->action_Play->setText("Play");
        ui->action_Play->setEnabled(true);
        ui->action_Pause->setEnabled(false);
        a_pause->setEnabled(false);
        a_play->setEnabled(true);
        showBoardSettings();
    }



}

void MainWindow::on_action_youTube_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Videos (*.avi *.mp4)"));
    if(fileName.size() != 0)
    {
        youtube= new YouTubeWrapper(QString(fileName),this);
        youtube->getAuth()->startLogin(true);
    }

}
void MainWindow::on_action_Pause_triggered()
{
    ui->action_Play->setText("Resume");
    mpQmlWidget->pauseAnimated();
    //mpGLWidget->pauseAnimated();
    ui->action_Play->setEnabled(true);
    a_play->setEnabled(true);
    ui->action_Undo->setEnabled(true);
    ui->action_Redo->setEnabled(true);
    a_undo->setEnabled(true);
    a_redo->setEnabled(true);
}



void MainWindow::a_record_to_file_triggered()
{
    ui->actionRecord_to_file->setChecked(!(ui->actionRecord_to_file->isChecked()));
}

void MainWindow::on_actionRecord_to_file_triggered()
{
   // ui->actionRecord_to_file->setChecked((ui->actionRecord_to_file->isChecked()));
    a_record_to_file->setChecked(!(a_record_to_file->isChecked()));
}

void MainWindow::on_action_About_triggered()
{
    messAbout.setText("This is program for making video-lessons.\nITA, 2015");
    messAbout.show();
}
void MainWindow::on_speedBtn_pressed()
{
    ui->widget_speedTB->setVisible(!ui->widget_speedTB->isVisible());
}

void MainWindow::on_slider_speedTB_valueChanged(int value)
{
    lastInpuDelay = value;
    if(mpQmlWidget != NULL)
        mpQmlWidget->setDelay(1000/value);
}

void MainWindow::hideBoardSettings()
{
    if (ui->action_Board_Color->isEnabled()==true)
     ui->action_Board_Color->setEnabled(false);
    if (ui->action_Board_Font->isEnabled()==true)
       ui->action_Board_Font->setEnabled(false);
    a_color_canvas->setEnabled(false);
    a_font_canvas->setEnabled(false);
    setEnabledToolBar(false);
}

void MainWindow::showBoardSettings()
{
    if (ui->action_Board_Color->isEnabled()==false)
     ui->action_Board_Color->setEnabled(true);
    if (ui->action_Board_Font->isEnabled()==false)
       ui->action_Board_Font->setEnabled(true);
    a_color_canvas->setEnabled(true);
    a_font_canvas->setEnabled(true);

    setEnabledToolBar(true);
}

void MainWindow::setEnabledToolBar(bool status)
{
    ui->speedBtn->setEnabled(status);
    ui->crossBtn->setEnabled(status);
    ui->clearBtn->setEnabled(status);
    ui->backBtn->setEnabled(status);
    ui->delayBtn->setEnabled(status);
    ui->colorBtn->setEnabled(status);
    ui->animationBtn->setEnabled(status);

}

