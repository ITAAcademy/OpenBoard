#include "drawText.h"
#include "../TimeLine/listcontroll.h"

QString DrawTextElm::getLoggerText() const
{
    return loggerText;
}

void DrawTextElm::setLoggerText(const QString &value)
{
    loggerText = value;
    qDebug() << "DrawTextElm::setLoggerText " << value;
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
    if(keyCouter == 0)
    {
        clearBuffer();
        clearCanvas();
    }
}


int DrawTextElm::getFirstSymbolOfString(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    while( i < index)
    {
        int nextLen = stringList[i].length();
        if(!symbol)
            nextLen++;
        sumLength +=  nextLen;
        i++;
    }
    //if(sumLength != 0)
    //  sumLength++;
    return sumLength;
}
int DrawTextElm::getLastSymbolOfString(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    while( i <= index)
    {
        int nextLen = stringList[i].length();
        if(!symbol)
            nextLen++;
        sumLength +=  nextLen;
        i++;
    }
    //if(sumLength != 0)
    //  sumLength++;
    return sumLength + 1;
}

QPoint DrawTextElm::convertTextBoxToBufferIndex(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    int numParagraph = 0;
    while( i < stringList.length())
    {
        //  // //qDebug() <<"stringList:"<<stringList.length();
        int lenNext;
        if(symbol)
            lenNext = stringList[i].length();
        else
            lenNext = stringList[i].length() + 1;
        sumLength += lenNext;
        //   // //qDebug() <<"sumLength:"<<sumLength;
        //        // //qDebug() <<"index:"<<index;
        //        // //qDebug() <<"I:"<<i;

        if(sumLength > index)
        {
            int colum = index - (sumLength - lenNext);
            int row = i;
            return QPoint( colum, row);
        }
        i++;
    }
    return QPoint(stringList[i - 1].length(), i - 1);
}


bool DrawTextElm::drawAnimationFigure(AnimationFigure &figure, QPoint scale)
{
    return drawAnimationFigure(figure.rect.x(), figure.rect.y(), figure.rect.width(), figure.rect.height(), animationPersentOfCross, (OGLWidget::FigureType)figure.type, figure.fill, scale);
}


bool DrawTextElm::drawAnimationFigure(int x, int y, int width, int height, double persent, OGLWidget::FigureType type, bool fill, QPoint scale)
{
    isCrossingNow=true;
    //qDebug() << "wqweqweqwe "  << persent;
    if(persent < 0.98f)
    {

        //     drawFigure(int x, int y, int x2, int y2,
        //                 OGLWidget::FigureType type, bool fill = true, QColor col = "#FF0000", float size = 2)
        // pDrawWidget->drawFigure(x, y, x + (width - x)*persent, height, type, fill);



        // pDrawWidget->drawFigure(x,y,x + (width - x)*persent,height,type,fill);
        pDrawWidget->drawFigure(x , y , x + (width - x)*persent, height, type, fill, "#FF0000", 3* scale.y());
        //persent += animationPersentOfCross;
        // QThread::currentThread()->msleep(10);
        if(pDrawWidget->getStatus() == OGLWidget::STOP )
        {
            isCrossingNow=false;
            return true;
        }
        isCrossingNow=false;
        return false;
    }
    else
    {
        pDrawWidget->drawFigure(x, y, width, height, type, fill, "#FF0000", 3*scale.y());
        isCrossingNow=false;
        return true;
    }

}

double DrawTextElm::getAnimationPersentOfCross() const
{
    return animationPersentOfCross;
}

void DrawTextElm::setAnimationPersentOfCross(double value)
{
    animationPersentOfCross = value;
    ////qDebug() << "QWE    " << value;
}

int DrawTextElm::getRowFromTextBoxIndex(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    while( i < stringList.length())
    {
        int lenNext;
        if(symbol)
            lenNext = stringList[i].length();
        else
            lenNext = stringList[i].length() + 1;
        sumLength += lenNext;
        if(sumLength > index)
        {
            return i;
        }
        i++;
    }
}

int DrawTextElm::getCountNullString(int index)
{
    int i = 0;
    int sumLength = 0;
    while( i <= index)
    {
        int nextLen = stringList[i].length();
        if(nextLen == 0)
            sumLength++;
        i++;
    }
    return sumLength;
}

