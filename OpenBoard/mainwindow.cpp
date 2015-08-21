#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../TimeLine/listcontroll.h"

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


    curProjectFile.clear();
//// //qDebug() <<directory;
//    connect(&drawThread, SIGNAL(started()), this, SLOT(myfunction())); //cant have parameter sorry, when using connect

    mpOGLWidget = new OGLWidget(this);
   // gs(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);
    //mpOGLWidget->setAttribute(Qt::WA_ShowModal);
    //mpOGLWidget->setWindowFlags (Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);
    mpOGLWidget->show();
    mpOGLWidget->setVisible(false);
     //qDebug() << "connect unableToDraw";
/*
     mpOGLWidget->getTimeLine()->show();
     mpOGLWidget->show();

    qApp->processEvents(QEventLoop::AllEvents, 1000);
*/
    mpOGLWidget->setFixedSize(GLWIDGET_SIZE);
    mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());

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
connect(mpOGLWidget,SIGNAL(keyPressSignal(QKeyEvent*)),this,SLOT(keyEventSlot(QKeyEvent*)));

    ui->widget_Find->setVisible(false);
    ui->widget_delayTB->setVisible(false);
    lastInpuDelay = ui->slider_speedTB->value();

   // ui->slider_speedTB->setAlignment(Qt::AlignVCenter);
    ui->spinBox_speedTB->setAlignment(Qt::AlignVCenter);
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
        mSettings.setMainWindowColor(QColor(255,255,255));
        QColor col (255,255,255);
        mSettings.setBoardFontColor(QColor(255,255,255));


        QFont sfont("Tahoma", 10);
        mSettings.setBoardFont(QFont("Tahoma",20,1,false));
        mSettings.saveSettings();
    }

       setWindowTitle(mSettings.getMainWindowTitle());
       setGeometry(mSettings.getMainWindowRect());
       this->textEdit->setColOrigin(mSettings.getMainWindowColor());
       //commandTextEdit->setStyleSheet("color: " + mSettings.getMainWindowColor().name());
       //commandTextEdit->setTextColor(mSettings.getMainWindowColor());
       this->textEdit->setFont(mSettings.getMainWindowFont());
       commandTextEdit->setFont(mSettings.getMainWindowFont());

       toolBar= new QToolBar(this);
       toolBarBoard= new QToolBar(this);
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

       a_clear_drawing = new QAction(this);
       a_clear_drawing->setEnabled(false);
       a_clear_drawing->setIcon(QPixmap(":/icons/Oxygen-Icons.org-Oxygen-Actions-edit-clear.ico").scaled(QSize(16, 16)));
       a_clear_drawing->setToolTip(tr("Clear drawing"));
       connect(a_clear_drawing,SIGNAL(triggered()),this,  SLOT(on_actionClear_drawing_triggered()));
       toolBarBoard->addAction(a_clear_drawing);

       a_clear_drawingBuffer = new QAction(this);
       a_clear_drawingBuffer->setEnabled(false);
       a_clear_drawingBuffer->setIcon(QPixmap(":/iphone_toolbar_icons/refresh.png").scaled(QSize(16, 16)));
       a_clear_drawingBuffer->setToolTip(tr("Clear drawing history"));
       connect(a_clear_drawingBuffer,SIGNAL(triggered()),this,  SLOT(on_actionClear_drawingBuffer_triggered()));
       toolBarBoard->addAction(a_clear_drawingBuffer);

       a_show_last_drawing = new QAction(this);
       a_show_last_drawing->setEnabled(false);
       a_show_last_drawing->setIcon(QPixmap(":/iphone_toolbar_icons/forwardtoend.png").scaled(QSize(16, 16)));
       a_show_last_drawing->setToolTip(tr("Show last drawing"));
       connect(a_show_last_drawing,SIGNAL(triggered()),this,  SLOT(on_actionShow_last_drawing_triggered()));
       toolBarBoard->addAction(a_show_last_drawing);

       a_save_drawing = new QAction(this);
       a_save_drawing->setEnabled(true);
       a_save_drawing->setIcon(QPixmap(":/icons/Save-icon.png").scaled(QSize(16, 16)));
       a_save_drawing->setToolTip(tr("Save last drawing"));
       connect(a_save_drawing,SIGNAL(triggered()),this,  SLOT(on_actionSave_drawing_triggered()));
       toolBarBoard->addAction(a_save_drawing);


       a_cut = new QAction(this);
        a_cut->setEnabled(true);
         a_cut->setIcon(QPixmap(":/icons/cut-icon.png").scaled(QSize(16, 16)));
         connect(a_cut,SIGNAL(triggered()), this, SLOT(on_action_Cut_triggered()));
          a_cut->setToolTip(tr("Cut"));

       a_copy = new QAction(this);
        a_copy->setEnabled(true);
        a_copy->setIcon(QPixmap(":/icons/Copy-icon.png").scaled(QSize(16, 16)));
        connect(a_copy,SIGNAL(triggered()), this, SLOT(on_action_Copy_triggered()));
         a_copy->setToolTip(tr("Copy"));

       a_paste = new QAction(this);
        a_paste->setEnabled(true);
         a_paste->setIcon(QPixmap(":/icons/Paste-icon.png").scaled(QSize(16, 16)));
         connect(a_paste,SIGNAL(triggered()), this, SLOT(on_action_Paste_triggered()));
          a_paste->setToolTip(tr("Paste"));

       a_select_all = new QAction(this);
        a_select_all->setEnabled(true);
          a_select_all->setIcon(QPixmap(":/icons/select_all.png").scaled(QSize(16, 16)));
          connect(a_select_all,SIGNAL(triggered()), this, SLOT(on_action_Select_all_triggered()));
           a_select_all->setToolTip(tr("Select all"));

       a_search = new QAction(this);
        a_search->setEnabled(true);
           a_search->setIcon(QPixmap(":/icons/search-icon.png").scaled(QSize(16, 16)));
           connect(a_search,SIGNAL(triggered()), this, SLOT(on_action_Find_triggered()));
            a_search->setToolTip(tr("Search"));


       toolBar->addAction(a_cut);
       toolBar->addAction(a_copy);
       toolBar->addAction(a_paste);
       toolBar->addAction(a_select_all);
       toolBar->addAction(a_search);


       a_clear_textedit = new QAction(this);
       a_clear_textedit->setEnabled(true);
       a_clear_textedit->setIcon(QPixmap(":/icons/222.png").scaled(QSize(16, 16)));
       a_clear_textedit->setToolTip(tr("Clear text areas"));
       connect(a_clear_textedit,SIGNAL(triggered()),this,  SLOT(on_action_Clear_TextEdit_triggered()));
       toolBar->addAction(a_clear_textedit);



       toolBar->addSeparator();

       toolBar->addAction(QPixmap(":/icons/font-x-generic-icon.png").scaled(QSize(16, 16)), "Font text area", this, SLOT(on_action_Font_triggered()));
       toolBar->addAction(QPixmap(":/icons/colors-icon.png").scaled(QSize(16, 16)), "Color text area", this, SLOT(on_action_Color_triggered()));

       a_font_canvas = new QAction(this);
       a_font_canvas->setEnabled(false);
       a_font_canvas->setIcon(QPixmap(":/icons/font-x-generic-icon.png").scaled(QSize(16, 16)));
       a_font_canvas->setToolTip(tr("Font canvas"));
       connect(a_font_canvas,SIGNAL(triggered()),this,  SLOT(on_action_Board_Font_triggered()));
       toolBarBoard->addAction(a_font_canvas);

       a_color_canvas = new QAction(this);
       a_color_canvas->setEnabled(false);
       a_color_canvas->setIcon(QPixmap(":/icons/colors-icon.png").scaled(QSize(16, 16)));
       a_color_canvas->setToolTip(tr("Color canvas"));
       connect(a_color_canvas,SIGNAL(triggered()),this,  SLOT(on_action_Board_Color_triggered()));
       toolBarBoard->addAction(a_color_canvas);

       toolBar->addAction(QPixmap(":/icons/default_programs.png").scaled(QSize(16, 16)), "Reset default", this, SLOT(on_action_Reset_default_triggered()));
       toolBar->addSeparator();


       a_new_project = new QAction(this);
       a_new_project->setEnabled(true);
       a_new_project->setIcon(QPixmap(":/iphone_toolbar_icons/New Folder.png").scaled(QSize(16, 16)));
       a_new_project->setToolTip(tr("New project"));
       a_new_project->setIconText(tr("New project"));
       a_new_project->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_N));
        connect(a_new_project,SIGNAL(triggered()),mpOGLWidget->getTimeLine(),  SLOT(emitNewProject()));


       a_open_project = new QAction(this);
       a_open_project->setEnabled(true);
       a_open_project->setIcon(QPixmap(":/iphone_toolbar_icons/Open_.png").scaled(QSize(16, 16)));
       a_open_project->setToolTip(tr("Open project"));
       a_open_project->setIconText(tr("Open project"));
       a_open_project->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));
       connect(a_open_project,SIGNAL(triggered()),mpOGLWidget->getTimeLine(),  SLOT(emitOpenProject()));

       a_save_project = new QAction(this);
       a_save_project->setEnabled(true);
       a_save_project->setIcon(QPixmap(":/iphone_toolbar_icons/save.png").scaled(QSize(16, 16)));
       a_save_project->setToolTip("Save project");
       a_save_project->setIconText("Save project");
       a_save_project->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
       connect(a_save_project,SIGNAL(triggered()),mpOGLWidget->getTimeLine(),  SLOT(emitSaveProject()));

       a_exit = new QAction(this);
       a_exit->setEnabled(true);
       a_exit->setIcon(QPixmap(":/icons/Close-2-icon.png").scaled(QSize(16, 16)));
       a_exit->setToolTip("Exit");
       a_exit->setIconText("Exit");
       connect(a_exit,SIGNAL(triggered()),this,  SLOT(on_action_Exit_triggered()));



       QList <QAction *> list_act;
             list_act.append(a_new_project);
             list_act.append(a_open_project);
             list_act.append(a_save_project);

             this->ui->menu_File->addActions(list_act); //1234
             list_act.clear();
              list_act.append(a_exit);
               this->ui->menu_File->addSeparator();
               this->ui->menu_File->addActions(list_act); //1234

       a_show = new QAction(this);
       a_show->setEnabled(true);
       a_show->setIcon(QPixmap(":/icons/gnome_show_desktop.png").scaled(QSize(16, 16)));
       a_show->setToolTip(tr("Show canvas"));
       connect(a_show,SIGNAL(triggered()),this,  SLOT(on_action_Show_triggered()));
       toolBarBoard->addAction(a_show);
      // toolBar->addAction(QPixmap(":/icons/gnome_show_desktop.png").scaled(QSize(16, 16)), "Show canvas", this, SLOT(on_action_Show_triggered()));


       a_hide = new QAction(this);
       a_hide->setEnabled(false);
       a_hide->setIcon(QPixmap(":/icons/hide_icon.png").scaled(QSize(16, 16)));
       a_hide->setToolTip(tr("Hide canvas"));
       connect(a_hide,SIGNAL(triggered()),this,  SLOT(on_action_Hide_triggered()));
       toolBarBoard->addAction(a_hide);
      // toolBar->addAction(QPixmap(":/icons/hide_icon.png").scaled(QSize(16, 16)), "Hide canvas", this, SLOT(on_action_Hide_triggered()));

       a_play = new QAction(this);
       a_play->setEnabled(false);
       a_play->setIcon(QPixmap(":/icons/play-8-icon.png").scaled(QSize(16, 16)));
       a_play->setToolTip(tr("Play"));
       connect(a_play,SIGNAL(triggered()),mpOGLWidget->getTimeLine(), SIGNAL(playSignal()));
       toolBarBoard->addAction(a_play);






       a_pause = new QAction(this);
       a_pause->setEnabled(false);
       a_pause->setIcon(QPixmap(":/icons/pause-icon.png").scaled(QSize(16, 16)));
       a_pause->setToolTip(tr("Pause"));
       connect(a_pause,SIGNAL(triggered()),mpOGLWidget->getTimeLine(), SIGNAL(pauseSignal()));
       toolBarBoard->addAction(a_pause);

       a_stop = new QAction(this);
       a_stop->setEnabled(false);
       this->ui->action_Stop->setEnabled(false);
       a_stop->setIcon(QPixmap(":/icons/stop_icon.png").scaled(QSize(16, 16)));
       a_stop->setToolTip(tr("Stop"));
       connect(a_stop,SIGNAL(triggered()),mpOGLWidget->getTimeLine(), SIGNAL(stopSignal()));
       toolBarBoard->addAction(a_stop);

       a_record_to_file = new QAction(this);
       a_record_to_file->setEnabled(false);
       a_record_to_file->setIcon(QPixmap(":/icons/12video icon.png").scaled(QSize(16, 16)));
       a_record_to_file->setToolTip(tr("Record in file"));
       a_record_to_file->setCheckable(true);
       a_record_to_file->setChecked(false);
       connect(a_record_to_file,SIGNAL(triggered()),this,  SLOT(on_action_Record_to_file_triggered()));
       toolBarBoard->addAction(a_record_to_file);

        connect(ui->actionRecord_to_file,SIGNAL(triggered()),this,  SLOT(on_action_Record_to_file_triggered()));
