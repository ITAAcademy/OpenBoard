#ifndef PARSER
#define PARSER

#include <QLinkedList>
#include <QString>

#include "unit.h"
#include "unitsumbol.h"
#include "unitcommand.h"

class Parser
{
public:
    Parser();
    virtual ~Parser();

    int ParsingLine(QLinkedList<Unit*>& list, QString& str);
};

#endif // PARSER

