#include "unitcommand.h"



UnitCommand::UnitCommand() : Unit()
{
    Type = "";
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

void UnitCommand::changeColor(OGLWidget *canvas)
{
   // canvas->setFillColor(QColor(unit_data));
    qDebug() << "void UnitCommand::changeColor(OGLWidget *canvas)";
    ColorMarker marker;
    marker.startIndex=canvas->getCursorIndex();
    marker.value=unit_data;
    canvas->colors.push_back(marker);
    qSort(canvas->colors.begin(),canvas->colors.end(),isLower);
}

void UnitCommand::nextLine(OGLWidget *canvas)
{
    canvas->nextRow();
}

void UnitCommand::boardClean(OGLWidget *canvas)
{
    canvas->clearBuffer();
    canvas->clearCanvas();
}

void UnitCommand::moveLeft(OGLWidget *canvas, int n){
    canvas->moveCursor(-n);
qDebug() <<"Moved left";

//INSERT CODE
}
void UnitCommand::moveRight(OGLWidget* canvas, int n){
qDebug() <<"Moved right " << n;
canvas->moveCursor(n);
//INSERT CODE
}

void UnitCommand::deletePreChar(OGLWidget *canvas)
{
    canvas->crossOutLastSymbol();
}
void UnitCommand::deleteLeft(OGLWidget *canvas, int n){
//INSERT CODE
    canvas->deleteFromBuffer(-n);
}
void UnitCommand::deleteRight(OGLWidget* canvas, int n){
//INSERT CODE
    canvas->deleteFromBuffer(n);
}


void UnitCommand::erasePreChar(OGLWidget *canvas,int n)
{
    //canvas->crossOutLastSymbol();
    canvas->crossOutWithAnimation(n);
}
void UnitCommand::clearPreChar(OGLWidget *canvas, int n)
{
    //canvas->crossOutLastSymbol();
   canvas->crossOutLastSymbol(n);
   qDebug() << "cross" << n;
}

void UnitCommand::pause(OGLWidget *canvas)
{
    //QThread::msleep(unit_data.toULong()*100);
    canvas->update();
    canvas->pause(unit_data.toULong()*100);
}

void UnitCommand::backSlash(OGLWidget *canvas)
{
    canvas->insertToBuffer('\\');
    canvas->moveCursor();
    canvas->update();
}

void UnitCommand::draw(OGLWidget *canvas)
{
    if (Type == "ChangeColor")
    {
        changeColor(canvas);
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
