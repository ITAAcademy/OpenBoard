#include "drawText.h"
#include "../TimeLine/listcontroll.h"
DrawTextElm::DrawTextElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("text");
}

DrawTextElm::~DrawTextElm()
{

}

void DrawTextElm::draw()
{
   // if(keyCouter < mUnitList.size() && bPlay && tickTimer.elapsed() > tickTime)
    //{
      //  mUnitList.at(keyCouter)->draw(pDrawWidget);
        //keyCouter++;
     //   tickTimer.restart();
   // }
    int current_time =  pDrawWidget->getTimeLine()->getPlayTime();
    if (current_time > 0)
    {
       // qDebug() << "startDrawTime:"<<startDrawTime;
       int realKeyValue = (current_time - startDrawTime)*mUnitList.size()/lifeTime;
       qDebug() << "pDrawWidget->getTimeLine()->getPlayTime()"<< current_time;
   // if (keyCouter < realKeyValue)

        while(keyCouter <=realKeyValue)
        {
            if (keyCouter < mUnitList.size() && bPlay) mUnitList.at(keyCouter)->draw(pDrawWidget);
                    keyCouter++;
        }
      //  qDebug() << "drawInfo   " << (double) 1 - (double)(qAbs(((current_time - startDrawTime) - (lifeTime/mUnitList.size())*keyCouter)))/(lifeTime/mUnitList.size());
        if(keyCouter < mUnitList.size() - 1 && mUnitList.at(keyCouter)->unitType != mUnitList.at(keyCouter - 1)->unitType)
            pDrawWidget->update();
        pDrawWidget->setAnimationPersentOfCross( qAbs((double) 1 - (double)(qAbs(((current_time - startDrawTime) - (tickTime)*keyCouter)))/(tickTime)));
    }
    pDrawWidget->drawTextBuffer(x, y, width, height, z);


}

void DrawTextElm::setLifeTime(int value)
{
    lifeTime = value;
    if(mUnitList.size() != 0)
        tickTime = lifeTime/mUnitList.size();
    qDebug() << "tickTime4:"<<tickTime;

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

   /* Unit unit;
    unit.setUnitData(QString(" "));
    mUnitList.append(&unit);*/

    if(mUnitList.size() > 0)
        tickTime = lifeTime/mUnitList.size();
     qDebug()<<"tickTime5:"<<tickTime;
}

void DrawTextElm::setUnitList(const QList<Unit *> &unitList)
{
    mUnitList = unitList;


  /*  Unit unit;
    unit.setUnitData(QString(" "));
    mUnitList.append(&unit);*/

    if(unitList.size() != 0)
    {
        tickTime = lifeTime/unitList.size();
         qDebug()<<"tickTime6 :"<<tickTime;
    }

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
