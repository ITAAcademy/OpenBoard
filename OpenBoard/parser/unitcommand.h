#ifndef UNITCOMMAND
#define UNITCOMMAND

#include "unit.h"

class UnitCommand : public Unit
{
private:
    QString Type;
public:
    UnitCommand();
    virtual ~UnitCommand();
    void moveLeft(QmlWidget* canvas, int n);
    void moveRight(QmlWidget* canvas, int n);
    void setUnitCommandType(QString str);
    void changeColor(QmlWidget* canvas);
    void nextLine(QmlWidget* canvas);
    void boardClean(QmlWidget* canvas);
    void deletePreChar(QmlWidget* canvas);
    void deleteLeft(QmlWidget* canvas, int n);
    void deleteRight(QmlWidget* canvas, int n);
    void erasePreChar(QmlWidget* canvas);
    void pause(QmlWidget* canvas);
    void backSlash(QmlWidget* canvas);
    void draw(QmlWidget *canvas);
    void clearPreChar(QmlWidget* canvas);
    QString getUnitCommandType();
};

#endif // UNITCOMMAND

