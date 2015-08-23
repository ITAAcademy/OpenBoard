#include "drawElement.h"


OGLWidget *DrawElement::getDrawWidget() const
{
    return pDrawWidget;
}

bool DrawElement::setDrawWidget(OGLWidget *value)
{
    if(value == pDrawWidget && value != NULL)
        return false;
    if(pDrawWidget != NULL)
    {
        disconnect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
        disconnect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
        disconnect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    }
    pDrawWidget = value;
    setFBOWrapper(pDrawWidget->initFboWrapper());//TODO
    connect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
    connect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
    connect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    return true;
}

QString DrawElement::getKey() const
{
    return key;
}

void DrawElement::setKey(const QString &value)
{
    key = value;
}
DrawElement::DrawElement(OGLWidget *drawWidget, QObject *parent) : QObject(parent)
{
    pDrawWidget = drawWidget;
    bPause = false;
    bPlay = false;
    x = 0;
    y = 0;
    z = 0;
    width = 100;
    height = 100;
    keyCouter = 0;
    lifeTime = -1;
    icon = QImage();
    typeId = Element_type::Empty;

    if(pDrawWidget != NULL)
    {
        connect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
        connect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
        connect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    }
    qDebug() << "RRRR BEFORE";
   // if (pDrawWidget)
//fboWrapper=pDrawWidget->initFboWrapper();
 qDebug() << "RRRR AFTER";
}

void DrawElement::copy(DrawElement *elm)
{
    lifeTime = elm->getLifeTime();
    tickTime = elm->getTickTime();
    startDrawTime = elm->getStartDrawTime();
    x = elm->getX();
    y = elm->getY();
    z = elm->getZ();
    width = elm->getSize().width();
    height = elm->getSize().height();
    //typeId = elm->getTypeId();
}

DrawElement::~DrawElement()
{


 qDebug() << "delete DrawElement";
    if(pDrawWidget != NULL)
    {
        pDrawWidget->deleteFBO(fboWrapper);
        disconnect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
        disconnect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
        disconnect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    }
}

void DrawElement::paint()
{
    pDrawWidget->bindBuffer(fboWrapper.frameBuffer);
    draw();
    pDrawWidget->bindBuffer(0);
    if(aspectRatio)
        pDrawWidget->paintBufferOnScreen(fboWrapper,x, y, width, width, z);
    else
        pDrawWidget->paintBufferOnScreen(fboWrapper,x, y, width, height, z);
}

void DrawElement::draw()
{

}

FBOWrapper DrawElement::getFBOWrapper()
{
 return fboWrapper;
}
DrawElement::setFBOWrapper(FBOWrapper wrapper)
{
this->fboWrapper=wrapper;
}

bool DrawElement::load(QString path)
{
    QFile appFile(path);
    if(!appFile.exists())
        return false;
    lastPath = path;
    appFile.open(QFile::ReadOnly);
    this->load(&appFile);
    appFile.close();

}

bool DrawElement::load(QIODevice* device)
{
    /*QDataStream stream(device);

    int temp_type;
    stream >> temp_type  >> key >> lifeTime >> tickTime >> startDrawTime >> x >> y >> z >> width >> height >> keyCouter;
   typeId = static_cast<Element_type>(temp_type);
    icon = load_image(stream);
    load_add(stream);*/
    loadTypeId(device);
    loadRest(device);
}
bool DrawElement::loadTypeId(QIODevice* device)
{
    QDataStream stream(device);
    int temp_type;
    stream >> temp_type  ;
   typeId = static_cast<Element_type>(temp_type);
}
bool DrawElement::loadRest(QIODevice* device)
{
    QDataStream stream(device);
    stream  >> key >> lifeTime >> tickTime >> startDrawTime >> x >> y >> z >> width >> height >> keyCouter;
    //if (typeId == Element_type::Image)
        icon = load_image(stream);
    load_add(stream);
}

bool DrawElement::save(QIODevice* device)
{
    QDataStream stream(device);

    int temp_type = static_cast<int>(typeId);
    stream << temp_type << key << lifeTime << tickTime << startDrawTime << x << y << z << width << height << keyCouter;
    //if (typeId == Element_type::Image)
        save_image(stream, icon);
    save_add(stream);
}

