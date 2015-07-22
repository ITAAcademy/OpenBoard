#include "drawText.h"

DrawTextElm::DrawTextElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{

}

DrawTextElm::~DrawTextElm()
{

}

void DrawTextElm::draw()
{
    if(keyCouter < mUnitList.size() && tickTimer.elapsed() > tickTime)
    {
        mUnitList.at(keyCouter++)->draw(pDrawWidget);
        tickTimer.restart();
    }
    pDrawWidget->drawTextBuffer(x, y, width, height);
}

void DrawTextElm::setLifeTime(int value)
{
    lifeTime = value;
    if(mUnitList.size() != 0)
        tickTime = lifeTime/mUnitList.size();
}

QList<Unit *> DrawTextElm::unitList() const
{
    return mUnitList;
}

void DrawTextElm::setUnitList(const QList<Unit *> &unitList)
{
    mUnitList = unitList;
    tickTime = lifeTime/unitList.size();
}

void DrawTextElm::setTickTime(int value)
{

}
