#ifndef UNIT
#define UNIT

#include <QString>

class Unit
{
private:
    int pos_x;
    int pos_y;
    QString unit_data;

public:
    Unit();
    virtual ~Unit();

    void setUnitData(QString str);
    void setPosition(int x, int y);

    QString getUnitData();
    int getPosition_X();
    int getPosition_Y();
};

#endif // UNIT

