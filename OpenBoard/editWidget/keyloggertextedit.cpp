#include "keyloggertextedit.h"
#include "qdebug.h"
#include <QKeyEvent>
#include <QTextEdit>
#include <qmath.h>
#include "parser\parser.h"
KeyloggerTE::KeyloggerTE(MyTextEdit *destination,QWidget* parent){
this->destination=destination;
    this->setParent(parent);
         //connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(onCursorChanged()));
}
void KeyloggerTE::keyPressEvent(QKeyEvent *event){
    event->accept();

    int keyCode = event->key();
    QString keyChar(event->text());
   // QTextCursor
           int localCursorPosition = textCursor().position();
           QString localText = toPlainText();
           int localCursorPositionInBlock = textCursor().positionInBlock();
           int localCursorBlockNumber = textCursor().blockNumber();
           int localCursorSelectionStart=textCursor().selectionStart();
           int localCursorSelectionEnd=textCursor().selectionEnd();
    QTextEdit::keyPressEvent(event);



            QString textInField = destination->toPlainText();
             QStringList stringsInCommandTextEdit = toPlainText().split('\n');
    //Якщо буква то просто вставляєм її в текст
             if(event->modifiers() & Qt::ControlModifier)
             {
                 if (event->matches(QKeySequence::Paste))
                     textInField += QApplication::clipboard()->text();
             }
    else
    switch(keyCode){
    case Qt::Key_Up:
        qDebug() << "on_Key_UP";
         if (textCursor().position()!=previousCursorPosition)
         {
           int delta =   abs(localCursorPosition - textCursor().position());
            textInField +=QString("\\ml%1").arg(delta, 3, 10, QChar('0'));
         }
        break;
    case Qt::Key_Down:
        qDebug() << "on_Key_DOWN";
        if (textCursor().position()!=previousCursorPosition)
        {
          int delta =    abs(localCursorPosition - textCursor().position());
           textInField +=QString("\\mr%1").arg(delta, 3, 10, QChar('0'));
        }
        break;
    case Qt::Key_Left:
        qDebug() << "on_KEY_LEFT";
           if (textCursor().position()!=previousCursorPosition)
         textInField +="\\ml001";
        break;
    case Qt::Key_Right:
        qDebug() << "on_KEY_RIGHT";
        if (textCursor().position()!=previousCursorPosition)
        textInField +="\\mr001";
        break;
    case Qt::Key_Home:
        if (localCursorPositionInBlock!=0)
        {
            int delta = localCursorPositionInBlock;
             textInField +=QString("\\ml%1").arg(delta, 3, 10, QChar('0'));
        }
        break;
    case Qt::Key_End:

        if (localCursorPositionInBlock!=stringsInCommandTextEdit[localCursorBlockNumber].length())
        {
            int delta = stringsInCommandTextEdit[localCursorBlockNumber].length()-localCursorPositionInBlock;
             textInField +=QString("\\mr%1").arg(delta, 3, 10, QChar('0'));
        }
        break;
    case Qt::Key_Delete:
        if (localCursorSelectionEnd-localCursorSelectionStart!=0)
        {
            int delta = localCursorSelectionEnd-localCursorSelectionStart;
            if (localCursorPosition==localCursorSelectionEnd)
            textInField +=QString("\\dl%1").arg(delta, 3, 10, QChar('0'));
            else textInField +=QString("\\dr%1").arg(delta, 3, 10, QChar('0'));
        }
        else if (localCursorPosition<localText.length())
        {
            textInField +="\\dr001";
        }
        qDebug()<<"textCursor().position():"<<textCursor().position();
        qDebug()<<"previousCursorPosition:"<<previousCursorPosition;
        qDebug()<<"localCursorPosition:"<<localCursorPosition;
        break;
    case Qt::Key_Backspace:
        qDebug() << "on_KEY_BACKSPACE";
qDebug() << "cursorPosition:" <<localCursorPosition;
qDebug() << "selection start:" << localCursorSelectionStart;
qDebug() << "selection end:" << localCursorSelectionEnd;
if (localCursorSelectionEnd-localCursorSelectionStart==0)
           {if (textCursor().position()!=previousCursorPosition)
        textInField +="\\dl001";
            }
else {
    int delta = localCursorSelectionEnd-localCursorSelectionStart;
    if (localCursorPosition==localCursorSelectionEnd)
    textInField +=QString("\\dl%1").arg(delta, 3, 10, QChar('0'));
    else textInField +=QString("\\dr%1").arg(delta, 3, 10, QChar('0'));
}
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        qDebug() << "on_KEY_ENTER";
        textInField +="\\n";
        break;
     case Qt::Key_Backslash:
        lastSlashPosInDestination = textInField.length();
        qDebug() << "Last slash pos:"<<lastSlashPosInDestination;
        textInField +="\\\\";
        break;
    default:

        if(keyChar.length()>0) {
            textInField +=keyChar;
        }
        break;
    }
     //if (!(event->matches(QKeySequence::Copy)))//|| event->matches(QKeySequence::Paste)))


     if (lastSlashPosInDestination!=-1){
         textAfterBackSlash= textInField.mid(lastSlashPosInDestination+1);
         if (textAfterBackSlash.length()<=Parser::MAX_COMMAND_LENGTH){
        bool isCommandAfterSlash=false;
         qDebug() << "TEXT AFTER SLASH:"<<textAfterBackSlash;
        for (int i =0;i<Parser::COMMANDS_COUNT;i++)
         if (textAfterBackSlash==Parser::commands[i]){
              qDebug() << "Command "<<Parser::commands[i] << "after slash detected";
                 isCommandAfterSlash=true;
         }

        if (isCommandAfterSlash){
           textInField = textInField.remove(lastSlashPosInDestination,1);

        qDebug() << "SLASH:"<<textAfterBackSlash;
        qDebug() << "SLASH POS:"<<lastSlashPosInDestination;
        lastSlashPosInDestination=-1;
        textAfterBackSlash.clear();
        }
         }
     }
      destination->setPlainText(textInField);
     previousCursorPosition=textCursor().position();
}
void KeyloggerTE::focusInEvent( QFocusEvent * ev )
{
    emit KeyloggerTE::setFocus() ;
    QTextEdit::focusInEvent(ev);
}

void KeyloggerTE::mousePressEvent(QMouseEvent *eventPress){
  QTextEdit::mousePressEvent(eventPress);
    int delta = textCursor().position() - previousCursorPosition;
    previousCursorPosition=textCursor().position();

      QString textInField = destination->toPlainText();
      if (delta>0)
      textInField +=QString("\\mr%1").arg(delta, 3, 10, QChar('0'));
      else if (delta<0)
      textInField +=QString("\\ml%1").arg(-delta, 3, 10, QChar('0'));
     destination->setPlainText(textInField);
//qDebug() << "cursor changed";
}
void KeyloggerTE::mouseReleaseEvent(QMouseEvent *eventPress){
  QTextEdit::mouseReleaseEvent(eventPress);
    int delta = textCursor().position() - previousCursorPosition;
    previousCursorPosition=textCursor().position();

      QString textInField = destination->toPlainText();
      if (delta>0)
      textInField +=QString("\\mr%1").arg(delta, 3, 10, QChar('0'));
      else if (delta<0)
      textInField +=QString("\\ml%1").arg(-delta, 3, 10, QChar('0'));
     destination->setPlainText(textInField);
//qDebug() << "cursor changed";
}

