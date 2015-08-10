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
    QString loggerText;
    QString unParsestring;
    Parser myParser;
    quint64 drawTime;
public:
    explicit DrawTextElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawTextElm();
    void draw();
    void setLifeTime(int value);
    QList<Unit *> unitList() const;
    void setUnitList(const QList<Unit *> &unitList);
    QString getUnParsestring() const;
    void setUnParsestring(const QString &valueUnParss, const QString &valueLogger, bool needToSaveLifeTime = false);

private:
    void setTickTime(int value);
    bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
};

#endif // DrawTextElm_H