ui->actionRecord_to_file->setCheckable(true);

a_send_to_youtube = new QAction(this);
 a_send_to_youtube->setEnabled(true);
 a_send_to_youtube->setIcon(QPixmap(":/icons/youtube_icon.png").scaled(QSize(16, 16)));
 a_send_to_youtube->setToolTip(tr("Send to YouTube"));
 connect(a_send_to_youtube,SIGNAL(triggered()),this,  SLOT(on_action_youTube_triggered()));
 toolBar->addAction(a_send_to_youtube);


       toolBar->addAction(QPixmap(":/icons/info.png").scaled(QSize(16, 16)), "About", this, SLOT(on_action_About_triggered()));
       toolBar->setMovable(false);
       toolBarBoard->setMovable(false);



       QObjectList chield = toolBar->children();
       for( QObject* i: chield)
           i->setObjectName("item");
       toolBar->setIconSize(QSize(20,20));

       chield = toolBarBoard->children();
       for( QObject* i: chield)
           i->setObjectName("item");
       toolBarBoard->setIconSize(QSize(20,20));
       toolBarBoard->setContentsMargins(0,0,0,0);
       addToolBar(Qt::TopToolBarArea, toolBar);
       addToolBarBreak();
       addToolBar(Qt::RightToolBarArea, toolBarBoard);

      /* drawElements.append(new DrawTextElm(mpOGLWidget));
       ((DrawTextElm*)drawElements[0])->setLifeTime(6000);
       ((DrawTextElm*)drawElements[0])->setRect(180,180,200,200);*/


        connect(mpOGLWidget->getTimeLine(), SIGNAL(stopSignal()), this, SLOT(on_action_Stop_triggered()));
        connect(mpOGLWidget->getTimeLine(), SIGNAL(playSignal()), this, SLOT(on_action_Play_triggered()));
        connect(mpOGLWidget->getTimeLine(), SIGNAL(pauseSignal()), this, SLOT(on_action_Pause_triggered()));
        connect(this, SIGNAL(signalCurentStateChanged()), this, SLOT(slotCurentStateChanged()));

        connect(mpOGLWidget->getTimeLine(), SIGNAL(newProjectSignel()), this, SLOT(on_action_New_Project_triggered()));
        connect(mpOGLWidget->getTimeLine(), SIGNAL(openProjectSignel()), this, SLOT(on_action_Open_Project_triggered()));
        connect(mpOGLWidget->getTimeLine(), SIGNAL(saveProjectSignel()), this, SLOT(on_action_Save_Project_triggered()));

        connect(mpOGLWidget->getTimeLine(),SIGNAL(loadFromFileSignal()),this,SLOT(updateBlockFromTextEdit()));
        connect(mpOGLWidget->getTimeLine(), SIGNAL(updateSelectedBlock(QPoint)), this, SLOT(updateTextEditFromBlock(QPoint)));
    //    connect(commandTextEdit, SIGNAL(widgetVisibilityChanged(bool)), this, SLOT(updateVisibleTextEdit(bool)));

        connect(mpOGLWidget,SIGNAL(stopShowLastDrawingSignal()),this,SLOT(onStopShowLastDrawing()));


        setEnabledToolBar(false);

        onTextChangeUpdateTimer.setInterval(800);
        onTextChangeUpdateTimer.setSingleShot(true);
        connect(&onTextChangeUpdateTimer,SIGNAL(timeout()),this,SLOT(updateBlockFromTextEdit()));


       //load new style
        QFile file(":/style.txt");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();

        updateEditWidgets(true); //instal normal color

        on_action_New_Project_triggered();


}

