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
     t_cursor = this->textCursor();
    changebuf.cursor = 0;
    changebuf.cymbol = "";
    changebuf.changeSize =0;

     connect(this, SIGNAL(textChanged()),this, SLOT(tabTo4Spaces()));
     setContextMenuPolicy(Qt::NoContextMenu);
}
void KeyloggerTE::saveChanges(int sizeOfChange){

   changebuf.cursor = this->textCursor().position();
   changebuf.cymbol = this->toPlainText();
   changebuf.changeSize = sizeOfChange;
    if (undo_changes.length()>0){
        CursorSymbolExtended prevChange =   undo_changes.pop();
      prevChange.changeSize=sizeOfChange;
      undo_changes.push(prevChange);
    }
   undo_changes.push(changebuf);
}

void KeyloggerTE::undo()
{
    // qDebug() <<"changes before:"<<undo_changes.length();
    if (undo_changes.size() >0)
    {
        CursorSymbolExtended backup;
        backup.cursor = this->textCursor().position();
        backup.cymbol = this->toPlainText();
        redo_changes.push_back(backup);

       CursorSymbolExtended change ;

       int changesSizePrev = -1;
 if (changesDetected && undo_changes.size()>1){

   changesSizePrev = undo_changes.pop().changeSize;
     changesDetected=false;
 }
      change = undo_changes.pop();
     // curs.setPosition(change.cursor);
      this->clear();

       this->setPlainText(change.cymbol);
      t_cursor.setPosition(change.cursor);
        this->setTextCursor(t_cursor);
      //My code
      QString destText = destination->toPlainText();
             destText.chop(change.changeSize);
             destination->setPlainText(destText);
             QTextCursor tc = destination->textCursor();
             tc.setPosition(destText.length());
             destination->setTextCursor(tc);
             if (changesDetected && undo_changes.length()==0)this->clear();
    }
    else {

        this->clear();
        destination->clear();
    }
    // qDebug() <<"changes after:"<<undo_changes.length();

}

void KeyloggerTE::redo()
{

if (redo_changes.size() >0)
{

   CursorSymbolExtended backup;
   backup.cursor = this->textCursor().position();
   backup.cymbol = this->toPlainText();
   undo_changes.push_back(backup);

   CursorSymbolExtended change ;
   change = redo_changes.pop();
   this->setPlainText(change.cymbol);
   t_cursor.setPosition(change.cursor);
   this->setTextCursor(t_cursor);

}
}

