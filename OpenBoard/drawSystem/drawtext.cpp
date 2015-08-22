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
    //qDebug() << "LAST_CURSOR    " << textCursor;
    textCursor = value;
}

int DrawTextElm::getPrevTextCursor() const
{
    return prevTextCursor;
}

void DrawTextElm::setPrevTextCursor(int value)
{
    prevTextCursor = value;
}

void DrawTextElm::start()
{
    DrawElement::start();
        pDrawWidget->clearBuffer();
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
    int current_time;
    if(!bPlay)
        current_time =  pDrawWidget->getTimeLine()->getScalePointerPos();
    else
        current_time =  pDrawWidget->getTimeLine()->getPlayTime();
//    //qDebug() << current_time;
    if (current_time > 0 && mUnitList.size() != 1)
    {
       // //qDebug() << "startDrawTime:"<<startDrawTime;
        if((keyCouter == 0 || !bPlay) && curentCh != current_time )
       {
           pDrawWidget->clearCanvas();
           pDrawWidget->clearBuffer();
           keyCouter = 0;
           animationDelayCount = 1;
           animationDelayStart = 1;
           curentPauseValue = 0;
       }
       int realKeyValue = qCeil((double)(current_time - (curentPauseValue + startDrawTime)) / (double)((lifeTime - globalPauseLifeTime)/(mUnitList.size() - 1)));
       //qDebug() << mUnitList.size() << "            qwe         "<< realKeyValue;
      // //qDebug() << "cur " << current_time;
       ////qDebug() << "start " << startDrawTime;
       ////qDebug() << "list " << mUnitList.length();

   // if (keyCouter < realKeyValue)

        while( keyCouter < mUnitList.size() && pDrawWidget->listOfAnimationFigure.isEmpty() && (keyCouter <= realKeyValue || mUnitList[keyCouter]->unitType == 1) )
        {
            if(!bPlay)
                current_time =  pDrawWidget->getTimeLine()->getScalePointerPos();
            else
                current_time =  pDrawWidget->getTimeLine()->getPlayTime();

            //if ()
            {
                mUnitList.at(keyCouter)->draw(pDrawWidget);
                if( bPlay && mUnitList.at(keyCouter)->delay > 0)
                {
                    curentPauseValue += mUnitList.at(keyCouter)->delay;
                    if(mUnitList[keyCouter]->unitType == 1 && ((UnitCommand*) mUnitList[keyCouter])->getUnitCommandType() == "ErasePreChar")
                    {
                        animationDelayCount = mUnitList.at(keyCouter)->delay;
                        animationDelayStart = current_time;
                        pDrawWidget->crossTextDraw();
                    }
                    keyCouter++;
                    break;
                }
            }
            keyCouter++;

        }
      //  //qDebug() << "drawInfo   " << (double) 1 - (double)(qAbs(((current_time - startDrawTime) - (lifeTime/mUnitList.size())*keyCouter)))/(lifeTime/mUnitList.size());
      /*  if(keyCouter > 0 && keyCouter < mUnitList.size() && mUnitList.at(keyCouter)->unitType != mUnitList.at(keyCouter - 1)->unitType)
            pDrawWidget->update();*/

        if(mUnitList.size() != 0 && (mUnitList.size() - globalDeltaComandSize  - 1) != 0)
            tickTime = ((lifeTime - globalPauseLifeTime)/(mUnitList.size()  - 1));
       // //qDebug() << "                                                                           HHHH" << animationDelayCount - current_time;
        pDrawWidget->setAnimationPersentOfCross( (double)(current_time - animationDelayStart)/animationDelayCount);
           // //qDebug() << realKeyValue <<"    KEY    " << keyCouter;
    }

    pDrawWidget->drawTextBuffer(x, y, width, height, z);
    curentCh = current_time;
}

void DrawTextElm::setLifeTime(int value)
{
    lifeTime = value;
    if(mUnitList.size() != 0 && (mUnitList.size() - globalDeltaComandSize  - 1) != 0)
        tickTime = ((lifeTime - globalPauseLifeTime)/(mUnitList.size() - globalDeltaComandSize  - 1));
    //qDebug() << "tickTime4:"<<tickTime;

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
    // //qDebug() << value;
    globalPauseLifeTime = 0;
    globalDeltaComandSize = 0;
    //qDebug() << "START";
    myParser.ParsingLine(mUnitList, unParsestring, drawTime, globalPauseLifeTime, globalDeltaComandSize, delay);
    //qDebug() << "STOP";
    UnitCommand* command = new UnitCommand();
    command->setUnitCommandType("Update");
    command->setUnitData("1");
   // command->unitType = 2;
    mUnitList.append(command);
    /*if (needToSaveLifeTime)
        lifeTime=drawTime;*/
    if(mUnitList.size() > 0 && (mUnitList.size() - globalDeltaComandSize  - 1) != 0)
        tickTime = ((lifeTime - globalPauseLifeTime)/(mUnitList.size() - globalDeltaComandSize  - 1));
     //qDebug()<<"tickTime5:"<<tickTime;
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
         //qDebug()<<"tickTime6 :"<<tickTime;
    }

}

void DrawTextElm::setTickTime(int value)
{

}

bool DrawTextElm::load_add(QDataStream &stream)
{
    stream >> unParsestring >> loggerText >> textCursor >> prevTextCursor;
    setUnParsestring(unParsestring, loggerText);
    /*int sizeOfString = 0;
    stream >> sizeOfString;
    QByteArray data;
    data.resize(sizeOfString);
    // //qDebug() << "OUT " << sizeOfString;
    stream.readRawData(data.data(), sizeOfString);
    unParsestring = data;
    // //qDebug() << data;*/
    //myParser.ParsingLine(mUnitList, unParsestring,drawTime,delay);
}

bool DrawTextElm::save_add(QDataStream &stream)
{
 /*   stream << unParsestring.length();
    // //qDebug() << "IN " << unParsestring.length();
    stream.writeRawData(unParsestring.toLatin1().data(), unParsestring.length());*/
    stream << unParsestring << loggerText << textCursor << prevTextCursor;
}