MainWindow::~MainWindow()
{
    mSettings.setMainWindowRect(geometry());
    mpOGLWidget->getTimeLine()->close();
    //drawThread.quit();
    if(toolBar != NULL)
        delete toolBar;
    delete ui;
    delete mpOGLWidget;
}

void MainWindow::setViewState(VIEW_STATE state)
{
    /*
     VIDEO_EDIT_TEXT,
    VIDEO_EDIT_PRO,
    VIDEO_EDIT_DEFAULT,
    BRUSH_ANIMATION,
    VISUAL_EFFECT
*/
    ////qDebug() << "Hdfjkhdfdhdjfh" << state;
switch (state){

case VIDEO_EDIT_TEXT:
{
    on_action_Show_triggered();
    mpOGLWidget->getTimeLine()->hide();
    toolBar->show();
    toolBarBoard->show();
    a_clear_drawing->setVisible(false);
    a_clear_drawingBuffer->setVisible(false);
    a_clear_textedit->setVisible(true);
    a_color_canvas->setVisible(true);
    a_exit->setVisible(true);
    a_font_canvas->setVisible(true);
    a_hide->setVisible(false);
    a_new_project->setVisible(true);
    a_open_project->setVisible(true);
    a_pause->setVisible(true);
    a_play->setVisible(true);
    a_record_to_file->setVisible(true);
    a_redo->setVisible(true);
    a_save_drawing->setVisible(false);
    a_save_project->setVisible(true);
    a_show->setVisible(false);
    a_show_last_drawing->setVisible(false);
    a_stop->setVisible(true);
    a_undo->setVisible(true);


    break;
}
case VIDEO_EDIT_PRO:
{
   // mpOGLWidget->getTimeLine()->show();
    toolBar->show();
    toolBarBoard->show();
    a_clear_drawing->setVisible(true);
    a_clear_drawingBuffer->setVisible(true);
    a_clear_textedit->setVisible(true);
    a_color_canvas->setVisible(true);
    a_exit->setVisible(true);
    a_font_canvas->setVisible(true);
    a_hide->setVisible(true);
    a_new_project->setVisible(true);
    a_open_project->setVisible(true);
    a_pause->setVisible(true);
    a_play->setVisible(true);
    a_record_to_file->setVisible(true);
    a_redo->setVisible(true);
    a_save_drawing->setVisible(true);
    a_save_project->setVisible(true);
    a_show->setVisible(true);
    a_show_last_drawing->setVisible(true);
    a_stop->setVisible(true);
    a_undo->setVisible(true);
    if(mpOGLWidget->isVisible())
        mpOGLWidget->getTimeLine()->show();
    //qDebug() << "PRO";
    //mpOGLWidget->getTimeLine()->hide();
    break;
}
/*case VIDEO_EDIT_DEFAULT:
    toolBar->show();
    toolBarBoard->show();
    a_clear_drawing->setVisible(true);
    a_clear_drawingBuffer->setVisible(true);
    a_clear_textedit->setVisible(true);
    a_color_canvas->setVisible(true);
    a_exit->setVisible(true);
    a_font_canvas->setVisible(true);
    a_hide->setVisible(false);
    a_new_project->setVisible(true);
    a_open_project->setVisible(true);
    a_pause->setVisible(true);
    a_play->setVisible(true);
    a_record_to_file->setVisible(true);
    a_redo->setVisible(true);
    a_save_drawing->setVisible(true);
    a_save_project->setVisible(true);
    a_show->setVisible(false);
    a_show_last_drawing->setVisible(true);
    a_stop->setVisible(true);
    a_undo->setVisible(true);
    break;*/
case BRUSH_ANIMATION:
{
    toolBar->hide();
    toolBarBoard->show();
    on_action_Show_triggered();
    mpOGLWidget->getTimeLine()->hide();
    a_clear_drawing->setVisible(true);
    a_clear_drawingBuffer->setVisible(true);
    a_clear_textedit->setVisible(true);
    a_color_canvas->setVisible(true);
    a_exit->setVisible(true);
    a_font_canvas->setVisible(true);
    a_hide->setVisible(false);
    a_new_project->setVisible(true);
    a_open_project->setVisible(true);
    a_pause->setVisible(false);
    a_play->setVisible(false);
    a_record_to_file->setVisible(false);
    a_redo->setVisible(false);
    a_save_drawing->setVisible(true);
    a_save_project->setVisible(true);
    a_show->setVisible(false);
    a_show_last_drawing->setVisible(true);
    a_stop->setVisible(false);
    a_undo->setVisible(false);
    break;
}
case VISUAL_EFFECT:
{
    toolBar->show();
    toolBarBoard->show();
    a_clear_drawing->setVisible(true);
    a_clear_drawingBuffer->setVisible(true);
    a_clear_textedit->setVisible(true);
    a_color_canvas->setVisible(true);
    a_exit->setVisible(true);
    a_font_canvas->setVisible(true);
    a_hide->setVisible(true);
    a_new_project->setVisible(true);
    a_open_project->setVisible(true);
    a_pause->setVisible(true);
    a_play->setVisible(true);
    a_record_to_file->setVisible(true);
    a_redo->setVisible(true);
    a_save_drawing->setVisible(true);
    a_save_project->setVisible(true);
    a_show->setVisible(true);
    a_show_last_drawing->setVisible(true);
    a_stop->setVisible(true);
    a_undo->setVisible(true);
    break;
}
case OPENING_PROJECT:
    on_action_Open_Project_triggered();
    break;
}

    if(!isVisible())
        show();
    activateWindow();
}