void KeyloggerTE::keyPressEvent(QKeyEvent *event){
    bool needToSaveForUndo = true;
    event->accept();
    if (redo_changes.size()>0)
    {
    CursorSymbolExtended change = redo_changes.pop();
    redo_changes.push(change);
    }
    int keyCode = event->key();
    quint32 scanCode = event->nativeScanCode();
    QString keyChar(event->text());
   // QTextCursor
           int localCursorPosition = textCursor().position();
           QString localText = toPlainText();
           int localCursorPositionInBlock = textCursor().positionInBlock();
           int localCursorBlockNumber = textCursor().blockNumber();
           int localCursorSelectionStart=textCursor().selectionStart();
           int localCursorSelectionEnd=textCursor().selectionEnd();

            QString textInFieldBeforePress=destination->toPlainText();
            // qDebug() << "nativeScanCode:"<<scanCode;
            if (event->modifiers() & Qt::ControlModifier && scanCode==SCAN_KEY_Z )
            {
                  if (keyCode==Qt::Key_Z){
               // qDebug() <<"UNDO";
                undo();
                changesDetected=false;
                return;
                  }
                  else
                  {
                      QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Z,Qt::ControlModifier);
                      QCoreApplication::postEvent (this, event);
                  }
               //if (!changesSize.empty())textInFieldBeforePress.chop(changesSize.pop());
                //if(undo_changes.size()>0) setPlainText(undo_changes.pop().cymbol);

            }
        //    else
    QPlainTextEdit::keyPressEvent(event);

            QString textInField = destination->toPlainText();

             QStringList stringsInCommandTextEdit = toPlainText().split('\n');
             if(event->modifiers() & Qt::ControlModifier)
             {

                 if (scanCode==SCAN_KEY_V)
                 {
                     if (keyCode!=Qt::Key_V){
                         QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_V,Qt::ControlModifier);
                         QCoreApplication::postEvent (this, event);
                     }
                     textInField += QApplication::clipboard()->text();
                    // insertPlainText(QApplication::clipboard()->text());




                 }
                 else
                 if (scanCode==SCAN_KEY_X)
                 {
                     if (keyCode!=Qt::Key_X)
                     {
                         QKeyEvent *e = new QKeyEvent ( QEvent::KeyPress, Qt::Key_X,Qt::ControlModifier);
                         QCoreApplication::postEvent (this, e);
                     }
                     int delta = localCursorSelectionEnd-localCursorSelectionStart;
                     if (localCursorPosition==localCursorSelectionEnd)
                     textInField +=QString("\\dl%1").arg(delta, 3, 10, QChar('0'));
                     else textInField +=QString("\\dr%1").arg(delta, 3, 10, QChar('0'));

                 }
                 else
                 if (scanCode==SCAN_KEY_A)
                 {
                     if (keyCode!=Qt::Key_A)
                     {
                         QKeyEvent *e1 = new QKeyEvent ( QEvent::KeyRelease, Qt::Key_A,Qt::ControlModifier);
                         QCoreApplication::postEvent (this, e1);

                         QKeyEvent *e = new QKeyEvent ( QEvent::KeyPress, Qt::Key_A,Qt::ControlModifier);
                         QCoreApplication::postEvent (this, e);
                     }

                 }
                 else
                 if (scanCode==SCAN_KEY_C)
                 {
                     if (keyCode!=Qt::Key_C)
                     {
                         QKeyEvent *e = new QKeyEvent ( QEvent::KeyPress, Qt::Key_C,Qt::ControlModifier);
                         QCoreApplication::postEvent (this, e);
                     }

                 }
                 else //if (event->matches(QKeySequence::Undo))
                     needToSaveForUndo=false;
                // return;

             }
    else
    switch(keyCode){
    case Qt::Key_Up:
        // qDebug() << "on_Key_UP";
         if (textCursor().position()!=previousCursorPosition)
         {
           int delta =   abs(localCursorPosition - textCursor().position());
            textInField +=QString("\\ml%1").arg(delta, 3, 10, QChar('0'));
         }
        break;
    case Qt::Key_Down:
        // qDebug() << "on_Key_DOWN";
        if (textCursor().position()!=previousCursorPosition)
        {
          int delta =    abs(localCursorPosition - textCursor().position());
           textInField +=QString("\\mr%1").arg(delta, 3, 10, QChar('0'));
        }
        break;
    case Qt::Key_Left:
        // qDebug() << "on_KEY_LEFT";
           if (textCursor().position()!=previousCursorPosition)
         textInField +="\\ml001";
        break;
    case Qt::Key_Right:
        // qDebug() << "on_KEY_RIGHT";
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
        // qDebug()<<"textCursor().position():"<<textCursor().position();
        // qDebug()<<"previousCursorPosition:"<<previousCursorPosition;
        // qDebug()<<"localCursorPosition:"<<localCursorPosition;
        break;
    case Qt::Key_Backspace:
        // qDebug() << "on_KEY_BACKSPACE";
// qDebug() << "cursorPosition:" <<localCursorPosition;
// qDebug() << "selection start:" << localCursorSelectionStart;
// qDebug() << "selection end:" << localCursorSelectionEnd;
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
        // qDebug() << "on_KEY_ENTER";
        textInField +="\n";
        break;
     case Qt::Key_Backslash:
        lastSlashPosInDestination = textInField.length();
        // qDebug() << "Last slash pos:"<<lastSlashPosInDestination;
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
         // qDebug() << "TEXT AFTER SLASH:"<<textAfterBackSlash;
        for (int i =0;i<Parser::COMMANDS_COUNT;i++)
         if (textAfterBackSlash==Parser::commands[i]){
              // qDebug() << "Command "<<Parser::commands[i] << "after slash detected";
                 isCommandAfterSlash=true;
         }

        if (isCommandAfterSlash){
           textInField = textInField.remove(lastSlashPosInDestination,1);

        // qDebug() << "SLASH:"<<textAfterBackSlash;
        // qDebug() << "SLASH POS:"<<lastSlashPosInDestination;
        lastSlashPosInDestination=-1;
        textAfterBackSlash.clear();
        }
         }
     }
     int destinationLen = destination->toPlainText().length();
     int textInFieldLen = textInField.length();
     if(textInField.length() != 0)
     {
        destination->setPlainText(textInField);
     }
      //changesSize.push(textInField.length());
     previousCursorPosition=textCursor().position();

     if (needToSaveForUndo){
         changesDetected=true;

         int sizeOfChanges = textInFieldLen-destinationLen;
         // qDebug() << "Save changes ,size:"<<sizeOfChanges;
         saveChanges(sizeOfChanges);
     }
}
void KeyloggerTE::focusInEvent( QFocusEvent * ev )
{
    emit KeyloggerTE::setFocus() ;
    QPlainTextEdit::focusInEvent(ev);
}

