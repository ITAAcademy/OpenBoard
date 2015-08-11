#include "drawText.h"
#include "../TimeLine/listcontroll.h"

QString DrawTextElm::getLoggerText() const
{
    return loggerText;
}

void DrawTextElm::setLoggerText(const QString &value)
{
    loggerText = value;
}

quint64 DrawTextElm::getDrawTime() const
{
    return drawTime;
}


int DrawTextElm::getTextCursor() const
{
    return textCursor;
}

void DrawTextElm::setTextCursor(const int &value)
{
    textCursor = value;
}
DrawTextElm::DrawTextElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("text");
    setTypeId(Element_type::Text);
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
	        if(keyCouter == 0)
           {
               pDrawWidget->clearCanvas();
               pDrawWidget->clearBuffer();
           }
       int realKeyValue = (current_time - startDrawTime)*mUnitList.size()/lifeTime;
       qDebug() << "pDrawWidget->getTimeLine()->getPlayTime()"<< realKeyValue;
       qDebug() << "cur " << current_time;
       qDebug() << "start " << startDrawTime;
       qDebug() << "list " << mUnitList.length();

   // if (keyCouter < realKeyValue)

        while(keyCouter <=realKeyValue || (current_time - startDrawTime>lifeTime-50 && current_time - startDrawTime<=lifeTime))
        {
            current_time =  pDrawWidget->getTimeLine()->getPlayTime();
            if (keyCouter < mUnitList.size() && bPlay) mUnitList.at(keyCouter)->draw(pDrawWidget);
                    keyCouter++;
        }
      //  qDebug() << "drawInfo   " << (double) 1 - (double)(qAbs(((current_time - startDrawTime) - (lifeTime/mUnitList.size())*keyCouter)))/(lifeTime/mUnitList.size());
        if(keyCouter > 0 && keyCouter < mUnitList.size() && mUnitList.at(keyCouter)->unitType != mUnitList.at(keyCouter - 1)->unitType)
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

void DrawTextElm::setUnParsestring(const QString &valueUnParss, const QString &valueLogger)
{
    unParsestring = valueUnParss;
    loggerText = valueLogger;
    // qDebug() << value;
    myParser.ParsingLine(mUnitList, unParsestring, drawTime, delay);
    UnitCommand* command = new UnitCommand();
    command->setUnitCommandType("MoveLeft");
    command->setUnitData("1");
    mUnitList.append(command);
    /*if (needToSaveLifeTime)
        lifeTime=drawTime;*/
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
    stream >> unParsestring >> loggerText >> textCursor;
    setUnParsestring(unParsestring, loggerText);
    /*int sizeOfString = 0;
    stream >> sizeOfString;
    QByteArray data;
    data.resize(sizeOfString);
    // qDebug() << "OUT " << sizeOfString;
    stream.readRawData(data.data(), sizeOfString);
    unParsestring = data;
    // qDebug() << data;*/
    //myParser.ParsingLine(mUnitList, unParsestring,drawTime,delay);
}

bool DrawTextElm::save_add(QDataStream &stream)
{
 /*   stream << unParsestring.length();
    // qDebug() << "IN " << unParsestring.length();
    stream.writeRawData(unParsestring.toLatin1().data(), unParsestring.length());*/
    stream << unParsestring << loggerText << textCursor;
}
