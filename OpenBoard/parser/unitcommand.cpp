#include "unitcommand.h"
#include "drawSystem/drawtext.h"


UnitCommand::UnitCommand() : Unit()
{
    Type = "";
    unitType = 1;
}

UnitCommand::~UnitCommand()
{

}

void UnitCommand::setUnitCommandType(QString str)
{
    Type = str;
}
bool isLower(const ColorMarker &c1,const ColorMarker &c2)
{
    return c1.startIndex < c2.startIndex;
}

void UnitCommand::changeColor(DrawTextElm *canvas)
{
   // canvas->setFillColor(QColor(unit_data));
    // //qDebug() << "void UnitCommand::changeColor(DrawTextElm *canvas)";
    ColorMarker startMarker;
    qDebug() << "change color cursor index:"<<canvas->getCursorIndex();
      int len = unit_data.length();
      QString countString="0";
      if (len-7>0)countString=unit_data.mid(7,len-7);//-7 because # symbol presents in string
      int count =countString.toInt();
      qDebug()<<"COUNT:"<<count;
      if (count>0)//colorize characters at right
    startMarker.startIndex=canvas->getCursorIndex();
      else startMarker.startIndex=canvas->getCursorIndex()+count;//colorize characters at left
    startMarker.value=unit_data.mid(0,7);//MAYBE PROBLEM || BUG (need 7) check later



    qDebug() << "UNIT_DATA:"<<unit_data;
    qDebug() << "COUNT_STRING:"<<countString;

    ColorMarker endMarker;
    if (count!=0)
    { 
        if (count>0)
        endMarker.startIndex = canvas->getCursorIndex()+count;
        else endMarker.startIndex = canvas->getCursorIndex();
        //endMarker.value="#000000";//NOT USED, USE CANVAS COLOR
        endMarker.useDefaulColor = true;
        startMarker.terminant=&endMarker;
        qDebug()<<"before for";
        for (int i=0;i<canvas->colors.length();i++){
            if ((canvas->colors[i].startIndex>=startMarker.startIndex) &&
                    (canvas->colors[i].startIndex <= endMarker.startIndex))
            {
                qDebug()<< "before null check";
                if (canvas->colors[i].terminant!=NULL)
                    //delete canvas->colors[i].terminant;
                {
                    ColorMarker beginMarker =canvas->colors[i];
                    qDebug() << "beforeremoveall";

                    if (canvas->colors[i].terminant->startIndex>endMarker.startIndex)
                        canvas->colors[i].startIndex=endMarker.startIndex+1;
                    else
                    {
                        canvas->colors.removeAll(*(beginMarker.terminant));
                         canvas->colors.removeAt(i);
                    }
                    qDebug () << "canvas->colors[i].terminant!=NULL";

                //canvas->colors.removeAll(beginMarker);
                qDebug() << "beforeremoveat";
               ;
                qDebug() << "delete terminant";
                }
                else
                canvas->colors.removeAt(i);
            }
    }


    }
canvas->colors.push_back(endMarker);
    canvas->colors.push_back(startMarker);

    qSort(canvas->colors.begin(),canvas->colors.end(),isLower);
    qDebug()<<"colors:";
    for (int i = 0; i < canvas->colors.length();i++)
        qDebug()<<"startIndex:"<<canvas->colors[i].startIndex
               <<"useDefaulColor:"<<canvas->colors[i].useDefaulColor;
}

void UnitCommand::nextLine(DrawTextElm *canvas)
{
    canvas->nextRow();
}

void UnitCommand::boardClean(DrawTextElm *canvas)
{
    canvas->clearBuffer();
    canvas->clearCanvas();
}

void UnitCommand::moveLeft(DrawTextElm *canvas, int n){
    canvas->moveCursor(-n);
// //qDebug() <<"Moved left";

//INSERT CODE
}
void UnitCommand::moveRight(DrawTextElm* canvas, int n){
// //qDebug() <<"Moved right " << n;
canvas->moveCursor(n);
//INSERT CODE
}

void UnitCommand::deletePreChar(DrawTextElm *canvas)
{
    canvas->crossOutLastSymbol(1);
}
void UnitCommand::deleteLeft(DrawTextElm *canvas, int n){
//INSERT CODE
    canvas->deleteFromBuffer(-n);
}
void UnitCommand::deleteRight(DrawTextElm* canvas, int n){
//INSERT CODE
    canvas->deleteFromBuffer(n);
}


void UnitCommand::erasePreChar(DrawTextElm *textElement,int n)
{
    //canvas->crossOutLastSymbol();
  //  unitType = 2;
    textElement->crossOutWithAnimation(n);
    textElement->crossText();
}
void UnitCommand::clearPreChar(DrawTextElm *canvas, int n)
{
    //canvas->crossOutLastSymbol();
   canvas->crossOutLastSymbol(n);
   canvas->crossText();
   // //qDebug() << "cross" << n;
}

void UnitCommand::update(DrawTextElm *canvas)
{
    canvas->update();
   // //qDebug() << "UPDATEEEEEEEEE";
}

void UnitCommand::pause(DrawTextElm *canvas)
{
    //QThread::msleep(unit_data.toULong()*100);
   // canvas->update();
    delay = unit_data.toULong()*100;
    canvas->crossText();
    //canvas->pause(unit_data.toULong()*1000);
}

void UnitCommand::backSlash(DrawTextElm *canvas)
{
    canvas->insertToBuffer('\\');
    canvas->moveCursor();
  //  canvas->update();
}

void UnitCommand::draw(DrawTextElm *canvas)
{
    qDebug() << "UnitCommand::draw(DrawTextElm *canvas)";
    if (Type == "ChangeColor")
    {
        changeColor(canvas);
        return;
    }
    if (Type == "Update")
    {
        update(canvas);
        return;
    }
    if (Type == "NextLine")
    {
        nextLine(canvas);
        return;
    }
    if (Type == "BoardClean")
    {
        boardClean(canvas);
        return;
    }
    if (Type == "ClearPreChar")
    {
        clearPreChar(canvas, unit_data.toInt());
        return;
    }
    if (Type == "MoveLeft")
    {
        moveLeft(canvas, unit_data.toInt());
        return;
    }
    if (Type == "MoveRight")
    {
         moveRight(canvas, unit_data.toInt());
         return;
    }
    if (Type == "ErasePreChar")
    {
        erasePreChar(canvas,unit_data.toInt());
        return;
    }
    if (Type == "Pause")
    {
        pause(canvas);
        return;
    }
    if (Type == "BackSlash")
    {
        backSlash(canvas);
        return;
    }
    if (Type=="DeleteLeft")
    {
        deleteLeft(canvas, unit_data.toInt());
        return;
    }
    if (Type=="DeleteRight")
    {
        deleteRight(canvas, unit_data.toInt());
        return;
    }
}

QString UnitCommand::getUnitCommandType()
{
    return Type;
}
