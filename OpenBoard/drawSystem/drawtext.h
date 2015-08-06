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
    Parser myParser;
    quint64 drawTime;
public:
    explicit DrawTextElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawTextElm();
    void draw();
    void setLifeTime(int value);
    QList<Unit *> unitList() const;
    QString unParsestring;
    void setUnitList(const QList<Unit *> &unitList);
    QString getUnParsestring() const;
    void setUnParsestring(const QString &value);

private:
    void setTickTime(int value);
    bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
};

#endif // DrawTextElm_H
