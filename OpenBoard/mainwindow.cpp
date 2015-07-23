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

    ui->delayBtn->setToolTip("Pause");
    ui->speedBtn->setToolTip("Speed");
    ui->backBtn->setToolTip("Paragraph");
    ui->animationBtn->setToolTip("Animated cross out");
    ui->crossBtn->setToolTip("Cross out");
    ui->colorBtn->setToolTip("Color");
    ui->clearBtn->setToolTip("Clean");


    //QStandardPaths path;
    directory = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(),
                                       QStandardPaths::LocateDirectory);
//qDebug() <<directory;
//    connect(&drawThread, SIGNAL(started()), this, SLOT(myfunction())); //cant have parameter sorry, when using connect

    mpOGLWidget = new OGLWidget();
    mpOGLWidget->setFixedSize(GLWIDGET_SIZE);
    mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
    mpOGLWidget->hide();
   // mpOGLWidget->moveToThread(&drawThread);
    textEdit = new MyTextEdit(QColor("#000000"), QColor("#FF0000"), ui->centralWidget);
    textEdit->setObjectName(QStringLiteral("textEdit"));
    textEdit->setEnabled(true);
    connect(textEdit,SIGNAL(setFocus()),this,SLOT(onCommandFocusLost()));


    commandTextEdit = new KeyloggerTE(textEdit, this);
    commandTextEdit->setObjectName(QStringLiteral("commandTextEdit"));
   // connect(commandTextEdit,SIGNAL(textChanged()),this,SLOT(key()));
    commandTextEdit->setEnabled(true);
    connect(commandTextEdit,SIGNAL(setFocus()),this,SLOT(onCommandFocusSet()));

    ui->verticalLayout->addWidget(textEdit,-1);
    ui->verticalLayout->addWidget(commandTextEdit,-1);
    connect(ui->button_Delay, SIGNAL(pressed()), this, SLOT(delay_released()));
    //connect(QColorDialog, SIGNAL(finished()), this, SLOT(on_colorBtn_released()));
    connect(ui->button_Find, SIGNAL(pressed()), this, SLOT(search()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    connect(ui->actionSend_to_youTube, SIGNAL( triggered()), this, SLOT (on_action_youTube_triggered()));
    connect(textEdit,SIGNAL(doUndoRedoStart()),this,SLOT(doUndoRedoStart()));
    connect(textEdit,SIGNAL(doUndoRedoEnd()),this,SLOT(doUndoRedoEnd()));

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
       a_undo->setToolTip(tr("Undo"));
       connect(a_undo,SIGNAL(triggered()),this,  SLOT(on_action_Undo_triggered()));
       toolBar->addAction(a_undo);
              //toolBar->addAction(QPixmap(":/icons/undo-icon.png").scaled(QSize(16, 16)), "Undo", this, SLOT(on_action_Undo_triggered()));
       a_redo = new QAction(this);
       a_redo->setEnabled(true);
       a_redo->setIcon(QPixmap(":/icons/redo-icon.png").scaled(QSize(16, 16)));
       a_redo->setToolTip(tr("Redo"));
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
       a_font_canvas->setToolTip(tr("Font canvas"));
       connect(a_font_canvas,SIGNAL(triggered()),this,  SLOT(on_action_Board_Font_triggered()));
       toolBar->addAction(a_font_canvas);

       a_color_canvas = new QAction(this);
       a_color_canvas->setEnabled(false);
       a_color_canvas->setIcon(QPixmap(":/icons/colors-icon.png").scaled(QSize(16, 16)));
       a_color_canvas->setToolTip(tr("Font canvas"));
       connect(a_color_canvas,SIGNAL(triggered()),this,  SLOT(on_action_Board_Color_triggered()));
       toolBar->addAction(a_color_canvas);

       toolBar->addAction(QPixmap(":/icons/default_programs.png").scaled(QSize(16, 16)), "Reset default", this, SLOT(on_action_Reset_default_triggered()));
       toolBar->addSeparator();

       a_show = new QAction(this);
       a_show->setEnabled(true);
       a_show->setIcon(QPixmap(":/icons/gnome_show_desktop.png").scaled(QSize(16, 16)));
       a_show->setToolTip(tr("Show canvas"));
       connect(a_show,SIGNAL(triggered()),this,  SLOT(on_action_Show_triggered()));
       toolBar->addAction(a_show);
      // toolBar->addAction(QPixmap(":/icons/gnome_show_desktop.png").scaled(QSize(16, 16)), "Show canvas", this, SLOT(on_action_Show_triggered()));


       a_hide = new QAction(this);
       a_hide->setEnabled(false);
       a_hide->setIcon(QPixmap(":/icons/hide_icon.png").scaled(QSize(16, 16)));
       a_hide->setToolTip(tr("Hide canvas"));
       connect(a_hide,SIGNAL(triggered()),this,  SLOT(on_action_Hide_triggered()));
       toolBar->addAction(a_hide);
      // toolBar->addAction(QPixmap(":/icons/hide_icon.png").scaled(QSize(16, 16)), "Hide canvas", this, SLOT(on_action_Hide_triggered()));

       a_play = new QAction(this);
       a_play->setEnabled(false);
       a_play->setIcon(QPixmap(":/icons/play-8-icon.png").scaled(QSize(16, 16)));
       a_play->setToolTip(tr("Play"));
       connect(a_play,SIGNAL(triggered()),this,  SLOT(on_action_Play_triggered()));
       toolBar->addAction(a_play);

       a_pause = new QAction(this);
       a_pause->setEnabled(false);
       a_pause->setIcon(QPixmap(":/icons/pause-icon.png").scaled(QSize(16, 16)));
       a_pause->setToolTip(tr("Pause"));
       connect(a_pause,SIGNAL(triggered()),this,  SLOT(on_action_Pause_triggered()));
       toolBar->addAction(a_pause);

       a_stop = new QAction(this);
       a_stop->setEnabled(false);
       a_stop->setIcon(QPixmap(":/icons/stop_icon.png").scaled(QSize(16, 16)));
       a_stop->setToolTip(tr("Stop"));
       connect(a_stop,SIGNAL(triggered()),this,  SLOT(on_action_Stop_triggered()));
       toolBar->addAction(a_stop);

       a_record_to_file = new QAction(this);
       a_record_to_file->setEnabled(false);
       a_record_to_file->setIcon(QPixmap(":/icons/12video icon.png").scaled(QSize(16, 16)));
       a_record_to_file->setToolTip(tr("Record in file"));
       a_record_to_file->setCheckable(true);
       a_record_to_file->setChecked(false);
       connect(a_record_to_file,SIGNAL(triggered()),this,  SLOT(a_record_to_file_triggered()));
       toolBar->addAction(a_record_to_file);

       toolBar->addAction(QPixmap(":/icons/youtube_icon.png").scaled(QSize(16, 16)), "Send to YouTube", this, SLOT(on_action_youTube_triggered()));
       toolBar->addAction(QPixmap(":/icons/info.png").scaled(QSize(16, 16)), "About", this, SLOT(on_action_About_triggered()));
       toolBar->setMovable(false);

       addToolBar(Qt::TopToolBarArea, toolBar);

       /*drawElements.append(new DrawTextElm(mpOGLWidget));
       ((DrawTextElm*)drawElements[0])->setLifeTime(6000);
       ((DrawTextElm*)drawElements[0])->setRect(180,180,200,200);*/

/*
 //load new style
        QFile file(":/style.txt");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
        file.close();
        */

}

MainWindow::~MainWindow()
{
    mSettings.setMainWindowRect(geometry());
    //drawThread.quit();
    if(toolBar != NULL)
        delete toolBar;
    delete ui;
    delete mpOGLWidget;
}

void MainWindow::closeEvent(QCloseEvent*)
{
    if(mpOGLWidget != NULL)
    {
        on_action_Hide_triggered();
    }
    qDebug() << "Close drawWidget";
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
    /*if(mpOGLWidget != NULL)
    {
        mpOGLWidget->close();
        delete mpOGLWidget;
        mpOGLWidget = NULL;
    }*/
    //mpOGLWidget = new OGLWidget();

    mpOGLWidget->show();
    mpOGLWidget->pause(100);// wait for show window
    mpOGLWidget->setDelay(1000/lastInpuDelay);
    mpOGLWidget->setFixedSize(GLWIDGET_SIZE);
    mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());

    timeLine.show();
    ui->action_Pause->setEnabled(true);
    ui->action_Play->setEnabled(true);
    ui->action_Stop->setEnabled(true);
    //mpOGLWidget.create();
    mpOGLWidget->setDrawText(textEdit->toPlainText());
    /*
     * init
     */

    mpOGLWidget->setTextFont(mSettings.getBoardFont());
    mpOGLWidget->setMainFillColor(mSettings.getBoardFontColor());
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
   // if(mpOGLWidget->getStatus() == mpOGLWidget->PLAY || mpOGLWidget->getStatus() == mpOGLWidget->PAUSE)
      //  mpOGLWidget->stopAnimated();
    on_action_Stop_triggered();
    mpOGLWidget->hide();
  //  mpOGLWidget->close();*/
    // delete mpOGLWidget;
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
    if(mpOGLWidget != NULL)
        mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(mpOGLWidget != NULL)
        mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
}

