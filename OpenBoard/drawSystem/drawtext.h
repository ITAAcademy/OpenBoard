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
    int textCursor = 0;
    quint64 drawTime;
    int globalPauseLifeTime = 0;
public:
    int curentPauseValue = 0;
    explicit DrawTextElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawTextElm();
    void draw();
    void setLifeTime(int value);
    QList<Unit *> unitList() const;
    void setUnitList(const QList<Unit *> &unitList);
    QString getUnParsestring() const;
    void setUnParsestring(const QString &valueUnParss, const QString &valueLogger);

    QString getLoggerText() const;
    void setLoggerText(const QString &value);

    quint64 getDrawTime() const;

    int getTextCursor() const;
    void setTextCursor(const int &value);

private:
    void setTickTime(int value);
    bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
};

#endif // DrawTextElm_H