void MainWindow::closeEvent(QCloseEvent*)
{
    if(mpOGLWidget != NULL && mpOGLWidget->isVisible())
    {
        on_action_Hide_triggered();
        mpOGLWidget->close();
    }
    // //qDebug() << "Close drawWidget";
}

void MainWindow::updateEditWidgets( bool forceEnabled )
{
    if(textEdit != NULL && commandTextEdit != NULL)
    {
        textEdit->textColorSet(-1);
        if(textEdit->isEnabled() || forceEnabled)
        {
            this->textEdit->setColOrigin(mSettings.getMainWindowColor());
            commandTextEdit->setStyleSheet("color: " + mSettings.getMainWindowColor().name());
            textEdit->setStyleSheet("color: " + mSettings.getMainWindowColor().name());
        }
        else
        {
            commandTextEdit->setStyleSheet("color: black");
            textEdit->setStyleSheet("color: black");
            this->textEdit->setColOrigin("black");
        }
    }
}

bool MainWindow::event(QEvent * e) // overloading event(QEvent*) method of QMainWindow
{
    switch(e->type())
    {
        // ...

        case QEvent::WindowActivate : {
        if(!isActive)
          {
              if(mpOGLWidget->isVisible()) // get focus for windows
              {
                  mpOGLWidget->getTimeLine()->setFocus();
                  //childIsActive = true;
              }
              isActive = true;
             qApp->processEvents();
             activateWindow();
              isActive = true;
          }
          mpOGLWidget->getTimeLine()->emitFocusLostSignal();
          mpOGLWidget->hideBrushManager();
          QPoint current_pos = mpOGLWidget->pos();
          current_pos.setY(current_pos.y() + mpOGLWidget->height());
          mpOGLWidget->getTimeLine()->setViewPosition(current_pos);
          updateBlockFromTextEdit();
          //qDebug() << "SET_ACTIVE_MAIN_WINDOW";
          break ;
      }

      case QEvent::WindowDeactivate :
          // lost focus
          bool activeOther = false;
          if(mpOGLWidget->isActiveWindow())
              activeOther = true;
          if(mpOGLWidget->getTimeLine()->isActiveWindow())
              activeOther = true;
          if(!activeOther)
              isActive = false;
          //qDebug() << "LOSE_ACTIVE_MAIN_WINDOW";
          break ;

    } ;

    if (e->type() == QEvent::WindowStateChange) {
        if (isMinimized()) {
            mpOGLWidget->getTimeLine()->hide();
            mpOGLWidget->hide();
          isActive = false;
          e->ignore();
        } else {
          e->accept();
          mpOGLWidget->show();
          mpOGLWidget->getTimeLine()->show();
        }
      }
    return QMainWindow::event(e) ;
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    //mpOGLWidget->getTimeLine()->setFocus();

    if(mpOGLWidget != NULL)
        mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(mpOGLWidget != NULL)
        mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());
}

void MainWindow::focusInEvent(QFocusEvent * event)
{

}

void MainWindow::on_action_Show_triggered()
{
    a_clear_drawing->setEnabled(true);
    a_clear_drawingBuffer->setEnabled(true);
    a_show_last_drawing->setEnabled(true);
    a_save_drawing->setEnabled(true);

    showBoardSettings();
    a_show->setEnabled(false);
    ui->action_Show->setEnabled(false);
    a_hide->setEnabled(true);
    ui->action_Hide->setEnabled(true);
    if (!mpOGLWidget->m_manager.isAbleToDraw())
    {
        a_save_drawing->setEnabled(false);
        ui->actionSave_drawing->setEnabled(false);
    }

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
    mpOGLWidget->getTimeLine()->show();
    mpOGLWidget->show();
    //mpOGLWidget->pause(100);// wait for show window

   mpOGLWidget->setDelay(1000/lastInpuDelay);
    mpOGLWidget->setFixedSize(GLWIDGET_SIZE);
    mpOGLWidget->move(pos().x() + width() + WINDOW_MARGING, pos().y());

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
    //a_pause->setEnabled(true);
    //a_stop->setEnabled(true);
    a_font_canvas->setEnabled(true);
    a_color_canvas->setEnabled(true);
    a_record_to_file->setEnabled(true);
    ui->actionRecord_to_file->setEnabled(true);
    a_undo->setEnabled(true);
    a_redo->setEnabled(true);

    ui->action_Pause->setEnabled(false);
    a_pause->setEnabled(false);
    updateTextEditFromBlock(mpOGLWidget->getTimeLine()->getSelectedBlockPoint());
    mpOGLWidget->update();
    activateWindow();

}

void MainWindow::on_action_Hide_triggered()
{
    a_clear_drawing->setEnabled(false);
    a_clear_drawingBuffer->setEnabled(false);
    a_show_last_drawing->setEnabled(false);
    a_save_drawing->setEnabled(false);
   // if(mpOGLWidget->getStatus() == mpOGLWidget->PLAY || mpOGLWidget->getStatus() == mpOGLWidget->PAUSE)
      //  mpOGLWidget->stopAnimated();
    mpOGLWidget->hide();
    mpOGLWidget->getTimeLine()->hide();
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
    ui->actionRecord_to_file->setEnabled(false);   

   on_block_text_buttons_toolbar(false);
}

