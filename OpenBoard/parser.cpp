#include "parser.h"


Parser::Parser()
{

}

Parser::~Parser()
{

}

int Parser::ParsingLine(QLinkedList<Unit*> &list, QString& str)
{
    QString pars_line;
    int state = -1;

    for(int i = 0; i < str.length(); i++)
    {
        if((QString)str[i] == (QString)"\0" || i >= str.length())
        {
            state = -1;
            break;
        }
        else
        {
            pars_line.clear();
            pars_line = str[i];
        }

        if(pars_line == (QString)"\\")
        {
            pars_line += str[i+1];

            if(pars_line == (QString)"\\n")
            {
                UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("NextLine");
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            if(pars_line == (QString)"\\a")
            {
                UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("BoardClean");
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            if(pars_line == (QString)"\\-")
            {
                UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("DeletePreChar");
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            if(pars_line == (QString)"\\<")
            {
                UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("ErasePreChar");
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            if(pars_line == (QString)"\\\\")
            {
                UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("BackSlash");
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            if(pars_line == (QString)"\\p")
            {
                UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("Pause");

                QRegExp exp("[0-9]");
                pars_line.clear();

                if(exp.exactMatch((QString)str[i+2]))
                {
                    while(exp.exactMatch((QString)str[i+2]))
                    {
                        pars_line += str[i+2];
                        i++;
                    }
                }
                else
                {
                    state = i;
                    break;
                }

                command->setUnitData(pars_line);
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            if(pars_line == (QString)"\\c")
            {
                UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("ChangeColor");

                QRegExp exp("[0-9A-Z]");
                pars_line.clear();
                int tmp = 1;

                if(exp.exactMatch((QString)str[i+2]))
                {
                    while(exp.exactMatch((QString)str[i+2]) && tmp <= 6)
                    {
                        pars_line += str[i+2];
                        i++; tmp++;
                    }
                }
                else
                {
                    state = i;
                    break;
                }

                command->setUnitData(pars_line);
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            else
            {
                state = i;
                break;
            }
        }
        else
        {
            UnitSumbol *sumbol = new UnitSumbol();
            sumbol->setUnitData(pars_line);
            list.push_back(sumbol);
            state = -1;
        }
    }
    return state;
}
