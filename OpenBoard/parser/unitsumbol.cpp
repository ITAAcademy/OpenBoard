#include "unitsumbol.h"

UnitSumbol::UnitSumbol() : Unit()
{
    Size = 0;
    Color = "";
    Font = "";
}

UnitSumbol::~UnitSumbol()
{

}

void UnitSumbol::draw(QmlWidget *canvas)
{
    canvas->drawWrapText(unit_data);
}

void UnitSumbol::setUnitSumbolColor(QString color)
{
    Color = color;
}

void UnitSumbol::setUnitSumbolSize(int size)
{
    Size = size;
}

void UnitSumbol::setUnitSumbolType(QString str)
{
    Font = str;
}

QString UnitSumbol::getUnitSumbolColor()
{
    return Color;
}

QString UnitSumbol::getUnitSumbolType()
{
    return Font;
}

int UnitSumbol::getUnitSumbolSize()
{
    return Size;
}