void MainWindow::on_action_Clear_TextEdit_triggered()
{
    this->textEdit->newText();
    this->commandTextEdit->newText();
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
    commandTextEdit->setFont(font);
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

        //textEdit->setTextColor("#000000");
        //commandTextEdit->setTextColor("#000000");
        commandTextEdit->setFont(font);
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
    colorm = QColorDialog::getColor(textEdit->getColOrigin(), this);
    //!!!!!!!!!!!
    if(colorm.isValid())
    {
        QString col = colorm.name();
        //textEdit->setTextColor(col);
        textEdit->setColOrigin(colorm);
        QString temp = textEdit->toPlainText();
        textEdit->clear();
        textEdit->insertPlainText(temp);

        //commandTextEdit->setTextColor(col);
        //commandTextEdit->setTextColor(col);

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
    colorm = QColorDialog::getColor(mpOGLWidget->getMainFillColor(), this);

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
    //// //qDebug() <<"UNDO";
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
   /* else {
        //qDebug() <<"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
        textEdit->setFocus();

        QString str = ui->lineEdit_Find->text();
            QList<QTextEdit::ExtraSelection> extraSelections;
            textEdit->moveCursor(QTextCursor::Start);
            QColor color = QColor("green");//QColor(Qt::white).lighter(130);
           while(textEdit->find(str))
                {
                    QTextEdit::ExtraSelection extra;
                    extra.format.setBackground(color);

                    extra.cursor = textEdit->textCursor();
                    extraSelections.append(extra);
                }
               textEdit->setExtraSelections(extraSelections);
    }*/
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

ProjectStartupSetting MainWindow::getCurentState()
{
    return curentState;
}

void MainWindow::keyEventSlot(QKeyEvent *event)
{
    QApplication::postEvent(this, event);
    //qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAA";
}

void MainWindow::setCurentState(ProjectStartupSetting state)
{
    curentState = state;
    //qDebug() << state.state;
}

void MainWindow::search()
{
    QString str = ui->lineEdit_Find->text();

    QList<QTextEdit::ExtraSelection> extraSelections;
    textEdit->moveCursor(QTextCursor::Start);
    QColor color ("green");// QColor(Qt::yellow).lighter(130);

    if(ui->check_case_sensitive->isChecked() == false
            && ui->check_whole_words->isChecked() == false)
    {
        while(textEdit->find(str))
        {           
            QTextEdit::ExtraSelection extra;
            extra.cursor = textEdit->textCursor();
            extra.format.setBackground(color);
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
    QTextCursor cursor = textEdit->textCursor();
    cursor.setPosition(extraSelections[0].cursor.position());
    textEdit->setTextCursor(cursor);
}

bool MainWindow::on_action_Save_as_triggered()
{

    QString suf;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), directory,
                                                    tr("Text Files (*.txt);;All Files (*.*)"), &suf, QFileDialog::DontUseNativeDialog | QFileDialog::DontConfirmOverwrite);
    fileName =  mSuffixFromFilter(suf, fileName);

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
                                                              tr("Text Files (*.txt);;All Files (*.*)"), 0, QFileDialog::DontUseNativeDialog);

    openFile( fileName);
    }
     textEdit->openText();
     commandTextEdit->openText();
}

bool MainWindow::openFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QFile::ReadOnly))
        {
            curFile = fileName;
            QString readedString = QString::fromLocal8Bit((file.readAll()));
            readedString.replace("\t", "    ");
             textEdit->setPlainText(readedString);
             commandTextEdit->setPlainText(readedString);
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
        commandTextEdit->clear();
    }
    textEdit->newText();

}



bool MainWindow::on_action_Save_Project_triggered()
{

   if(curProjectFile.isEmpty())
   {
        isActive = false;
        qApp->processEvents();
        activateWindow();
        QString suf;
       QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save project"), directory, tr("Project file (*.project )"), &suf, QFileDialog::DontUseNativeDialog | QFileDialog::DontConfirmOverwrite);
       fileName =  mSuffixFromFilter(suf, fileName);
        isActive = true;
        qApp->processEvents();
        activateWindow();
       if(fileName.isEmpty())   return false;
         curProjectFile = fileName;
   }

   QFile file(curProjectFile);
   if(file.open(QIODevice::WriteOnly))
   {
       ui->statusBar->showMessage("project saving...");

       mpOGLWidget->getTimeLine()->save(&file);
        QDataStream stream(&file);
        int state =   static_cast<int>(curentState.state);
              stream << curentState.advance_mode << state ;
       file.close();
       ui->statusBar->showMessage("project saved");
       mpOGLWidget->getTimeLine()->setIsProjectChanged(false);
       return true;
   }
   else
   {
       QMessageBox::warning(this, "Error",tr("Project\'s saving failed") //щ
                            .arg(curProjectFile).arg(file.errorString()));
       return false;
   }
}

void MainWindow::on_action_Open_Project_triggered()
{   
    isActive = true;
    qApp->processEvents();
    activateWindow();
    if (mpOGLWidget->getTimeLine()->isProjectChanged())
    {
    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Test", "Are you want to save changes in current project?",
                                   QMessageBox::Yes|QMessageBox::No | QMessageBox::Cancel);
     if (reply == QMessageBox::Cancel)
         return ;
     else
     if (reply == QMessageBox::Yes)
     {
       if (on_action_Save_Project_triggered() == false)
           return;
     }
    }
    mpOGLWidget->getTimeLine()->setIsProjectChanged(false);
    curProjectFile.clear();
    isActive = false;
    qApp->processEvents();
    activateWindow();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), directory, tr("Project file (*.project)"), 0, QFileDialog::DontUseNativeDialog);
   //qDebug() << "DDDDDDDDDDDDDDDDDDDDDDDDDDD fileName = " <<  fileName;
    isActive = true;
    qApp->processEvents();
    activateWindow();
    if(fileName.isEmpty())   return;
    curProjectFile = fileName;

    QFile file(curProjectFile);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->statusBar->showMessage("project opening...");


        mpOGLWidget->getTimeLine()->load(&file);
        QDataStream stream(&file);
        int state ;
        stream >> curentState.advance_mode >> state ;
       curentState.state = static_cast<VIEW_STATE>(state);
        file.close();
        ui->statusBar->showMessage("project opened");
       mpOGLWidget->getTimeLine()->sendUpdateModel();
       mpOGLWidget->setList(mpOGLWidget->getTimeLine()->getPointedBlocksDE());
        return ;
    }
    else
    {
        QMessageBox::warning(this, "Error",tr("Project\'s opening failed") //щ
                             .arg(curProjectFile).arg(file.errorString()));
        return ;
    }

}

void MainWindow::on_action_New_Project_triggered()
{
    //qDebug() << "NEW_PROJECT";
    if (mpOGLWidget->getTimeLine()->isProjectChanged())
    {
        QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Test", "Are you want to save changes in current project?",
                                       QMessageBox::Yes|QMessageBox::No | QMessageBox::Cancel);
         if (reply == QMessageBox::Cancel)
             return;
         else
         if (reply == QMessageBox::Yes)
         {
             if (on_action_Save_Project_triggered() == false)
                 return;
         }
    }

     curProjectFile.clear();
     //mpOGLWidget->getTimeLine()->emitResetProject();
     mpOGLWidget->getTimeLine()->resetProjectToDefault();
     // //qDebug() << "AAAAAAAAAAAAAAAAAAAA1";
     mpOGLWidget->getTimeLine()->setIsProjectChanged(false);
     mpOGLWidget->getTimeLine()->setBlocked(true);

     setEnabledToolBar(true);
     // //qDebug() << "AAAAAAAAAAAAAAAAAAAA3";
     on_action_Clear_TextEdit_triggered();
 ////qDebug() << "AAAAAAAAAAAAAAAAAAAA4";
     if (firstNewProjectCreating)
     {
         ProjectStartupSetting state = this->getCurentState();
         state.state = VIDEO_EDIT_PRO;
         this->setCurentState(state);
         firstNewProjectCreating = false;
     }

     if(isVisible())
        this->setCurentState(ProjectCreator::getProjectSetting(false, false));
     else
         this->setCurentState(ProjectCreator::getProjectSetting(true, false));
