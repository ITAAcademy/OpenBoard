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
    static QString commands [];
      static int  COMMANDS_COUNT;
    static int MAX_COMMAND_LENGTH;

    Parser();
    virtual ~Parser();

    static int ParsingLine(QList<Unit*>& list, QString &str);
};

#endif // PARSER