void MainWindow::on_action_Font_triggered()
{   //call QtFontDialog & setFont to all elements (this)
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, textEdit->font(), this);
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
    mpOGLWidget.setFont(qmlFont);   */
}

//!!!!!!!!!!!!!!!!!!
//!
void MainWindow::on_action_Board_Font_triggered()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, mpOGLWidget->getTextFont(), this);
    if (!ok)
        return;

 /*   QString qmlFont;
    QFontInfo fontInf(font);
    qmlFont = QString::number(fontInf.pointSize()) + "pt \"" + font.family() + "\"";*/
    mpOGLWidget->setTextFont(font);
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
    colorm = QColorDialog::getColor(textEdit->getColOrigin());
    //!!!!!!!!!!!
    if(colorm.isValid())
    {
        QString col = colorm.name();
        textEdit->setTextColor(col);
        textEdit->setColOrigin(colorm);
        QString temp = textEdit->toPlainText();
        textEdit->clear();
        textEdit->insertPlainText(temp);

        mSettings.setMainWindowColor(colorm);
    }
      /*a_show->setEnabled(false);
      ui->action_Show->setEnabled(false);*/
}

//!!!!!!!!!!!!!
//!
 void MainWindow::on_action_Board_Color_triggered()
{
    QColor colorm;
    colorm = QColorDialog::getColor(mpOGLWidget->getMainFillColor());

   // QString col = colorm.name();
    if(colorm.isValid())
    {
        mpOGLWidget->setMainFillColor(colorm);
        mSettings.setBoardFontColor(colorm);
    }



}