qDebug() << "111111111 curentState.state " <<(int) curentState.state;
 ////qDebug() << "AAAAAAAAAAAAAAAAAAAA6";

{
    setEnabledToolBar(false);
   /* if (curentState.state ==OPENING_PROJECT)
    {
        on_action_Open_Project_triggered();
        if(!isVisible())
            show();
        activateWindow();
        return;
    }*/
    VIEW_STATE temp_state = curentState.state;

     if(!curentState.advance_mode)
        setViewState(curentState.state);
     else
         setViewState(VIDEO_EDIT_PRO);


     if (temp_state != OPENING_PROJECT)
     {
         qDebug() << "AAAAAAAAAAAAAAAAAAAA8 ";
     //qDebug() << "AAAAAAAAAAAAAAAAAAAA   DAAAAAAAAAAAAAA";
     //qApp->processEvents(QEventLoop::AllEvents, 1000); //this lead to crash
    // //qDebug() << "AAAAAAAAAAAAAAAAAAAAww";
     switch (curentState.state) {
     case VIDEO_EDIT_TEXT:
     {
         DrawImageElm *first = new DrawImageElm(mpOGLWidget);
         QImage load(curentState.firstImage);
         qApp->processEvents();
         first->setDrawImage(load);



         DrawImageElm *last = new DrawImageElm(mpOGLWidget);
         QImage load2(curentState.lastImage);
         qApp->processEvents();
         last->setDrawImage(load2);

         first->setTypeId(Element_type::Image);
         last->setTypeId(Element_type::Image);

         DrawTextElm *text = new DrawTextElm(mpOGLWidget);

         first->setLifeTime(curentState.firsTime);
         last->setLifeTime(curentState.lastTime);

         first->setSize(width(), height());
         last->setSize(width(), height());
         text->setSize(width(), height());



         mpOGLWidget->getTimeLine()->addNewBlock(0, "NEW4", first);
         mpOGLWidget->getTimeLine()->addNewBlock(0, "NEW3", text);
         mpOGLWidget->getTimeLine()->addNewBlock(0, "NEW2", last);
         mpOGLWidget->getTimeLine()->setSelectedBlockPoint(0, 1);
         // //qDebug() << "AAAAAAAAAAAAAAAAAAAA9";
         break;
     }
     case VIDEO_EDIT_DEFAULT:
         mpOGLWidget->getTimeLine()->addNewBlock(0, "NEW1", new DrawTextElm(NULL));
         // //qDebug() << "AAAAAAAAAAAAAAAAAAAA10";
         break;
     default:
         break;
     }
////qDebug() << "AAAAAAAAAAAAAAAAAAAAqq";

   //  qApp->processEvents(QEventLoop::AllEvents, 1000);
}
     mpOGLWidget->getTimeLine()->sendUpdateModel();
     //qApp->processEvents(QEventLoop::AllEvents, 1000);

     mpOGLWidget->setList(mpOGLWidget->getTimeLine()->getPointedBlocksDE());
     mpOGLWidget->getTimeLine()->setBlocked(false);

}





}


void MainWindow::on_delayBtn_pressed()
{
    show_pause_menu();

   // textEdit->setFocus();
    if( isCommandTextEditFocused )
        commandTextEdit->setFocus();
    else
        textEdit->setFocus();
}

void MainWindow::delay_released()
{
   /* QTextCursor prev_cursor = textEdit->textCursor();
    prev_cursor.setPosition(QTextCursor::End);*/
    QString text = QString("\\p%1").arg(ui->spinBox_delayTB->value(), 2, 10, QChar('0'));
   // emit textEdit->setFocus();
   //  textEdit->setTextCursor(prev_cursor);
    if( isCommandTextEditFocused )
        textEdit->appendNoNL(text);
    else
        textEdit->insertPlainText(text);

    updateBlockFromTextEdit();

  /*  QString text = ui->action_clearTB->text();
    if( isCommandTextEditFocused )
        textEdit->appendNoNL(text);
    else
        textEdit->insertPlainText(text);*/
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

    // //qDebug() << "focus changed"<<isCommandTextEditFocused;
}
void MainWindow::onCommandFocusLost(){
    isCommandTextEditFocused=false;
    // //qDebug() << "focus changed"<<isCommandTextEditFocused;
}

void MainWindow::on_actionClear_drawing_triggered()
{
// //qDebug() << "on_actionClear_drawing_triggered()";
mpOGLWidget->clearFrameBuffer();
//// //qDebug() << mpOGLWidget->isClearFrameBuffer;
}

