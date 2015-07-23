#include "drawElement.h"


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

void DrawElement::pause()
{
    bPause = true;
}

void DrawElement::stop()
{
    bPause = false;
}

void DrawElement::start()
{
    keyCouter = 0;
    tickTimer.start();
    bPause = false;
}

int DrawElement::getTickTime() const
{
    return tickTime;
}

void DrawElement::setTickTime(int value)
{
    tickTime = value;
}
DrawElement::DrawElement(OGLWidget *drawWidget, QObject *parent) : QObject(parent)
{
    pDrawWidget = drawWidget;
    bPause = false;
    x = 0;
    y = 0;
    z = 0;
    width = 100;
    height = 100;
    keyCouter = 0;
    lifeTime = 10;

    connect(pDrawWidget, SIGNAL(startSignal()), this, SLOT(start()));
    connect(pDrawWidget, SIGNAL(stopSignal()), this, SLOT(stop()));
    connect(pDrawWidget, SIGNAL(pauseSignal()), this, SLOT(pause()));
}

DrawElement::~DrawElement()
{

}

void DrawElement::draw()
{

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

QSize  DrawElement::getSize()
{
    return QSize(width,height);
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
