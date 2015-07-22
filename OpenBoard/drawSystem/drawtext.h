#ifndef DrawTextElm_H
#define DrawTextElm_H
#pragma once
#include <QObject>
#include "drawelement.h"
#include "../parser/parser.h"

class DrawTextElm : public DrawElement
{
    Q_OBJECT

    QList <Unit*>mUnitList;
public:
    explicit DrawTextElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawTextElm();
    void draw();
    void setLifeTime(int value);
    QList<Unit *> unitList() const;
    void setUnitList(const QList<Unit *> &unitList);
private:
    void setTickTime(int value);
};

#endif // DrawTextElm_H
