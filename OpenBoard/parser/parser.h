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

    static int ParsingLine(QList<Unit*>& list, QString &str,quint64& timeSpendToDraw,int delay = 0);
   static quint64 processTimeOfUnits(QList<Unit *> list,int delayMS=0);
};

#endif // PARSER

