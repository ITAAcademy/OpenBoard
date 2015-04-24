#ifndef UNIT
#define UNIT

#include <QString>
#include "qmlwidget.h"

class Unit
{
private:
    int pos_x;
    int pos_y;

public:
    QString unit_data;

public:
    Unit();
    virtual ~Unit();
    virtual void draw(QmlWidget* canvas);

    void setUnitData(QString str);
    void setPosition(int x, int y);
    void setPosition(QPoint pos);

    QString getUnitData();
    int getPosition_X();
    int getPosition_Y();
};

#endif // UNIT