DrawTextElm::DrawTextElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("text");
    setTypeId(Element_type::Text);
    aspectRatio = true;

    indexInList = 1;
    deleteWT = 0;
    fMetrics = new QFontMetrics(QFont(font));

    font = "LC Chalk";
    isWord  =  true;

    indexInList = 1;
    indexRowInList = 0;
    cursorIndex = 0;
    stringList.append("");

    indexW = 1;
    indexRow = 0;
    marginLeft = 20;
    marginTop = 40;

    line_x = marginLeft;
    line_y = lineHeight + pt;

    pt = 36;
    lineHeight = LINE_HEIGHT;

    isCrossingNow = false;
    scroll = 0;
    //clearBuffer();

    setTextFont(QFont("123")); //444
    mainFillColor = QColor(0,0,0,0);

}

DrawTextElm::~DrawTextElm()
{
    if(fMetrics != NULL)
        delete fMetrics;
    if(textureIndex != -1)
        pDrawWidget->deleteTexture(textureIndex);
}

void DrawTextElm::clearBuffer()
{
    qDebug() << "CLEAR_TEXT_BUFFER";
    colors.clear();
    //colors.append(mainFillColor);

    //startMarker.value=getMainFillColor();
    currentColor=mainFillColor;
    cross.clear();
    cross.append(0); // для визова зачеркування якщо стрічка зацінчується
    stringList.clear();
    stringList.append("");
    cursorIndex = 0;
    deleteWT = 0;
    crossWithAnimation = false;
}



