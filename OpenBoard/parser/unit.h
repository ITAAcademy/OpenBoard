#ifndef UNIT
#define UNIT
#pragma once
#include <QString>
#include <QtConcurrent/QtConcurrent>
#include "openglwidget.h"

class Unit
{
private:
    int pos_x;
    int pos_y;

public:
    QString unit_data;
    int unitType = 0; //
    int delay = -1;

public:
    Unit();
    virtual ~Unit();
    virtual void draw(OGLWidget* canvas);

    void setUnitData(QString str);
    void setPosition(int x, int y);
    void setPosition(QPoint pos);

    QString getUnitData();
    int getPosition_X();
    int getPosition_Y();
};

#endif // UNIT

