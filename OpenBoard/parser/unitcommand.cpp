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

void UnitCommand::changeColor(QmlWidget *canvas)
{
    canvas->setFillColor(QColor(unit_data));
}

void UnitCommand::nextLine(QmlWidget *canvas)
{
    canvas->nextRow();
}

void UnitCommand::boardClean(QmlWidget *canvas)
{
    canvas->clearCanvas();
}

void UnitCommand::deletePreChar(QmlWidget *canvas)
{
    canvas->crossOutLastSymbol();
}

void UnitCommand::erasePreChar(QmlWidget *canvas)
{
    //canvas->crossOutLastSymbol();
    canvas->crossOutWithAnimation();
}

void UnitCommand::pause(QmlWidget *canvas)
{
    //QThread::msleep(unit_data.toULong()*100);
    canvas->update();
    canvas->pause(unit_data.toULong()*100);
}

void UnitCommand::backSlash(QmlWidget *canvas)
{
    this->setPosition(canvas->drawWrapText("\\"));
}

void UnitCommand::draw(QmlWidget *canvas)
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
    if (Type == "DeletePreChar")
    {
        deletePreChar(canvas);
        return;
    }
    if (Type == "ErasePreChar")
    {
        erasePreChar(canvas);
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
}

QString UnitCommand::getUnitCommandType()
{
    return Type;
}
