#ifndef UNITSUMBOL
#define UNITSUMBOL

#include <QString>
#include "unit.h"

class UnitSumbol : Unit
{
private:
    int Size;
    QString Type;
    QString Color;

public:
    UnitSumbol();
    virtual ~UnitSumbol();

    void setUnitSumbolType(QString str);
    void setUnitSumbolSize(int size);
    void setUnitSumbolColor(QString color);

    QString getUnitSumbolType();
    QString getUnitSumbolColor();
    int getUnitSumbolSize();

};

#endif // UNITSUMBOL

