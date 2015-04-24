#ifndef OPENBOARDTEXT_H
#define OPENBOARDTEXT_H
#include <QVector>
#include <QString>
#include "openboardunit.h"

class OpenBoardText
{
private:
    QVector<OpenBoardUnit> internalText;
public:
    OpenBoardText();
    ~OpenBoardText();
    bool parse(QString*);
};

#endif // OPENBOARDTEXT_H