bool DrawElement::save(QString path)
{
    QFile appFile(QString(path + "." + type));
    appFile.open(QFile::WriteOnly);
    this->save(&appFile);
    appFile.close();
    /*QImage icon;
    int lifeTime;
    int tickTime;
    int startDrawTime;
    int x, y, z, width, height;
    int keyCouter;
    QTimer lifeTimer;
    QElapsedTimer tickTimer;

    OGLWidget *pDrawWidget;
    bool bPause;
    */

}

void DrawElement::clear()
{

}

bool DrawElement::reloadLastDone()
{
    if(lastPath.isNull())
        return false;
    QByteArray ba;
    QDataStream stream( &ba, QIODevice::ReadWrite );
    //qDebug() << "MY1" << lifeTime;
    stream << key << lifeTime << tickTime << startDrawTime << x << y << z << width << height << keyCouter;
    stream.device()->reset();
    load(lastPath);
    stream >> key >> lifeTime >> tickTime >> startDrawTime >> x >> y >> z >> width >> height >> keyCouter;
    //qDebug() << "MY2" << lifeTime;
}

QRect DrawElement::getRect()
{
    return QRect(x, y, width, height);
}

void DrawElement::setPosition(QPoint pos)
{
    x = pos.x();
    y = pos.y();
}

void DrawElement::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void DrawElement::setDelay(int d)
{
    delay=d;
}

void DrawElement::setSize(QSize pos)
{
    width = pos.width();
    height = pos.height();
}

void DrawElement::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void DrawElement::setRect(QRect rect)
{
    x = rect.x();
    y = rect.y();
    width = rect.width();
    height = rect.height();
}

void DrawElement::setRect(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
int DrawElement::getX() const
{
    return x;
}

void DrawElement::setX(int value)
{
    x = value;
}

int DrawElement::getY() const
{
    return y;
}

void DrawElement::setY(int value)
{
    y = value;
}

int DrawElement::getZ() const
{
    return z;
}

void DrawElement::setZ(int value)
{
    z = value;
}

int DrawElement::getLifeTime() const
{
    return lifeTime;
}

void DrawElement::setLifeTime(int value)
{
    lifeTime = value;
}

int DrawElement::getStartDrawTime() const
{
    return startDrawTime;
}

void DrawElement::setStartDraw(int value)
{
    startDrawTime = value;
}

QImage DrawElement::getIcon() const
{
    return icon;
}

void DrawElement::setIcon(const QImage &value)
{
    icon = value;
}

bool DrawElement::getPause() const
{
    return bPause;
}

void DrawElement::setPause(bool value)
{
    bPause = value;
}

void DrawElement::setType(const char name[])
{
    strcpy(type, name);
}

QString DrawElement::getType()
{
    return QString(type);
}

void DrawElement::setTypeId( Element_type val)
{
    this->typeId = val;
}

Element_type DrawElement::getTypeId()
{
    return this->typeId;
}

void DrawElement::pause()
{
    bPause = true;
}

void DrawElement::stop()
{
    ////qDebug() << "stop";
    bPause = false;
    keyCouter = 0;
    bPause = false;
    bPlay = false;
    tickTimer.restart();
}

void DrawElement::start()
{

    keyCouter = 0;
    bPause = false;
    bPlay = true;

    /*
     * NOT NEED SLOW
     *
     * reloadLastDone();
     *
     */


    //qDebug() << "START" << lastPath;
}

void DrawElement::restart()
{
    keyCouter = 0;
    tickTimer.restart();
}

bool DrawElement::load_add(QDataStream &stream)
{

}

bool DrawElement::save_add( QDataStream &stream)
{

}

bool DrawElement::save_image(QDataStream &stream, QImage img)
{
    stream << img.size().width() << img.size().height() << (int)img.format();
    stream.writeRawData((const char*)img.bits(), img.byteCount());
    //qDebug() <<"image saved:"<<img.byteCount();
}

QImage DrawElement::load_image(QDataStream &stream)
{
    int w, h, format;
    stream >> w >> h >> format;
    QImage img_temp(w, h, (QImage::Format)format);

    stream.readRawData((char*)img_temp.bits(), img_temp.byteCount());
    return img_temp;
}

int DrawElement::getTickTime() const
{
    return tickTime;
}

void DrawElement::setTickTime(int value)
{
    tickTime = value;
    // //qDebug()<<"tickTime3:"<<tickTime;
}

QSize  DrawElement::getSize()
{
    return QSize(width,height);
}


