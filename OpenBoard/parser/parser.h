#ifndef PARSER
#define PARSER

#include <QList>
#include <QString>
#include <QStringRef>

#include "unit.h"
#include "unitsumbol.h"
#include "unitcommand.h"

class Parser
{
public:
    Parser();
    virtual ~Parser();

    int ParsingLine(QList<Unit*>& list, QString& str);
};

#endif // PARSER