void MainWindow::on_action_Undo_triggered()
{
    textEdit->undom();
   // commandTextEdit->undo();
    //qDebug() <<"UNDO";
   // commandTextEdit->changesDetected=false;
}

void MainWindow::on_action_Redo_triggered()
{
    textEdit->rendom();
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
    if(curFile.isEmpty())
        return on_action_Save_as_triggered();
    QFile file(curFile);
    if(file.open(QIODevice::WriteOnly))
    {
        ui->statusBar->showMessage("files saving...");
        QString ss = textEdit->toPlainText();
        QTextStream outStream(&file);
        outStream << ss;
        file.close();
        ui->statusBar->showMessage("file saved");
        return true;
    }
    else
    {
        QMessageBox::warning(this, "Error",
                             tr("File\'s saving failed") //щ
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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), directory,
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
    /*if (curFile.isEmpty())
        return on_action_Save_as_triggered();
    else*/
        return saveFile();
}

void MainWindow::on_action_Open_triggered()
{
    if (maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), directory,
                                                              tr("Text Files (*.txt);;All Files (*.*)"));
    openFile( fileName);
    }
     textEdit->openText();
}

bool MainWindow::openFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QFile::ReadOnly))
        {
            curFile = fileName;
             textEdit->setText(QString::fromLocal8Bit((file.readAll())));
            return true;
        }
        else
        {
            QMessageBox::warning(this, "Error",tr("File opening failed")); //щ
             return false;
        }
    }
}

void MainWindow::on_action_New_triggered()
{
    if (maybeSave())
    {
        curFile.clear();
        textEdit->clear();
    }
textEdit->newText();
}

void MainWindow::on_delayBtn_pressed()
{
    show_pause_menu();

    textEdit->setFocus();
}

void MainWindow::delay_released()
{
    QString text = ui->action_delayTB->text();
    text += QString::number(ui->spinBox_delayTB->value());
    emit textEdit->setFocus();
    if( isCommandTextEditFocused )
        textEdit->appendNoNL(text);
    else
        textEdit->insertPlainText(text);
}

void MainWindow::show_pause_menu()
{
    ui->widget_delayTB->setVisible(!ui->widget_delayTB->isVisible());
}

