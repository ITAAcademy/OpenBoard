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
    void moveLeft(OGLWidget* canvas, int n);
    void moveRight(OGLWidget* canvas, int n);
    void setUnitCommandType(QString str);
    void changeColor(OGLWidget* canvas);
    void nextLine(OGLWidget* canvas);
    void boardClean(OGLWidget* canvas);
    void deletePreChar(OGLWidget* canvas);
    void deleteLeft(OGLWidget* canvas, int n);
    void deleteRight(OGLWidget* canvas, int n);
    void erasePreChar(OGLWidget* canvas,int n);
    void pause(OGLWidget* canvas);
    void backSlash(OGLWidget* canvas);
    void draw(OGLWidget *canvas);
    void clearPreChar(OGLWidget* canvas, int n);
    void update(OGLWidget* canvas);
    QString getUnitCommandType();
};

#endif // UNITCOMMAND