void KeyloggerTE::mousePressEvent(QMouseEvent *eventPress){
  QPlainTextEdit::mousePressEvent(eventPress);
    int delta = textCursor().position() - previousCursorPosition;
    previousCursorPosition=textCursor().position();

      QString textInField = destination->toPlainText();
      if (delta>0)
      textInField +=QString("\\mr%1").arg(delta, 3, 10, QChar('0'));
      else if (delta<0)
      textInField +=QString("\\ml%1").arg(-delta, 3, 10, QChar('0'));
      int destinationLen = destination->toPlainText().length();
      int textInFieldLen = textInField.length();
      if(textInField.length() != 0)
     destination->setPlainText(textInField);
     int sizeOfChanges = textInFieldLen-destinationLen;
     if (sizeOfChanges>0)
     {
     saveChanges(sizeOfChanges);//TODO
              changesDetected=true;
     }
//// qDebug() << "cursor changed";
}
void KeyloggerTE::mouseReleaseEvent(QMouseEvent *eventPress){
    QPlainTextEdit::mouseReleaseEvent(eventPress);
    int delta = textCursor().position() - previousCursorPosition;
    previousCursorPosition=textCursor().position();

      QString textInField = destination->toPlainText();
      if (delta>0)
        textInField +=QString("\\mr%1").arg(delta, 3, 10, QChar('0'));
      else if (delta<0)
        textInField +=QString("\\ml%1").arg(-delta, 3, 10, QChar('0'));
      int destinationLen = destination->toPlainText().length();
      int textInFieldLen = textInField.length();
      if(textInField.length() != 0)
     destination->setPlainText(textInField);

      int sizeOfChanges = textInFieldLen-destinationLen;
      if (sizeOfChanges>0)
      {
      saveChanges(sizeOfChanges);//TODO
               changesDetected=true;
      }
//// qDebug() << "cursor changed";
}


void KeyloggerTE::tabTo4Spaces()
{
    disconnect(this, SIGNAL(textChanged()),this, SLOT(tabTo4Spaces()));

    QTextCursor textCurs = this->textCursor();
    int cursorPos = textCurs.position();

     QString text =  this->toPlainText();
     if (text.contains(QString("\t")))
         cursorPos += 3;
    text.replace(QString("\t"), QString("    "));
    this->setPlainText(text);
   textCurs.setPosition(cursorPos);
   this->setTextCursor(textCurs);
      connect(this, SIGNAL(textChanged()),this, SLOT(tabTo4Spaces()));
}

void KeyloggerTE::newText()
{
    clear();
    undo_changes.clear();
    redo_changes.clear();
    previousCursorPosition = 0;
    lastSlashPosInDestination = -1;
    textAfterBackSlash="";
    t_cursor = this->textCursor();
    changebuf.cursor = 0;
    changebuf.cymbol = "";
    changebuf.changeSize =0;
}
int KeyloggerTE::getPreviousCursorPosition() const
{
    return previousCursorPosition;
}

void KeyloggerTE::setPreviousCursorPosition(const int& value)
{
    previousCursorPosition = value;
}


