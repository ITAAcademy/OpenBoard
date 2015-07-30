#include "drawElement.h"


OGLWidget *DrawElement::getDrawWidget() const
{
    return pDrawWidget;
}

void DrawElement::setDrawWidget(OGLWidget *value)
{
    disconnect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
    disconnect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
    disconnect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
    pDrawWidget = value;
    connect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
    connect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
    connect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
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
    lifeTime = 100;
    icon = QImage();

    connect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
    connect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
    connect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
}

DrawElement::~DrawElement()
{
    disconnect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
    disconnect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
    disconnect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
}

void DrawElement::paint()
{
    draw();
}

void DrawElement::draw()
{

}

bool DrawElement::load(QString path)
{
    QFile appFile(path);
    if(!appFile.exists())
        return false;
    lastPath = path;
    appFile.open(QFile::ReadOnly);
    QDataStream stream(&appFile);
    icon = load_image(stream);
    stream >> key >> lifeTime >> tickTime >> startDrawTime >> x >> y >> z >> width >> height >> keyCouter;
    load_add(stream);
    appFile.close();
}

bool DrawElement::save(QString path)
{
    QFile appFile(QString(path + "." + type));
    appFile.open(QFile::WriteOnly);
    QDataStream stream(&appFile);
    save_image(stream, icon);
    stream << key << lifeTime << tickTime << startDrawTime << x << y << z << width << height << keyCouter;
    save_add(stream);
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

bool DrawElement::reloadLastDone()
{
    if(lastPath.isNull())
        return false;
    QByteArray ba;
    QDataStream stream( &ba, QIODevice::ReadWrite );
    qDebug() << "MY1" << lifeTime;
    stream << key << lifeTime << tickTime << startDrawTime << x << y << z << width << height << keyCouter;
    stream.device()->reset();
    load(lastPath);
    stream >> key >> lifeTime >> tickTime >> startDrawTime >> x >> y >> z >> width >> height >> keyCouter;
    qDebug() << "MY2" << lifeTime;
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

void DrawElement::pause()
{
    bPause = true;
}

void DrawElement::stop()
{
    qDebug() << "stop";
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
    reloadLastDone();
    qDebug() << "START" << lastPath;
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
}

QSize  DrawElement::getSize()
{
    return QSize(width,height);
}


