#include "drawText.h"

DrawTextElm::DrawTextElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("text");
}

DrawTextElm::~DrawTextElm()
{

}

void DrawTextElm::draw()
{
    if(keyCouter < mUnitList.size() && bPlay && tickTimer.elapsed() > tickTime)
    {
        mUnitList.at(keyCouter)->draw(pDrawWidget);
        keyCouter++;
        tickTimer.restart();
    }
    qDebug() << "drawInfo" << mUnitList.size() << "     " << keyCouter;
    pDrawWidget->drawTextBuffer(x, y, width, height, z);

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
QString DrawTextElm::getUnParsestring() const
{
    return unParsestring;
}

void DrawTextElm::setUnParsestring(const QString &value)
{
    unParsestring = value;
    // qDebug() << value;
    myParser.ParsingLine(mUnitList, unParsestring);
    if(mUnitList.size() > 0)
        tickTime = lifeTime/mUnitList.size();
}

void DrawTextElm::setUnitList(const QList<Unit *> &unitList)
{
    mUnitList = unitList;
    if(unitList.size() != 0)
        tickTime = lifeTime/unitList.size();
}

void DrawTextElm::setTickTime(int value)
{

}

bool DrawTextElm::load_add(QDataStream &stream)
{
    stream >> unParsestring;
    /*int sizeOfString = 0;
    stream >> sizeOfString;
    QByteArray data;
    data.resize(sizeOfString);
    // qDebug() << "OUT " << sizeOfString;
    stream.readRawData(data.data(), sizeOfString);
    unParsestring = data;
    // qDebug() << data;*/
    myParser.ParsingLine(mUnitList, unParsestring);
}

bool DrawTextElm::save_add(QDataStream &stream)
{
 /*   stream << unParsestring.length();
    // qDebug() << "IN " << unParsestring.length();
    stream.writeRawData(unParsestring.toLatin1().data(), unParsestring.length());*/
    stream << unParsestring;
}