void MainWindow::on_backBtn_clicked()
{
    QString text = ui->action_backTB->text();
   // textEdit->insertPlainText(text);
   // textEdit->setFocus();
    if (isCommandTextEditFocused){
    commandTextEdit->insertPlainText("\n");
    textEdit->appendNoNL(text);
    }
    else{
     textEdit->insertPlainText(text);
    }
     commandTextEdit->previousCursorPosition=commandTextEdit->textCursor().position();
}
void MainWindow::onCommandFocusSet(){
    isCommandTextEditFocused=true;
    qDebug() << "focus changed"<<isCommandTextEditFocused;
}
void MainWindow::onCommandFocusLost(){
    isCommandTextEditFocused=false;
    qDebug() << "focus changed"<<isCommandTextEditFocused;
}

void MainWindow::on_animationBtn_clicked()
{
    QString textInField="";
    textEdit->toPlainText();
    QString text = ui->action_animatedTB->text();
   // textEdit->insertPlainText(text);
    if (isCommandTextEditFocused){
    //commandTextEdit->insertPlainText(text);
    textInField = textEdit->toPlainText();
    if (commandTextEdit->toPlainText().isEmpty())return;
    if (commandTextEdit->textCursor().selectionEnd()-commandTextEdit->textCursor().selectionStart()==0)
    {
            textInField +=text;
            textEdit->setPlainText(textInField);
    }
    else {
        int delta = commandTextEdit->textCursor().selectionEnd()-commandTextEdit->textCursor().selectionStart();
        if (commandTextEdit->textCursor().position()!=commandTextEdit->textCursor().selectionEnd())
        { textInField.chop(6);//Видаляємо перехід вліво КОСТИЛЯКА НА ЛОМАЦІ ))
            QTextCursor tCursor = commandTextEdit->textCursor();
            tCursor.clearSelection();
           commandTextEdit->setTextCursor(tCursor);
        }
        textInField +=QString("\\<%1").arg(delta, 3, 10, QChar('0'));
         textEdit->setPlainText(textInField);
    }
    }
    else
    textEdit->insertPlainText(text);

    commandTextEdit->saveChanges(text.length());

}

void MainWindow::on_crossBtn_clicked()
{
    QString textInField="";
    textEdit->toPlainText();
    QString text = "\\-001";
   // textEdit->insertPlainText(text);
    if (isCommandTextEditFocused){
    //commandTextEdit->insertPlainText(text);
    textInField = textEdit->toPlainText();
    if (commandTextEdit->toPlainText().isEmpty())return;
    if (commandTextEdit->textCursor().selectionEnd()-commandTextEdit->textCursor().selectionStart()==0)
    {
            textInField +=text;
            textEdit->setPlainText(textInField);
    }
    else {
        int delta = commandTextEdit->textCursor().selectionEnd()-commandTextEdit->textCursor().selectionStart();
        if (commandTextEdit->textCursor().position()!=commandTextEdit->textCursor().selectionEnd())
        { textInField.chop(6);//Видаляємо перехід вліво КОСТИЛЯКА НА ЛОМАЦІ ))
            QTextCursor tCursor = commandTextEdit->textCursor();
            tCursor.clearSelection();
           commandTextEdit->setTextCursor(tCursor);
        }
        textInField +=QString("\\-%1").arg(delta, 3, 10, QChar('0'));
         textEdit->setPlainText(textInField);
    }
    }
    else
    textEdit->insertPlainText(text);
      commandTextEdit->saveChanges(text.length());
}

void MainWindow::on_colorBtn_pressed()
{
    QTextCursor prev_cursor = textEdit->textCursor();
    colorPkr = QColorDialog::getColor(mpOGLWidget->getMainFillColor());
    textEdit->setTextCursor(prev_cursor);
    if(colorPkr.isValid())
    {
        QString text = ui->action_colorTB->text();
        textColorName = colorPkr.name();
        text += textColorName;
        text.remove(2,1);
        if( isCommandTextEditFocused )
            textEdit->appendNoNL(text);
        else
            textEdit->insertPlainText(text);
    }

 //   textEdit->setFocus();
}

void MainWindow::on_colorBtn_released()
{

}

void MainWindow::show_color_dialog()
{

}

void MainWindow::on_colorBtn_clicked()
{  //!!!!!!!!!!!!!!!!

//    QString text = ui->action_colorTB->text();
//    text += textColorName;
//    text.remove(2,1);
//    textEdit->insertPlainText(text);
  //  textEdit->setFocus();
}

