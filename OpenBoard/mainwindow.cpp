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
    bHide = false;
//    connect(&drawThread, SIGNAL(started()), this, SLOT(myfunction())); //cant have parameter sorry, when using connect

    mpQmlWidget = new QmlWidget();
    textEdit = new MyTextEdit(QColor("#000000"), QColor("#FF0000"), ui->centralWidget);
    textEdit->setObjectName(QStringLiteral("textEdit"));
    textEdit->setEnabled(true);

    ui->verticalLayout->addWidget(textEdit,-1);
    mTimer = new QTimer(this);
    mTimerClr = new QTimer(this);
    mTimer->setSingleShot(true);
    mTimerClr->setSingleShot(true);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(show_pause_menu()));
    connect(mTimerClr, SIGNAL(timeout()), this, SLOT(show_color_dialog()));
    connect(ui->button_Find, SIGNAL(pressed()), this, SLOT(search()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
 //   connect(ui->actionSend_to_youTube, SIGNAL( triggered()), this, SLOT (on_action_youTube_triggered()));

    ui->widget_Find->setVisible(false);
    ui->widget_delayTB->setVisible(false);
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

      //  else
        {

            setWindowTitle(mSettings.getMainWindowTitle());
            setGeometry(mSettings.getMainWindowRect());
            this->textEdit->setTextColor(mSettings.getMainWindowColor());
this->textEdit->setFont(mSettings.getMainWindowFont());


        }
}

MainWindow::~MainWindow()
{
    mSettings.setMainWindowRect(geometry());

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent*)
{
    if(mpQmlWidget != 0 && bHide != true)
    {
        qDebug() << bHide;
        mpQmlWidget->close();
        on_action_Stop_triggered();
        delete mpQmlWidget;
    }
    // add if not empty
    /*
    delete textEdit;
    delete mTimer;
    delete mTimerClr;
    //delete mUnitList;
    delete youtube;
    */
    //delete mpGLWidget;
}

void MainWindow::on_action_Show_triggered()
{
    if (ui->action_Board_Color->isEnabled()==false)
   ui->action_Board_Color->setEnabled(true);
    if (ui->action_Board_Font->isEnabled()==false)
   ui->action_Board_Font->setEnabled(true);
/*
 * QML
*/
    mpQmlWidget = new QmlWidget();
    mpQmlWidget->show();
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
    bHide = false;

/*
    mpGLWidget->setFixedSize(GLWIDGET_SIZE);
    mpGLWidget->move(pos().x() + width(), pos().y());
    mpGLWidget->show();
*/

}

void MainWindow::on_action_Hide_triggered()
{
   // mpGLWidget->hide();
    if(mpQmlWidget->getStatus() == mpQmlWidget->PLAY || mpQmlWidget->getStatus() == mpQmlWidget->PAUSE)
    {
        mpQmlWidget->stopAnimated();
        on_action_Stop_triggered();
    }
    mpQmlWidget->close();
    bHide = true;
    delete mpQmlWidget;

    while (mpQmlWidget != 0)
    {
       // qDebug() << mpQmlWidget;
        qApp->processEvents();
    }
    ui->action_Pause->setEnabled(false);
    ui->action_Play->setEnabled(false);
    ui->action_Stop->setEnabled(false);
   ui->action_Board_Color->setEnabled(false);
   ui->action_Board_Font->setEnabled(false);

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
       // setFont(font);
}

void MainWindow::on_action_Color_triggered()
{   //call QtColorDialog
    QColor colorm;
    colorm = QColorDialog::getColor();
    //!!!!!!!!!!!
    QString col = colorm.name();
        textEdit->setTextColor(col);
        QString temp = textEdit->toPlainText();
        textEdit->clear();
        textEdit->insertPlainText(temp);

          mSettings.setMainWindowColor(colorm);
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
        ui->lineEdit_Find->selectAll();
    }
    else {
        textEdit->setFocus();
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
                    tr("Документ был изменен, сохранить изменения?"),
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
    mTimer->start(TIMER_VALUE);
}

void MainWindow::on_delayBtn_released()
{
    if(mTimer->isActive()) {
        mTimer->stop();

        QString text = ui->action_delayTB->text();
        text += QString::number(ui->spinBox_delayTB->value() / 10);
        text += QString::number(ui->spinBox_delayTB->value() % 10);

        textEdit->insertPlainText(text);
    }
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
    mTimerClr->start(TIMER_VALUE);
}

void MainWindow::on_colorBtn_released()
{
    if(mTimerClr->isActive()) {
        mTimerClr->stop();

        QString text = ui->action_colorTB->text();
        textColorName = colorPkr.name();
        text += textColorName;
        text.remove(2,1);
        textEdit->insertPlainText(text);
    }
}

void MainWindow::show_color_dialog()
{
    colorPkr = QColorDialog::getColor(Qt::black, this);

    if(colorPkr.isValid())
        textColorName = colorPkr.name();
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
    if(mpQmlWidget->isVisible() && textEdit->toPlainText().length() != 0)
        //mpQmlWidget->drawWrapText(textEdit->toPlainText().at(textEdit->toPlainText().length() - 1));
    {
        QString str = textEdit->toPlainText();
        int status = mParser.ParsingLine(mUnitList, str);
        textEdit->textColorSet(status);
        if(status != -1)
            ui->action_Play->setEnabled(false);
        else
            ui->action_Play->setEnabled(true);
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
    emit textEdit->textChanged();
    if(mpQmlWidget->getStatus() == QmlWidget::PAUSE)
        ui->action_Play->setText("Play");
    else
    {
        mpQmlWidget->clearCanvas();
        mpQmlWidget->setFillColor(mpQmlWidget->getMainFillColor());
    }
    mpQmlWidget->drawAnimated(ui->actionRecord_to_file->isChecked());
    textEdit->setEnabled(false);
// reinit
    int i = 0;
    qDebug() << mUnitList.size();
    while( i < mUnitList.size() && mpQmlWidget->getStatus() != QmlWidget::STOP)
    {
        while(mpQmlWidget->getStatus() == QmlWidget::PAUSE)
            qApp->processEvents();
        mUnitList.at(i++)->draw(mpQmlWidget);
    }
    mpQmlWidget->drawWrapText(" ");
    on_action_Stop_triggered();
}

void MainWindow::on_action_Stop_triggered()
{
    mpQmlWidget->stopAnimated();
    ui->action_Play->setText("Play");
    textEdit->setEnabled(true);
    // mpGLWidget->stopAnimated();
}

void MainWindow::on_action_youTube()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Videos (*.avi *.mp4)"));
    youtube= new YouTubeWrapper(QString(fileName),this);
    youtube->getAuth()->startLogin(true);
}
void MainWindow::on_action_Pause_triggered()
{
    ui->action_Play->setText("Resume");
    mpQmlWidget->pauseAnimated();
    //mpGLWidget->pauseAnimated();
}