void MainWindow::on_actionClear_drawingBuffer_triggered()
{
    mpOGLWidget->drawBrushElm->clear();
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
        {
            textInField.chop(6);//Видаляємо перехід вліво КОСТИЛЯКА НА ЛОМАЦІ ))
            QTextCursor tCursor = commandTextEdit->textCursor();
            tCursor.clearSelection();
            commandTextEdit->setTextCursor(tCursor);
            commandTextEdit->setPreviousCursorPosition(tCursor.position() + delta);
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
    colorPkr = QColorDialog::getColor(mpOGLWidget->getMainFillColor(), this);
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
  //  qDebug() << "onTextChanged";
    QString str = textEdit->toPlainText();
    /*
     * bida z cursorom
    */

    QTextCursor cursor = textEdit->textCursor();
    int cursPos = textEdit->textCursor().position();
    int textSize = str.size();
    quint64 drawTime = 0;
    int pause = 0;
    int commandSize = 0;
    int status;

    if(ui != NULL)
        status = mParser.ParsingLine(mUnitList, str,drawTime, pause, commandSize, ui->slider_speedTB->value()); // add parsing /n
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
    //updateBlockFromTextEdit();
    onTextChangeUpdateTimer.start();
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

void MainWindow::updateTextEditFromBlock(QPoint point)
{
    //qDebug() << "SHOW SELECTED  " << point;
    if(point.x() != -1)
    {
        Element elm = mpOGLWidget->getTimeLine()->getBlock(point);
        if(elm.draw_element->getTypeId() == Element_type::Text)
        {
            DrawTextElm *text_elm = (DrawTextElm *)elm.draw_element;
            setEnabledToolBar(true);
            disconnect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
            textEdit->newText();
            commandTextEdit->newText();
            commandTextEdit->setPlainText(text_elm->getLoggerText());
            commandTextEdit->setPreviousCursorPosition(text_elm->getPrevTextCursor());
            commandTextEdit->textCursor().setPosition(text_elm->getTextCursor());
            textEdit->setPlainText(text_elm->getUnParsestring());
            connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
            return;
        }
    }
    //qDebug() << "DISABLE INPUT";
    textEdit->newText();
    commandTextEdit->newText();
    setEnabledToolBar(false);
}

void MainWindow::updateBlockFromTextEdit()
{
    QPoint point = mpOGLWidget->getTimeLine()->getSelectedBlockPoint();
    //qDebug() << "IMAGE" << commandTextEdit->getPreviousCursorPosition();
    if(point.x() != -1 )
    {
        Element elm = mpOGLWidget->getTimeLine()->getBlock(point);
        if(elm.draw_element->getTypeId() == Element_type::Text)
        {
            DrawTextElm *text_elm = (DrawTextElm *)elm.draw_element;
            text_elm->setDelay(ui->slider_speedTB->value()*10);
            text_elm->setUnParsestring(textEdit->toPlainText(), commandTextEdit->toPlainText());
            text_elm->setPrevTextCursor(commandTextEdit->getPreviousCursorPosition());
            text_elm->setTextCursor(commandTextEdit->textCursor().position());
            int change_time = text_elm->getDrawTime();
            if(change_time < 100)
                change_time = 100;
            ui->expected_time->setText("EXPECTED TIME:  " + QString::number(change_time) + " ms");
            if(ui->check_use_speed_value->isChecked())
            {
                mpOGLWidget->getTimeLine()->setBlockTime(point.x(), point.y(), change_time);
                mpOGLWidget->getTimeLine()->emitUpdateTrackAt(point.x());
                //mpOGLWidget->getTimeLine()->sendUpdateModel();
            }
        }
    }
}

void MainWindow::updateVisibleTextEdit(bool state)
{
    updateTextEditFromBlock(mpOGLWidget->getTimeLine()->getSelectedBlockPoint());
    commandTextEdit->textCursor().setPosition(commandTextEdit->getPreviousCursorPosition());
}

void MainWindow::on_action_Play_triggered()
{
    on_blockRightToolbar_exceptPlayPauseStop(false);
    ui->action_Play->setEnabled(false);
    a_play->setEnabled(false);

    //mpOGLWidget->setMayShowRedRectangle( false);

    this->ui->action_Hide->setEnabled(false);
    a_hide->setEnabled(false);

    a_stop->setEnabled(true);
        this->ui->action_Stop->setEnabled(true);

    if(mpOGLWidget->getStatus() == OGLWidget::PAUSE)
    {
        ui->action_Play->setText("Play");
    }
    else
    {
        mpOGLWidget->clearCanvas();
        mpOGLWidget->clearBuffer();
        mpOGLWidget->setFillColor(mpOGLWidget->getMainFillColor());
        drawCounter = 0;
    }


    onTextChanged();
    updateBlockFromTextEdit();
    // curent
    //((DrawTextElm*)drawElements[0])->setUnitList(mUnitList);
    //((DrawTextElm*)drawElements[0])->setUnParsestring(textEdit->toPlainText());
/*
     DrawTextElm drawTTElements(mpOGLWidget);
     drawTTElements.setDelay(ui->slider_speedTB->value());
     bool needToSaveLifeTime = ui->check_use_speed_value->isChecked();
     drawTTElements.setUnitList(mUnitList);
     drawTTElements.setUnParsestring(textEdit->toPlainText(), commandTextEdit->toPlainText(), needToSaveLifeTime);
     drawTTElements.save("curent");
     */
   /*  drawTTElements.load("curent.txt");
     // //qDebug() << "                                                          qqqqqqqq" << drawTTElements.getType();*/
 //   drawElements[0]->load("kaka");

  //  // //qDebug() << mUnitList.size();
   // QString name = this->windowTitle();
    play = true;
    //mpOGLWidget->editingRectangle.isEditingRectangleVisible = false;
    if(mpOGLWidget->getStatus() != OGLWidget::PLAY )
    {
        if(mpOGLWidget->drawAnimated(ui->actionRecord_to_file->isChecked()))
        {
            mpOGLWidget->setCurStatus( OGLWidget::PLAY );
            mpOGLWidget->getTimeLine()->play(); //off for test

            //qDebug("11111111111111111111111111111111");
        }
        else
        {
            on_action_Stop_triggered();
            mpOGLWidget->getTimeLine()->stop();
            //qDebug("222222222222222222222222222222222");
            return;
        }
    }
    hideBoardSettings();

    updateEditWidgets();


	ui->action_Pause->setEnabled(true);
	a_pause->setEnabled(true);

    on_block_text_buttons_toolbar(false);

    /*while( play && mpOGLWidget != 0 && mpOGLWidget->getStatus() != OGLWidget::STOP)
    {
        //while(mpOGLWidget->getStatus() == OGLWidget::PAUSE)
        if( mpOGLWidget->getStatus() != OGLWidget::PAUSE )
        {
            qApp->processEvents();
        }
        else
            qApp->processEvents();
    }
    on_action_Stop_triggered();*/


}

void MainWindow::on_action_Stop_triggered()
{
    on_blockRightToolbar_exceptPlayPauseStop(true);
  //  mpOGLWidget->setMayShowRedRectangle( true);
    a_stop->setEnabled(false);
     this->ui->action_Stop->setEnabled(false);



    this->ui->action_Hide->setEnabled(true);
    a_hide->setEnabled(true);



    if(mpOGLWidget->getStatus() != OGLWidget::STOP)
    {
        mpOGLWidget->stopAnimated();
        mpOGLWidget->getTimeLine()->stop();
       // qDebug("STOP");
    }
   /* textEdit->setEnabled(true);
    ui->action_Undo->setEnabled(true);
    ui->action_Redo->setEnabled(true);
    a_undo->setEnabled(true);
    a_redo->setEnabled(true);*/

    if(mpOGLWidget->isVisible()) //445
    {
        /*textEdit->setEnabled(true);
        commandTextEdit->setEnabled(true);*/   

       // on_block_text_buttons_toolbar(true);
        ui->action_Play->setEnabled(true);
        ui->action_Pause->setEnabled(false);
        a_pause->setEnabled(false);
        a_play->setEnabled(true);
        ui->action_Play->setText("Play");

        showBoardSettings();
        updateTextEditFromBlock(mpOGLWidget->getTimeLine()->getSelectedBlockPoint());

        //if last selected block dont have text type, text*s toolbar buttons dont must be enabled
        /*ListControll *temp_TL = mpOGLWidget->getTimeLine();
        QPoint sel_block = temp_TL->getSelectedBlockPoint();
        if (sel_block.x() > -1)
            if (temp_TL->getBlock(sel_block.x(),sel_block.y()).draw_element->getTypeId() != Element_type::Text)
                on_block_text_buttons_toolbar(false);*/

    }
    updateEditWidgets();

    //mpOGLWidget->editingRectangle.isEditingRectangleVisible = true;
    play = false;

}

void MainWindow::on_action_youTube_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Videos (*.avi *.mp4)"), 0, QFileDialog::DontUseNativeDialog);
    if(fileName.size() != 0)
    {
        youtube= new YouTubeWrapper(QString(fileName),this);
        youtube->getAuth()->startLogin(true);
    }

}
void MainWindow::on_action_Pause_triggered()
{
//mpOGLWidget->setMayShowRedRectangle( true);
    ui->action_Pause->setEnabled(false);
    a_pause->setEnabled(false);
    ui->action_Play->setText("Resume");
    //mpGLWidget->pauseAnimated();
    ui->action_Play->setEnabled(true);
    a_play->setEnabled(true);
    ui->action_Undo->setEnabled(true);
    ui->action_Redo->setEnabled(true);
    a_undo->setEnabled(true);
    a_redo->setEnabled(true);
    if (mpOGLWidget->getStatus() != OGLWidget::PAUSE)
    {
        mpOGLWidget->pauseAnimated();
        mpOGLWidget->getTimeLine()->pause();
    }

}





void MainWindow::on_action_Record_to_file_triggered()
{
    disconnect(ui->actionRecord_to_file,SIGNAL(triggered()),this,  SLOT(on_action_Record_to_file_triggered()));
    disconnect(a_record_to_file,SIGNAL(triggered()),this,  SLOT(on_action_Record_to_file_triggered()));

    isRecordToFile = !isRecordToFile;
    ui->actionRecord_to_file->setChecked(isRecordToFile);
    a_record_to_file->setChecked( isRecordToFile);
    //a_record_to_file->setChecked(!(a_record_to_file->isChecked()));
    connect(ui->actionRecord_to_file,SIGNAL(triggered()),this,  SLOT(on_action_Record_to_file_triggered()));
     connect(a_record_to_file,SIGNAL(triggered()),this,  SLOT(on_action_Record_to_file_triggered()));



   /* //qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA " << a_record_to_file->isChecked()
             << " ui->actionRecord_to_file" << ui->actionRecord_to_file->isChecked();*/

}

void MainWindow::on_action_About_triggered()
{
    messAbout.setText("This is program for making video-lessons.\nITA, 2015");
    messAbout.show();
}

void MainWindow::updateCurrentTxt()
{
    /*//qDebug() << "updateCurrentTxt";
    DrawTextElm drawTTElements(mpOGLWidget);
    drawTTElements.setDelay(ui->slider_speedTB->value());
    bool needToSaveLifeTime = ui->check_use_speed_value->isChecked();
    drawTTElements.setUnitList(mUnitList);
    drawTTElements.setUnParsestring(textEdit->toPlainText(), commandTextEdit->toPlainText(), needToSaveLifeTime);
    drawTTElements.save("curent");*/
}

void MainWindow::onStopShowLastDrawing()
{
    ui->actionShow_last_drawing->setText("show last drawing");
    ui->actionClear_drawing->setEnabled(true);
    a_clear_drawing->setEnabled(true);
    a_clear_drawingBuffer->setEnabled(true);
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
    ui->speedBtn->setEnabled(status);
    ui->slider_delayTB->setEnabled(status);
    ui->slider_speedTB->setEnabled(status);
    ui->spinBox_speedTB->setEnabled(status);
    ui->spinBox_delayTB->setEnabled(status);
    ui->check_use_speed_value->setEnabled(status);

    on_block_text_buttons_toolbar(status);

}

void MainWindow::on_actionShow_last_drawing_triggered()
{
    // //qDebug() << "show_last_drawing";
    bool isLastDrawingShow = mpOGLWidget->getShowLastDrawing();
   // mpOGLWidget->isMousePlay=true;
    if (isLastDrawingShow)
    {
        mpOGLWidget->stopShowLastDrawing();

        //ui->actionShow_last_drawing->setText("show last drawing");
    }
    else
    {
    mpOGLWidget->setShowLastDrawing(true);
    ui->actionShow_last_drawing->setText("stop show last drawing");
    ui->actionClear_drawing->setEnabled(false);
    a_clear_drawing->setEnabled(false);
    a_clear_drawingBuffer->setEnabled(false);
    }

}

void MainWindow::on_actionSave_drawing_triggered()
{
    QString suf;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Drawing (*.paint)"), &suf, QFileDialog::DontUseNativeDialog | QFileDialog::DontConfirmOverwrite);

    fileName =  mSuffixFromFilter(suf, fileName);
    if(!fileName.size())
        return;
    //qDebug() << fileName;
    mpOGLWidget->drawBrushElm->save(fileName);
}

void MainWindow::on_actionLoad_drawing_temp_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Drawing (*.paint)"), 0, QFileDialog::DontUseNativeDialog);
    if(!fileName.size())
        return;
    mpOGLWidget->drawBrushElm->load(fileName);
}

