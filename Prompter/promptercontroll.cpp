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
void PrompterManager::setCurrentBlockTime(int newTime){
    if (currentBlockTime!=newTime)blockTimeChanged(newTime);
    currentBlockTime=newTime;
}
int PrompterManager::getCurrentBlockTime(){
    return currentBlockTime;
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
bool LessThan (const QObject *c1,  const QObject *c2){
    const PromptItem* typed1 = qobject_cast<const PromptItem*>(c1);
    const PromptItem* typed2= qobject_cast<const PromptItem*>(c2);
    //qDebug()<<"c1:"<<typed1->startTime();
   // qDebug()<<"c2:"<<typed2->startTime();
return typed1->startTime() < typed2->startTime();
}

int PrompterManager::addPrompt(int startTime, int lifeTime, QString text)
{
    if(!checkTimeisCorrect(startTime,lifeTime,-1))
    {
        qDebug() << "PROMPT_CONCURENT_ERROR";
        return PROMPT_CONCURENT_ERROR;
    }
    promptsData.push_back(new PromptItem(startTime,lifeTime,text));
qSort(promptsData.begin(),promptsData.end(),LessThan);
 view.engine()->rootContext()->setContextProperty("promptsData",QVariant::fromValue(promptsData));
    return PROMPT_SUCCESS;
}

int PrompterManager::setPromptStartTimeAt(int index, int startTime)
{
    if (index>=promptsData.length()) return PROMPT_INDEX_OUT_OF_RANGE;
    PromptItem *item = (PromptItem*)promptsData[index];
    item->setStartTime(startTime);
    qSort(promptsData.begin(),promptsData.end(),LessThan);
     view.engine()->rootContext()->setContextProperty("promptsData",QVariant::fromValue(promptsData));
    return PROMPT_SUCCESS;
}
bool PrompterManager::checkTimeisCorrect(int startTime,int lifeTime,int indexOfChangedElement){
    for (int i = 0; i<promptsData.length();i++){
        if (i==indexOfChangedElement)continue;
        PromptItem *item = (PromptItem*)promptsData[i];

        const int itemStartTime = item->startTime();
        const int itemLifeTime = item->lifeTime();
        bool intersectionOfTimeInterval = !((startTime>itemStartTime && startTime>itemStartTime+itemLifeTime) ||
                (startTime+lifeTime<itemStartTime && startTime+lifeTime<itemStartTime+itemLifeTime));
        if (intersectionOfTimeInterval)return false;
    }
    return true;
}

int PrompterManager::setPromptLifeTimeAt(int index, int lifeTime)
{
    if (index>=promptsData.length()) return PROMPT_INDEX_OUT_OF_RANGE;
    PromptItem *item = (PromptItem*)promptsData[index];
    if(!checkTimeisCorrect(item->startTime(),lifeTime,index))
    {
        qDebug() << "PROMPT_CONCURENT_ERROR";
        return PROMPT_CONCURENT_ERROR;
    }
    item->setLifeTime(lifeTime);
    qSort(promptsData.begin(),promptsData.end(),LessThan);
     view.engine()->rootContext()->setContextProperty("promptsData",QVariant::fromValue(promptsData));
    return PROMPT_SUCCESS;
}

int PrompterManager::setPromptTextAt(int index, QString text)
{
    if (index>=promptsData.length()) return PROMPT_INDEX_OUT_OF_RANGE;
    PromptItem *item = (PromptItem*)promptsData[index];
    item->setPromptText(text);
    qSort(promptsData.begin(),promptsData.end(),LessThan);
     view.engine()->rootContext()->setContextProperty("promptsData",QVariant::fromValue(promptsData));
    return PROMPT_SUCCESS;
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