void DrawTextElm::draw()
{
    drawFrameNumber%=25;
    drawFrameNumber++;
    if (drawFrameNumber==1 || drawFrameNumber==13)textCursorVisible=!textCursorVisible;
    // qDebug() << "void DrawTextElm::draw()" << pDrawWidget->getTimeLine()->getPlayTime();

    GLint curentBuff;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &curentBuff);
    pDrawWidget->bindBuffer(renderFbo.frameBuffer);
    pDrawWidget->disableShader();

    pDrawWidget->clearTexture(textureIndex);
    pDrawWidget->clearFrameBuffer(fboWrapper);
    pDrawWidget->clearFrameBuffer(renderFbo);

    float koff1=(float)pDrawWidget->getWax()/width;
    float  koff2=(float)pDrawWidget->getWay()/height;

    if(staticText)
    {

        //if (width>=height)koff=(float)pDrawWidget->getWax()/width;
        //else koff = (float)pDrawWidget->getWay()/height;
        //if (koff1>koff2)koff=koff1;
        // else koff=koff2;*/

        textFont.setPointSize(mainTextFont.pointSize());
        textFont.setBold(mainTextFont.bold());
        textFont.setItalic(mainTextFont.italic());
        textFont.setUnderline(mainTextFont.underline());
        textFont.setStrikeOut(mainTextFont.strikeOut());
        textFont.setFamily(mainTextFont.family());
        textFont.setStyleStrategy(QFont::PreferQuality);
        pt = textFont.pointSize();
        lineHeight = LINE_HEIGHT;
        QStringList list = unParsestring.split("\n");
        line_y = fMetrics->height();
        for(int i = 0; i < list.length() /*&& i < (height/(lineHeight + pt)) - 1*/; i++)
        {
            pDrawWidget->drawTextFromTexture(0, line_y , z, list[i],textureIndex, mainFillColor, textFont,koff1,koff2);
            //pDrawWidget->myRenderText(pDrawWidget, 0, (i + 1)*(lineHeight + pt), z, unParsestring, mainFillColor, textFont);
            line_y += lineHeight + pt;
        }

        pDrawWidget->enableShader();
        pDrawWidget->bindBuffer(curentBuff);
        pDrawWidget->clearFrameBuffer(curentBuff);
        pDrawWidget->drawTexture(0,0,renderFbo.tWidth, renderFbo.tHeight,
                                 renderFbo.bindedTexture, 0, 1, 1, z );
        return;
    }

    int current_time;
    if(!bPlay)
        current_time =  pDrawWidget->getTimeLine()->getScalePointerPos();
    else
        current_time =  pDrawWidget->getTimeLine()->getPlayTime();

    if (current_time > 0 && mUnitList.size() != 1)
    {
        // //qDebug() << "startDrawTime:"<<startDrawTime;
        if((keyCouter == 0 || !bPlay) && curentCh != current_time )
        {
            clearCanvas();
            clearBuffer();
            keyCouter = 0;
            animationDelayCount = 1;
            animationDelayStart = 1;
            curentPauseValue = 0;
        }
        int realKeyValue = qRound((double)(current_time - (curentPauseValue + startDrawTime)) / (double)((lifeTime*staticMoment - globalPauseLifeTime)/(mUnitList.size() - 1)));
        //qDebug() << mUnitList.size() << "            qwe         "<< realKeyValue;
        // //qDebug() << "cur " << current_time;
        ////qDebug() << "start " << startDrawTime;
        ////qDebug() << "list " << mUnitList.length();

        // if (keyCouter < realKeyValue)

        while( keyCouter < mUnitList.size() && listOfAnimationFigure.isEmpty() && (keyCouter <= realKeyValue || mUnitList[keyCouter]->unitType == 1) )
        {
            if(!bPlay)
                current_time =  pDrawWidget->getTimeLine()->getScalePointerPos();
            else
                current_time =  pDrawWidget->getTimeLine()->getPlayTime();

            //if ()
            {
                mUnitList.at(keyCouter)->draw(this);
                if( bPlay && mUnitList.at(keyCouter)->delay > 0)
                {
                    curentPauseValue += mUnitList.at(keyCouter)->delay;
                    if(mUnitList[keyCouter]->unitType == 1 && ((UnitCommand*) mUnitList[keyCouter])->getUnitCommandType() == "ErasePreChar")
                    {
                        animationDelayCount = mUnitList.at(keyCouter)->delay;
                        animationDelayStart = current_time;
                       // crossTextDraw(koff1, koff2);
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
        setAnimationPersentOfCross( (double)(current_time - animationDelayStart)/animationDelayCount);
        // //qDebug() << realKeyValue <<"    KEY    " << keyCouter;
    }

    drawTextBuffer(0, 0, pDrawWidget->getWax(), pDrawWidget->getWay(), z, true,koff1,koff2);
    curentCh = current_time;

         //pDrawWidget->drawTextFromTexture(0, line_y , z, list[i],textureIndex, mainFillColor, textFont,koff1,koff2);
         //pDrawWidget->myRenderText(pDrawWidget, 0, (i + 1)*(lineHeight + pt), z, unParsestring, mainFillColor, textFont);


     //


    /*
     * render renderBuff
     */
    pDrawWidget->enableShader();
    pDrawWidget->bindBuffer(curentBuff);
    pDrawWidget->clearFrameBuffer(curentBuff);
    pDrawWidget->drawTexture(0,0,renderFbo.tWidth, renderFbo.tHeight,
                             renderFbo.bindedTexture, 0, 1, 1, z );
}

void DrawTextElm::drawTextCursor(int cursorRow, int cursorColumn,float scaleX,float scaleY)
{
if (!pDrawWidget->isShowTextCursor())return;
    int cursorWidth = 5;
    int cursorHeight = fMetrics->height();
    int cursorPosY = lineHeight+pt;
        cursorPosY *=cursorRow;
     QString textBeforeCursor = stringList[cursorRow].mid(0,cursorColumn);
    int cursorPosX =marginLeft + fMetrics->width(textBeforeCursor);
    float drawWidth =(cursorPosX+cursorWidth)*scaleX;
            float drawHeight = (cursorPosY+cursorHeight)*scaleY;
    pDrawWidget->drawRectangle(cursorPosX*scaleX,cursorPosY*scaleY,drawWidth,drawHeight,QColor(Qt::white));
}

void DrawTextElm::setLifeTime(int value, bool feedBack, bool visual)
{
    DrawElement::setLifeTime(value, feedBack, visual);
    if(feedBack)
        return;

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
    //qDebug() << " DrawTextElm::setUnParsestring:"<<unParsestring;
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

bool DrawTextElm::load_add(QDataStream &stream, float version)
{
    stream >> unParsestring >> loggerText >> textCursor >> prevTextCursor >> mainTextFont >> mainFillColor >> bCalcTime;
    setUnParsestring(unParsestring, loggerText);
    if(version > 2.8)
    {
        stream >> staticText;
    }
    if(version > 2.9)
    {
        stream >> staticMoment;
    }

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
    stream << unParsestring << loggerText << textCursor << prevTextCursor << mainTextFont << mainFillColor << bCalcTime << staticText << staticMoment;
}

void DrawTextElm::clearCanvas(int m_x, int m_y)
{
    //QMetaObject::invokeMethod(canvas, "clear");
    symbolPositionList.clear();
    listWords.clear();
    listStr.clear();
    indexRow = 0;
    indexW = 1;
    marginLeft = m_x;

    line_x = m_x;
    lineHeight = LINE_HEIGHT;
    pt = textFont.pointSize();
    line_y = fMetrics->height();
        marginTop = m_y;
    scroll = 0;
    //listStr[0] = 0;
}

void DrawTextElm::insertToBuffer(const QChar ch)
{
    crossText();
    // crossTextDraw();
    while (isCrossingNow);
    QPoint convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
    // // //qDebug() << convertedIndex << " " << stringList.size() << " " << ch;
    QString &str =  stringList[convertedIndex.y()];
    if (convertedIndex.x()>=str.length())
        str.append(ch);
    else
        str.insert(convertedIndex.x(), ch);
    cross.insert(cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y(), 0);
    //  //qDebug() << "insert " << cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y() << "        " << cross;

    //  DrawTextElm(convertedIndex.y());
    listChars.append(ch);
    int crossIndex = cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y();
    //ZIGZAG: NEED TO RESIZE ???
    /*if (crossIndex>colors.length()-1)
    {
        colors.reserve(crossIndex*2);
    }*/
    /*if (crossIndex>colors.size()-1){
        colors.resize(crossIndex*2);
    }*/
    colors.insert(crossIndex,currentColor);
    //qDebug() << "1234567890             " << str;
    emit drawTextChanged();

    // pause(delay);

}

void DrawTextElm::moveCursor(int n, bool withWrapShift)
{
    //update();
    crossText();
    int j = 0;
    int shift = 0;
    /*if(withWrapShift)
    {
        int max = qAbs (convertTextBoxToBufferIndex(cursorIndex).y() - convertTextBoxToBufferIndex(cursorIndex + n).y());
        while( j < wrapShift.size() && j < max) //bhfhfghfghfghfghfghfghfghfghfghfghgf\ml0011
            if(wrapShift[j++] <= cursorIndex)
                shift = j;
    }
    */
    /* int maxSymbol = getLastSymbolOfString(stringList.length() - 1, false);
    if( maxSymbol < n)
        n = maxSymbol;*/
    // //qDebug() << "MAX_SYMBOL" << maxSymbol;
    if(n > 0)
        cursorIndex += n + shift;
    else
        cursorIndex += n -  shift;
    //cursorIndex += n;
    if(cursorIndex < 0)
        cursorIndex = 0;
    //   // //qDebug() << "Cursor move to n " << n <<"=== cur state " << cursorIndex << "QPOINT  " << convertTextBoxToBufferIndex(cursorIndex);

}

void DrawTextElm::nextRow( int n, int Row, bool wrap)
{
    //isLastRow();
    QPoint convertedIndex;
    if(Row == -1)
    {
        if( n == -1)
            convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
        else
            convertedIndex = convertTextBoxToBufferIndex(n);
    }
    else
        convertedIndex = QPoint(n, Row);

    int i = convertedIndex.y() + 1;
    QString lastStr = stringList[i - 1].right(stringList[i - 1].length() - convertedIndex.x());

    //qDebug() << "           LASTSTR    " << lastStr << "         " << convertedIndex.x();
    if(i >= stringList.length())
        stringList.append(lastStr);
    else
        stringList.insert(i, lastStr);
    stringList[i - 1].resize(convertedIndex.x());
    moveCursor(1, false );
    /* last work
    moveCursor(lastStr.length() + 1);
    */
    /* if(wrap)
        testWrap(i);*/
    emit drawTextChanged();

}

void DrawTextElm::drawTextBuffer( int m_x, int m_y, int m_width, int m_height, int z, bool cross, float scaleX,float scaleY)
{
    // qDebug() << "stringList:"<<stringList;
    pDrawWidget->setBusy(true);
    //if(!crossTextV2())
    //   return QPoint(0, 0);
    //int width = fMetrics->width(str)*1.125 ;//+ fMetrics->leftBearing(str.at(0)) + fMetrics->rightBearing(str.at(0));
    textFont.setPointSize(mainTextFont.pointSize());
    textFont.setBold(mainTextFont.bold());
    textFont.setItalic(mainTextFont.italic());
    textFont.setUnderline(mainTextFont.underline());
    textFont.setStrikeOut(mainTextFont.strikeOut());
    lineHeight = LINE_HEIGHT;
    //1234
    // textFont.setPointSize(20);
    textFont.setFamily(mainTextFont.family());
    textFont.setStyleStrategy(QFont::PreferQuality);

    if(fMetrics != NULL)
        delete fMetrics;
    fMetrics = new QFontMetrics(textFont);
    pt = textFont.pointSize();

    clearCanvas(m_x, m_y);
    int maxDrawElm = (height/(lineHeight + pt));
    ////qDebug() << "DRAW   "   <<  maxDrawElm;
    int CurRow = convertTextBoxToBufferIndex(cursorIndex).y();
    if(CurRow >= indexRowInList + maxDrawElm)
    {
        indexRowInList += CurRow - (indexRowInList + maxDrawElm) + 1;
    }
    if(CurRow < indexRowInList)
    {
        indexRowInList = CurRow;
    }
    indexFirstDrawSymbol = getFirstSymbolOfString(indexRowInList, false);

    int lastRow = indexRowInList + maxDrawElm - 1;
    if(lastRow >= stringList.length())
        lastRow = stringList.length() - 1;
    if(lastRow < 0)
        lastRow = 0;
    indexLastDrawSymbol = getLastSymbolOfString(lastRow, false);

    ////qDebug() << "First  " << indexFirstDrawSymbol <<    "   " <<  indexRowInList << "    " << indexLastDrawSymbol;
    //  // //qDebug() << indexRowInList << "   indexFirstDrawSymbol   :           " << indexFirstDrawSymbol << cross;
    //   // //qDebug() << "START draw with indexRowInList " << indexRowInList << "MAX elm " << maxElm << "CUR " << CurRow;
    int i = indexRowInList;
//line_y = fMetrics->height();
    struct ColorMarker{
        int charCount;
        QColor color;
    };
    QVector<ColorMarker> colorMarkers;
   // QColor lastColor;
    int charsOfThisColor = 0;
    /* if (colors.length()>0)
     {
         lastColor=colors[0];
         charsOfThisColor++;
     }*/
     // qDebug() << "colors.length():"<<colors.length();
    qDebug() << "colors:";
    for (int k=0;k<colors.length()-1;k++)
    {
   // qDebug()<<colors[k].name();
        /*qDebug() << "comparsion of colors:";
        qDebug() << "colors[k]:"<<colors[k];
        qDebug() << "lastColor:"<<lastColor;*/

       // qDebug() << "charsOfThisColor:"<<charsOfThisColor;
        //ZIGZAG:DRAW COLORED TEXT
        if (colors[k]==colors[k+1])charsOfThisColor++;
        else{
            charsOfThisColor++;
            ColorMarker marker;
            marker.color=colors[k];
            marker.charCount=charsOfThisColor;
            colorMarkers.append(marker);
            charsOfThisColor=0;
        }

    }
        ColorMarker marker;
       if(colors.length()>0)
       {
           charsOfThisColor++;
           marker.color=colors[colors.length()-1];
       }
       else  marker.color=mainFillColor;

       marker.charCount=charsOfThisColor;
       colorMarkers.append(marker);

   /* for (int k = 0 ; k < colorMarkers.length();k++){
        qDebug() << "colorMarkers "<<k<<":"<<colorMarkers[k].charCount;
    }*/
int colorStartIndex=0;
    while( i < stringList.length() && i < indexRowInList + maxDrawElm)
    {
        //// //qDebug() << stringList[i] << "@";
       // QStringList tabulationStr = stringList[i].split("\t");
        //TODO SET TEXT COLOR TO CANVAS COLOR
        //setFillColor(fillColor);
        // for(int j = 0; j < tabulationStr.size(); j++)
        // {
        //    fillText(tabulationStr[j], x, y);
        //     x += fMetrics->width(tabulationStr[j] + "\t");
        //  }
        //  // //qDebug() << "C:"<<colors.length();
        // qDebug() << "colors.length()"<<colors.length();



   // qDebug() << "colorMarkers length:"<<colorMarkers.length();
       // qDebug()<<"foreach colorMarkers i:"<<i;

        for (int k = 0 ; k< colorMarkers.length();k++)
        {
           // qDebug() <<"k:"<<k<<"colorStartIndex:"<<colorStartIndex;
            int columnOfColorStrBegin;
            int columnOfColorStrEnd;

            int rowOfColorStrBegin =  convertTextBoxToBufferIndex(colorStartIndex).y();//Рядок в якому починається стрічка з кольором
            int rowOfColorStrEnd = 0;
            //Якщо не дійшли до останнього кольору, то встановл. рядок кінця стрічи з початку наступної кольорової
            if (k<colorMarkers.length()-1)rowOfColorStrEnd=convertTextBoxToBufferIndex(colorStartIndex+colorMarkers[k].charCount ).y();
            //Якщо останній колір, то така стрічка закінчується в останньому рядку
            else rowOfColorStrEnd=stringList.length()-1;
            //Якщо ColorIndex в цій стрічці відсутній, то переходим на інший ColorIndex
            if (!(i>=rowOfColorStrBegin && i<=rowOfColorStrEnd))
                continue;
            //Якщо на рядку, в якому починається кольорова стрічка — то стовпчик початку берем одразу з QList<ColorIndex> colors
            if (i==rowOfColorStrBegin)
                columnOfColorStrBegin =  convertTextBoxToBufferIndex(colorStartIndex ).x();
            //Інакше стовпчик початку - нульовий стовпчик . Інфа 100%
            else columnOfColorStrBegin = 0;
            //Якщо на останньому кольорі, то стовпчик кінця — індекс останнього символу стрічки.
            if (k==colorMarkers.length()-1) columnOfColorStrEnd =  stringList[i].length();
            else
                //якщо не останній колір і на останній стрічці, то стовпчик кінця — стовпчик початку наступної стрічки з кольором
                if (i==stringList.length()-1)  columnOfColorStrEnd =  convertTextBoxToBufferIndex(colorStartIndex+colorMarkers[k].charCount ).x();
            //Якщо не останній колір і не остання стрічка, то стовпчик кінця —
                else
                {
                    //Якщо в цій самій стрічці починається інша кольорова стрічка то кінцевий стовпчик поточної
                    //Кольорової стрічки - це почато наступної
                    if (convertTextBoxToBufferIndex(colorStartIndex+colorMarkers[k].charCount ).y()==i)
                        columnOfColorStrEnd =  convertTextBoxToBufferIndex(colorStartIndex+colorMarkers[k].charCount).x();
                    //Інакше КС(кінцевий стовпчик) — це кінець стрічки
                    else columnOfColorStrEnd =  stringList[i].length();
                }
            QString textToWarp;
            //Якщо перша кольорова стрічка, то додаєм до локального Х ширину стрічки, що йшла до кольорової стрічки
            if (k==0)
                textToWarp= stringList[i].mid(0,columnOfColorStrBegin);
            else  {
                int  columnOfColorStrBeginPrev=0;
                if (convertTextBoxToBufferIndex(colorStartIndex-colorMarkers[k-1].charCount ).y()==i)
                    columnOfColorStrBeginPrev=convertTextBoxToBufferIndex(colorStartIndex-colorMarkers[k-1].charCount ).x();
                textToWarp= stringList[i].mid(columnOfColorStrBeginPrev,columnOfColorStrBegin-columnOfColorStrBeginPrev);
            }
            line_x += fMetrics->width(textToWarp);
            //setFillColor(colors[k].value);
            fillColor = colorMarkers[k].color;
            qDebug() << "draw color k:"<<k;
            QString textToFill = stringList[i].mid(columnOfColorStrBegin,columnOfColorStrEnd-columnOfColorStrBegin);
            qDebug() << "textToFill:"<<textToFill;
            pDrawWidget->drawTextFromTexture(line_x,line_y,z,textToFill,textureIndex, fillColor,textFont,scaleX,scaleY);
        colorStartIndex+=textToWarp.length();//colorMarkers[k].charCount;//ZIGZAG:WHICH OF THESE ?
        }
        line_y += (lineHeight + pt);
        line_x = m_x;
        // localX=marginLeft;
        i++;
    }
    if(cross)
        crossTextDraw(scaleX, scaleY);
    pDrawWidget->setBusy(false);
    int cursorRow = convertTextBoxToBufferIndex(cursorIndex).y();
    int cursorColumn = convertTextBoxToBufferIndex(cursorIndex).x();
    if (textCursorVisible)
  drawTextCursor(cursorRow,cursorColumn,scaleX,scaleY);
    // updateGL();

}

bool DrawTextElm::crossText()
{
    //  // //qDebug() << "www " << deleteWT << cross;
    int spacePaid = 1;
    int row = convertTextBoxToBufferIndex(cursorIndex).y();
    while(deleteWT > 0)
    {
        //// //qDebug() << "DW " << deleteWT << convertTextBoxToBufferIndex(cursorIndex);
        int cursor = cursorIndex - row;
        /*   space paid
        *
        *  while( cursor - spacePaid >= 0)
        {
            QPoint convert = convertTextBoxToBufferIndex(cursor - spacePaid, true);
            //// //qDebug() << "\nSYMBOL                 :::" << cursor  - spacePaid <<"         " << stringList[convert.y()][convert.x()];
            if(stringList[convert.y()][convert.x()] <= 0x20)
                spacePaid++;
            else
                break;
        }*/
        cursor -= spacePaid;
        if(cursor >= 0 && cursor < cross.length())
        {
            if(crossWithAnimation)
                cross[cursor] = -1;
            else
                cross[cursor] = 1;
        }

        deleteWT--;
        spacePaid++;
    }


}

int DrawTextElm::getCursorIndex() const
{
    return cursorIndex;
}

void DrawTextElm::setCursorIndex(int value)
{
    cursorIndex = value;
}


void DrawTextElm::crossOutWithAnimation(int n)
{
    //  // //qDebug() << "URAAAA!!!  " << deleteWT;
    crossOutLastSymbol(n);
    crossWithAnimation = true;
}

void DrawTextElm::update(){
    pDrawWidget->setBusy(true);
    crossText();
    // crossTextDraw();
    pDrawWidget->moveEvent(NULL);
    //  pDrawWidget->setBusy(false);
}

QColor DrawTextElm::getMainFillColor() const
{
    return mainFillColor;
}

void DrawTextElm::setMainFillColor(const QColor &value)
{
    mainFillColor = value;
    setFillColor(value);
    currentColor=value;
}


int DrawTextElm::getCountDeleteWT() const
{
    return deleteWT;
}


bool DrawTextElm::getBNeedCalcTime() const
{
    return bCalcTime;
}

void DrawTextElm::setBNeedTime(bool value)
{
    bCalcTime = value;
}

bool DrawTextElm::isStaticText() const
{
    return staticText;
}

void DrawTextElm::setStaticText(bool value)
{
    staticText = value;
}

double DrawTextElm::getStaticMoment() const
{
    return staticMoment;
}

void DrawTextElm::setStaticMoment(double value)
{
    staticMoment = value;
}
QFont DrawTextElm::getTextFont() const
{
    return mainTextFont;
}


void DrawTextElm::setTextFont(const QFont &value)
{
    mainTextFont = value;
    if(fMetrics != NULL)
        delete fMetrics;
    fMetrics = new QFontMetrics(value);
    pt = value.pointSize();

}

bool DrawTextElm::setDrawWidget(OGLWidget *value)
{
    /* if (DrawElement::setDrawWidget(value))
    {
        if (!value->isInit())
            return false;
        textureIndex = pDrawWidget->loadTexture(QImage(pDrawWidget->getWax(),pDrawWidget->getWay(),QImage::Format_ARGB32));
    }*/
    if(value == pDrawWidget && value != NULL)
    {
        //  qDebug() << "VALUE  " << fboWrapper.errorStatus;
        if(renderFbo.errorStatus != 0 &&  pDrawWidget->isInit()){
            renderFbo = pDrawWidget->initFboWrapper(pDrawWidget->getWax(),pDrawWidget->getWay());//TODO
            return false;
        }
    }

    if(((!DrawElement::setDrawWidget(value) && textureIndex != 4294967295) || failedLoad < 0) || (!pDrawWidget->isVisible() || !pDrawWidget->isInit()))
    {
        return 0;
    }
    textureIndex = pDrawWidget->loadTexture(QImage(pDrawWidget->getWax(),pDrawWidget->getWay(),QImage::Format_ARGB32));

    if(textureIndex == 4294967295)
        failedLoad--;

}

void DrawTextElm::deleteFromBuffer(int n)
{
//ZIGZAG:INSERT COLOR DELETION

    crossText();
    int mustDell = qAbs(n);
    int crossCursor = cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y();
    colors.remove(n);
    int i = n;
    while( i != 0)
    {
        if(i > 0)
            cross.removeAt(crossCursor);
        else
            cross.removeAt(crossCursor + n);
        if(i > 0)
            i--;
        else
            i++;
        //qDebug() << "REMOVE" << crossCursor + i << "   " << " ::  " << cross;
    }
    while(mustDell > 0)
    {
        QPoint convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
        // cross.insert(cursorIndex - convertedIndex.y(), 0);
        // //qDebug() << convertedIndex << "DELL   " << mustDell;
        QString &str =  stringList[convertedIndex.y()];
        int realDell;
        if(n > 0)
        {
            if(mustDell > str.length() - convertedIndex.x())
                realDell = str.length() - convertedIndex.x();
            else
                realDell = mustDell;
            str.remove(convertedIndex.x(), realDell);
            mustDell -= realDell;
            if(mustDell > 0)
            {
                if(convertedIndex.y() + 1 < stringList.length())
                {
                    //  cursorIndex--;
                    mustDell--;
                    stringList[convertedIndex.y()].append(stringList[convertedIndex.y() + 1]);
                    stringList.removeAt(convertedIndex.y() + 1);
                }
                else
                    break;
            }
        }
        else
        {
            if(mustDell > convertedIndex.x())
                realDell = convertedIndex.x();
            else
                realDell = mustDell;
            str.remove(convertedIndex.x() - realDell, realDell);
            cursorIndex -= realDell;
            mustDell -= realDell;
            if(mustDell > 0)
            {
                if(convertedIndex.y() != 0)
                {
                    cursorIndex--;
                    mustDell--;
                    stringList[convertedIndex.y() - 1].append(str);
                    stringList.removeAt(convertedIndex.y());
                }
                else
                    break;
            }
        }

    }
    /*
    if (convertedIndex.x()>=str.length())
        str.append(ch);
    else

    DrawTextElm(convertedIndex.y());
    listChars.append(ch);
*/
    emit drawTextChanged();
    // pause(delay);
}

void DrawTextElm::crossOutLastSymbol( int n)
{
    // QPoint delPos = symbolPositionList.at(symbolPositionList.length() - 1 - deleteWT);
    //int k = 0;
    //QString str = listWords.right(1 + deleteWT);

    /*int widht = fMetrics->width(str)*1.5;
    int deltaY = deltaY = (widht - x) /(maxWidth - marginLeft);

    if(x - widht <= marginLeft)
    {
        deltaY++;
    }

    tx = maxWidth *deltaY - (widht - x + marginLeft);

    ty -= (lineHeight + pt)*deltaY;

    fillText("/", delPos.x(), delPos.y());
    fillText("\\", delPos.x(), delPos.y());*/
    //if()
    deleteWT += n;

}

bool DrawTextElm::crossTextDraw(float scale_x, float scale_y )
{
    glDisable(GL_DEPTH);

    for( int i = 0; i < listOfAnimationFigure.length(); i++)
    {
        if(drawAnimationFigure(listOfAnimationFigure[i], QPoint(scale_x, scale_y)))
        {
            //   qDebug() << "LAST" << listOfAnimationFigure[i].start << "     " << listOfAnimationFigure[i].stop << "     " << cross.length();
            for( int j = listOfAnimationFigure[i].start; j < listOfAnimationFigure[i].stop; j++) // convert to cross without animation
            {
                if(j < cross.length())
                {
                    cross[j] = 1;
                    qDebug() << cross;
                }
                else
                    break;
            }
            listOfAnimationFigure.remove(i);
            //qDebug() << cross;
        }

    }

    glEnable(GL_DEPTH);
    int y;
    int yIndex;
    int x1, x2, x;
    bool lastGood = false;
    bool needNextRow = false;
    int last = cross.length();
    if(indexLastDrawSymbol != 0)
        last = indexLastDrawSymbol;

    for(int i = indexFirstDrawSymbol; i < cross.length(); i++)
    {

        if(cross[i] != 0)
        {
            QPoint conv = convertTextBoxToBufferIndex(i, true);
            //    conv = convertTextBoxToBufferIndex(i + conv.y());
            if(!lastGood)
            {
                x1 = marginLeft + fMetrics->width(stringList[conv.y()].left(conv.x()));
                x = i;
                yIndex = /*(lineHeight + pt)* */  convertTextBoxToBufferIndex(i, true).y();
                lastGood = true;
                continue;
            }
            if(conv.y() == yIndex)
            {
                if(i != cross.length() - 1)
                    continue;
            }
            {
                needNextRow = true;
            }
        }
        if(lastGood)
        {

            QPoint conv = convertTextBoxToBufferIndex(i - 1, true);
            //    conv = convertTextBoxToBufferIndex(i + conv.y() + 1);
            // //qDebug() << "YYYYYYYYYYYYYYYYYYYYYYY" << y;
            yIndex -=   indexRowInList;
           // yIndex++;
            // //qDebug() << "YYYYYYYYYYYYYYYYYYYYYYY2" << y;
            y=fMetrics->height()/2;
            y += (lineHeight + pt)*yIndex;
            // QRect rect = fm.boundingRect( text);
            //y -= fMetrics->height();// first paid + midle LABEL1

            x2 = marginLeft + fMetrics->width(stringList[conv.y()].left(conv.x() + 1));
            y += marginTop;
            if( cross[i - 1] == -1 )
            {
                // //qDebug() << "FIRST";
                // drawAnimationFigure(x1, y, x2, y, LINE, 0);
                //drawAnimationFigure(x1, y, x2, y, LINE, 0);
                if(pDrawWidget->getStatus()  == OGLWidget::PLAY) //curStatus
                {
                    listOfAnimationFigure.append(AnimationFigure(QRect(x1 * scale_x, y*scale_y, x2 * scale_x, y *scale_y), (int)OGLWidget::LINE, x, i));
                    //    qDebug() << "FIRST" << x << "     " << i << "     " << cross.length();
                    for( int j = x; j < i; j++) // convert to cross without animation
                        cross[j] = 0;
                }
                else
                {
                    pDrawWidget->drawFigure(x1* scale_x,y*scale_y, x2*scale_x, y*scale_y, OGLWidget::LINE, false, "#FF0000", 3*scale_y);
                }

            }
            else{
                //drawFigure(x1, y, x2, y, LINE, 0);

                pDrawWidget->drawFigure(x1*scale_x,y*scale_y, x2*scale_x, y*scale_y, OGLWidget::LINE, false, "#FF0000", 3*scale_y);
                // //qDebug() << "SECOND";
            }
            lastGood = false;
            if(needNextRow)
                i--;
        }
    }

}

void DrawTextElm::isLastRow()
{
    //int maxElm = (height()/lineHeight + pt);

}

void DrawTextElm::setFillColor(QColor col)
{
    QString sColor = QString("rgba(%1, %2, %3, %4)").arg(col.red()).arg(col.green()).arg(col.blue()).arg(col.alpha());
    fillColor = col;
}
