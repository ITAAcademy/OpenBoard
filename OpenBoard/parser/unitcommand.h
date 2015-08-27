#ifndef UNITCOMMAND
#define UNITCOMMAND
#pragma once
#include "unit.h"



class UnitCommand : public Unit
{
private:
    QString Type;
public:
    UnitCommand();
    virtual ~UnitCommand();
    void moveLeft( DrawTextElm  *canvas, int n);
    void moveRight( DrawTextElm  *  canvas, int n);
    void setUnitCommandType(QString str);
    void changeColor(DrawTextElm * canvas);
    void nextLine(DrawTextElm * canvas);
    void boardClean(DrawTextElm * canvas);
    void deletePreChar(DrawTextElm * canvas);
    void deleteLeft(DrawTextElm * canvas, int n);
    void deleteRight(DrawTextElm * canvas, int n);
    void erasePreChar(DrawTextElm * canvas,int n);
    void pause(DrawTextElm * canvas);
    void backSlash(DrawTextElm * canvas);
    void draw( DrawTextElm  * canvas);
    void clearPreChar(DrawTextElm * canvas, int n);
    void update(DrawTextElm * canvas);
    QString getUnitCommandType();
};

#endif // UNITCOMMAND

