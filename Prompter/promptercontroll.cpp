#include "promptercontroll.h"




void PrompterManager::update()
{
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents, 200);
    //createdBrush.color_img = BrushPainter::getInstance()->applyColor(createdBrush);
    // emit currentBrushChanged();
}

PrompterManager::PrompterManager(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{
    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
    //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);
    view.engine()->rootContext()->setContextProperty("prompterControll", this);
    view.engine()->rootContext()->setContextProperty("promptsData",QVariant::fromValue(promptsData));
    view.setSource(QUrl("qrc:/mainWindow.qml")); \
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setColor("transparent");
    view.setWidth(WINDOW_SIZE_WIDTH_DEFAULT);
    view.setHeight(WINDOW_SIZE_HEIGHT_DEFAULT);
    view.setMinimumHeight(WINDOW_SIZE_HEIGHT_MIN);
    view.setMinimumWidth(WINDOW_SIZE_WIDTH_MIN);
}

PrompterManager::~PrompterManager()
{
    close();
}


void PrompterManager::show()
{
    if (!showed)
    {
    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
            QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
    emit showSignal();
    showed=true;
    }
}

void PrompterManager::hide()
{
    if (showed)
    {
    view.hide();
    emit hideSignal();
    showed=false;
    }
    //emit currentBrushChanged();
}

void PrompterManager::close()
{

    view.engine()->removeImageProvider("loader");
    view.close();

}

QQmlContext *PrompterManager::getRootContext()
{
    return view.rootContext();
}

bool PrompterManager::isActive()
{
    return view.isActive();
}


void PrompterManager::setFocus()
{
    // view.setPosition(view.position());
    if(view.isVisible())
    {
        view.setVisible(false);
        view.setWindowState(Qt::WindowNoState);
        view.setVisible(true);
    }

}
QPoint PrompterManager::getCurrentBlockIndex() const
{
    return currentBlockIndex;
}

void PrompterManager::setCurrentBlockIndex(const QPoint &value)
{
    currentBlockIndex = value;
}

void PrompterManager::moveWindow()
{
    QPoint posMouse = QCursor::pos();
    view.setPosition( posMouse - framaMousePosition);
}

void PrompterManager::resizeWindowWidth(bool left)
{
    QPoint posMouse = QCursor::pos();
    if (!left )
    {
        int tt = posMouse.x() - view.x();
        if (tt < view.minimumWidth())
            tt = view.minimumWidth();

        view.setWidth(tt)  ;
    }
    else
    {

        int delta = view.x()-posMouse.x();
        int viewX = view.x();
       int tt = delta+view.width();

        if (tt < view.minimumWidth())
        {
            //view.setX(view.x() + (tt - view.minimumWidth()));
            tt = view.minimumWidth();
        }
        else{
            view.setX(viewX-delta);
            view.setWidth(tt);
        }


    }
}

void PrompterManager::resizeWindowHeight(bool up)
{
    QPoint posMouse = QCursor::pos();
    if (!up )
    {
        int tt = posMouse.y() - view.y();
        if (tt < view.minimumHeight())
            tt = view.minimumHeight();
        view.setHeight(tt)  ;
    }
    else
    {
        /*int tt = view.y();
        view.setY(posMouse.y());

        tt = view.height() + tt - view.y();
        if (tt < view.minimumHeight())
        {
            view.setY(view.y() + (tt - view.minimumHeight()));
            tt = view.minimumHeight();
        }

        view.setHeight(tt);*/
        int delta = view.y()-posMouse.y();
        int viewY = view.y();
       int tt = delta+view.height();

        if (tt < view.minimumHeight())
        {
            //view.setX(view.x() + (tt - view.minimumWidth()));
            tt = view.minimumHeight();
        }
        else{
            view.setY(viewY-delta);
            view.setHeight(tt);
        }

    }
}

void  PrompterManager::setPrevMousePosition()
{
    prevMousePosition = QCursor::pos();
}

void PrompterManager::addPrompt(int startTime, int lifeTime, QString text)
{
    promptsData.push_back(new PromptItem(startTime,lifeTime,text));
    view.engine()->rootContext()->setContextProperty("promptsData",QVariant::fromValue(promptsData));
}

bool PrompterManager::setPromptStartTimeAt(int index, int startTime)
{
    if (index>=promptsData.length()) return false;
    PromptItem *item = (PromptItem*)promptsData[index];
    item->setStartTime(startTime);
    return true;
}

bool PrompterManager::setPromptLifeTimeAt(int index, int lifeTime)
{
    if (index>=promptsData.length()) return false;
    PromptItem *item = (PromptItem*)promptsData[index];
    item->setLifeTime(lifeTime);
    return true;
}

bool PrompterManager::setPromptTextAt(int index, QString text)
{
    if (index>=promptsData.length()) return false;
    PromptItem *item = (PromptItem*)promptsData[index];
    item->setPromptText(text);
    return true;
}
void  PrompterManager::setFramaMousePosition( const int x,const int y)
{
    framaMousePosition.setX(x);
    framaMousePosition.setY(y);
}

void  PrompterManager::setFramaMousePosition( const QPoint x)
{
    framaMousePosition = x;
}
