#include "unit.h"

Unit::Unit()
{
    unit_data = "";
    pos_x = 0;
    pos_y = 0;
}

Unit::~Unit()
{

}

void Unit::draw(QmlWidget *canvas)
{
}

void Unit::setUnitData(QString str)
{
    unit_data = str;
}

void Unit::setPosition(int x, int y)
{
    pos_x = x;
    pos_y = y;
}

void Unit::setPosition(QPoint pos)
{
    pos_x = pos.x();
    pos_y = pos.y();
}

QString Unit::getUnitData()
{
    return unit_data;
}

int Unit::getPosition_X()
{
    return pos_x;
}

int Unit::getPosition_Y()
{
    return pos_y;
}