void MainWindow::on_clearBtn_clicked()
{
    QString text = ui->action_clearTB->text();
    if( isCommandTextEditFocused )
        textEdit->appendNoNL(text);
    else
        textEdit->insertPlainText(text);
}

void MainWindow::doUndoRedoStart()
{
    disconnect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void MainWindow::doUndoRedoEnd()
{
    textEdit->textColorSet(-1);
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    textEdit->document()->setModified(true);
}

void MainWindow::onTextChanged()
{
    disconnect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    qDebug() << "onTextChanged";
    QString str = textEdit->toPlainText();
    /*
     * bida z cursorom
    */

    QTextCursor cursor = textEdit->textCursor();
    int cursPos = textEdit->textCursor().position();
    int textSize = str.size();
    int status = mParser.ParsingLine(mUnitList, str); // add parsing /n
   /* if(textSize != str.size())
    {
        textEdit->clear();
        textEdit->append(str);
        if(cursPos != textSize)
        {
            cursor.setPosition(cursPos + 1);
            textEdit->setTextCursor(cursor);
        }
    }
    */
    textEdit->textColorSet(status);
    if(textEdit->toPlainText().size() != 0)
        if(mpOGLWidget->isVisible())
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
    textEdit->saveChanges();
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    /*
    // DrawData temp = mpOGLWidget.getDrawData();
     /*if(!textEdit->toPlainText().isEmpty())
         this->inputText += textEdit->toPlainText().at(textEdit->toPlainText().size() - 1);
     mpOGLWidget.setDrawText(inputText);*/
     /*mpOGLWidget->setDrawText(textEdit->toPlainText());
     emit mpOGLWidget->drawTextChanged();*/
    //mpOGLWidget.Encode(mpOGLWidget.grabFramebuffer());
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
    if(mpOGLWidget->getStatus() == OGLWidget::PAUSE)
        ui->action_Play->setText("Play");
    else
    {
        mpOGLWidget->clearCanvas();
        mpOGLWidget->clearBuffer();
        mpOGLWidget->setFillColor(mpOGLWidget->getMainFillColor());
        drawCounter = 0;
    }
    mpOGLWidget->drawAnimated(ui->actionRecord_to_file->isChecked());
    textEdit->setEnabled(false);

    onTextChanged();
  /*  ((DrawTextElm*)drawElements[0])->setUnitList(mUnitList);
    ((DrawTextElm*)drawElements[0])->setUnParsestring(textEdit->toPlainText());
    QImage t(":/ThirdPart/images/brush.png");
    ((DrawTextElm*)drawElements[0])->setIcon(t);
    drawElements[0]->save("kaka");*/
 //   drawElements[0]->load("kaka");
   // mpOGLWidget->setList(drawElements);
  //  qDebug() << mUnitList.size();
   // QString name = this->windowTitle();
    /*play = true;
    while( play &&  drawCounter < mUnitList.size() && mpOGLWidget != 0 && mpOGLWidget->getStatus() != OGLWidget::STOP)
    {
        //while(mpOGLWidget->getStatus() == OGLWidget::PAUSE)
        if( mpOGLWidget->getStatus() != OGLWidget::PAUSE )
        {
            mUnitList.at(drawCounter++)->draw(mpOGLWidget);
            int temp = (int)((float)((float)drawCounter/mUnitList.size()*100));
            ui->statusBar->showMessage("Progress status:    " + QString::number(temp) + "%");
        }
        else
            qApp->processEvents();
    }
 //   setWindowTitle(name);
    if(mpOGLWidget != NULL)
    {
        mpOGLWidget->update();
        mpOGLWidget->drawBuffer();
    }
    on_action_Stop_triggered();
    play = false;
    */
}

void MainWindow::on_action_Stop_triggered()
{
    mpOGLWidget->stopAnimated();
    textEdit->setEnabled(true);
    ui->action_Undo->setEnabled(true);
    ui->action_Redo->setEnabled(true);
    a_undo->setEnabled(true);
    a_redo->setEnabled(true);

    if(mpOGLWidget->isVisible())
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
    mpOGLWidget->pauseAnimated();
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

    textEdit->setFocus();
}

void MainWindow::on_slider_speedTB_valueChanged(int value)
{
    lastInpuDelay = value;
    if(mpOGLWidget != NULL)
        mpOGLWidget->setDelay(1000/value);
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
