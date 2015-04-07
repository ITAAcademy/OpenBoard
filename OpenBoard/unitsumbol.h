#ifndef UNITSUMBOL
#define UNITSUMBOL

#include <QString>
#include "unit.h"

class UnitSumbol : public Unit
{
private:
    int Size;
    QString Font;
    QString Color;

public:
    UnitSumbol();
    virtual ~UnitSumbol();
    virtual void draw(QmlWidget* canvas);

    void setUnitSumbolType(QString str);
    void setUnitSumbolSize(int size);
    void setUnitSumbolColor(QString color);

    QString getUnitSumbolType();
    QString getUnitSumbolColor();
    int getUnitSumbolSize();

};

#endif // UNITSUMBOL