void MainWindow::on_actionHide_editBox_triggered()
{
    mpOGLWidget->forseEditBoxDisable = !mpOGLWidget->forseEditBoxDisable;
}

void MainWindow::on_slider_speedTB_sliderReleased()
{
    updateBlockFromTextEdit();
}

void MainWindow::on_block_text_buttons_toolbar(bool tt)
{
    textEdit->setEnabled(tt);
    commandTextEdit->setEnabled(tt);
    a_undo->setEnabled(tt);
    a_redo->setEnabled(tt);
    a_cut->setEnabled(tt);
    a_copy->setEnabled(tt);
    a_paste->setEnabled(tt);
    a_search->setEnabled(tt);
    a_undo->setEnabled(tt);
    a_clear_textedit->setEnabled(tt);
    a_select_all->setEnabled(tt);
     updateEditWidgets(tt);

     ui->action_Undo->setEnabled(tt);
     ui->action_Redo->setEnabled(tt);
     a_undo->setEnabled(true);

     this->ui->action_Copy->setEnabled(tt);
     this->ui->action_Cut->setEnabled(tt);
     this->ui->action_Paste->setEnabled(tt);
     this->ui->action_Undo->setEnabled(tt);
     this->ui->action_Redo->setEnabled(tt);
     this->ui->action_Select_all->setEnabled(tt);
     this->ui->action_Find->setEnabled(tt);
     this->ui->action_clearTB->setEnabled(tt);
     this->ui->action_Font->setEnabled(tt);
      this->ui->action_Color->setEnabled(tt);

}

void MainWindow::on_blockRightToolbar_exceptPlayPauseStop(bool tt)
{
    a_font_canvas->setEnabled(tt);
    a_color_canvas->setEnabled(tt);
    a_record_to_file->setEnabled(tt);
    a_clear_drawing->setEnabled(tt);
    a_clear_drawingBuffer->setEnabled(tt);
    a_show_last_drawing->setEnabled(tt);
    a_save_drawing->setEnabled(tt);
    a_open_project->setEnabled(tt);
    a_new_project->setEnabled(tt);
    a_save_project->setEnabled(tt);
    a_send_to_youtube->setEnabled(tt);

     this->ui->actionClear_drawing->setEnabled(tt);
    this->ui->actionLoad_drawing_temp->setEnabled(tt);
    this->ui->actionRecord_to_file->setEnabled(tt);
    this->ui->actionSave_drawing->setEnabled(tt);
    this->ui->actionShow_last_drawing->setEnabled(tt);
    this->ui->action_Board_Color->setEnabled(tt);
    this->ui->action_Board_Font->setEnabled(tt);
    ui->actionSend_to_youTube->setEnabled(tt);
}

