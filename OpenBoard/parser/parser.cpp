#include "parser.h"


Parser::Parser()
{

}

Parser::~Parser()
{

}
QString Parser::commands[]   ={
    "\\n",
    "\\a",
    "\\-",
    "\\<",
    "\\>",
    "\\ml",
    "\\mr",
    "\\dl",
    "\\dr",
    "\\#",
     "\\p",
    "\\c"
};
int Parser::COMMANDS_COUNT = 12;
int Parser::MAX_COMMAND_LENGTH = 3;
int Parser::ParsingLine(QList<Unit*> &list, const QString &str)
{
    list.clear();
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
        /*if(pars_line == (QString)"\n")
        {
            QStringRef section(&str, i + 1, 2);
            if((section.at(0) == '\\' || section.at(0) == 'n') && section != "\\n")
                str.remove(i, 2);
            else if(section != "\\n" )
            {
                QStringRef section(&str, i + 2, 2);
                if(section == "\\n")
                    str.remove(i + 2, 2);
                str.insert(i + 1, "\\n");
            }
            state = -1;
            continue;
        }*/
        if(pars_line[0] == '\n')
        {
            UnitCommand* command = new UnitCommand();
            command->setUnitCommandType("NextLine");
            list.push_back(command);
            state = -1;
            continue;
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
                command->setUnitCommandType("ClearPreChar");
                QRegExp exp("[0-9]");
                pars_line.clear();
                int count = 0;
                if(exp.exactMatch((QString)str[i+2]))
                {
                    while(exp.exactMatch((QString)str[i+2]) && ++count < 4)
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
                i += 1;
                continue;
            }
            if(pars_line == (QString)"\\<")
            {
                    UnitCommand* command = new UnitCommand();
                    command->setUnitCommandType("ErasePreChar");

                    QRegExp exp("[0-9]");
                    pars_line.clear();
                    int count = 0;
                    if(exp.exactMatch((QString)str[i+2]))
                    {
                        while(exp.exactMatch((QString)str[i+2]) && ++count < 4)
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
                    qDebug()<<"Pars line:"<<pars_line;
                    list.push_back(command);
                    state = -1;
                    i += 1;
                    continue;

               /* UnitCommand* command = new UnitCommand();
                command->setUnitCommandType("ErasePreChar");
                list.push_back(command);
                state = -1;
                i++;
                continue;*/
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
                int count = 0;
                if(exp.exactMatch((QString)str[i+2]))
                {
                    while(exp.exactMatch((QString)str[i+2]) && count++ < 2)
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

                QRegExp exp("[0-9a-f]");
                pars_line.clear();
                pars_line += "#";
                int tmp = 0;
                while(exp.exactMatch((QString)str[i+2]) &&  tmp < 6 )
                {
                    pars_line += str[i+2];
                    i++; tmp++;
                }
                if(tmp < 6)
                {
                    state = i;
                    qDebug() << "color error";
                    break;
                }

                command->setUnitData(pars_line);
                list.push_back(command);
                state = -1;
                i++;
                continue;
            }
            /*else
            {
                state = i;
                break;
            }*/
              pars_line += str[i+2];
              if (pars_line == (QString)"\\dl")
              {
                  UnitCommand* command = new UnitCommand();
                  command->setUnitCommandType("DeleteLeft");

                  QRegExp exp("[0-9]");
                  pars_line.clear();
                  int count = 0;
                  if(exp.exactMatch((QString)str[i+3]))
                  {
                      while(exp.exactMatch((QString)str[i+3]) && count++ < 3)
                      {
                          pars_line += str[i+3];
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
                  i += 2;
                  continue;

              }
             // pars_line += str[i+2];
              if (pars_line == (QString)"\\dr")
              {
                  UnitCommand* command = new UnitCommand();
                  command->setUnitCommandType("DeleteRight");

                  QRegExp exp("[0-9]");
                  pars_line.clear();
                  int count = 0;
                  if(exp.exactMatch((QString)str[i+3]))
                  {
                      while(exp.exactMatch((QString)str[i+3]) && count++ < 3)
                      {
                          pars_line += str[i+3];
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
                  i += 2;

                  continue;

              }

              if (pars_line == (QString)"\\ml")
              {
                  UnitCommand* command = new UnitCommand();
                  command->setUnitCommandType("MoveLeft");

                  QRegExp exp("[0-9]");
                  pars_line.clear();
                  int count = 0;
                  if(exp.exactMatch((QString)str[i+3]))
                  {
                      while(exp.exactMatch((QString)str[i+3]) && count++ < 3)
                      {
                          pars_line += str[i+3];
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
                  i += 2;
                  continue;

              }
              if (pars_line == (QString)"\\mr")
              {
                  UnitCommand* command = new UnitCommand();
                  command->setUnitCommandType("MoveRight");

                  QRegExp exp("[0-9]");
                  pars_line.clear();
                  int count = 0;
                  if(exp.exactMatch((QString)str[i+3]))
                  {
                      while(exp.exactMatch((QString)str[i+3]) && count++ < 3)
                      {
                          pars_line += str[i+3];
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
                  i += 2;
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
