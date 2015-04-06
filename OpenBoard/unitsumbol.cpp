#include "unitsumbol.h"

UnitSumbol::UnitSumbol() : Unit()
{
    Size = 0;
    Color = "";
    Type = "";
}

UnitSumbol::~UnitSumbol()
{

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
    Type = str;
}

QString UnitSumbol::getUnitSumbolColor()
{
    return Color;
}

QString UnitSumbol::getUnitSumbolType()
{
    return Type;
}

int UnitSumbol::getUnitSumbolSize()
{
    return Size;
}
