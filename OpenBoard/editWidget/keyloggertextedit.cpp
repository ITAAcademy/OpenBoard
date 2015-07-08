#include "keyloggertextedit.h"
#include "qdebug.h"
#include <QKeyEvent>
#include <QTextEdit>
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
           int localCursorPositionInBlock = textCursor().positionInBlock();
           int localCursorBlockNumber = textCursor().blockNumber();
           int localCursorSelectionStart=textCursor().selectionStart();
           int localCursorSelectionEnd=textCursor().selectionEnd();
    QTextEdit::keyPressEvent(event);

            QString textInField = destination->toPlainText();
             QStringList stringsInCommandTextEdit = toPlainText().split('\n');
    //Якщо буква то просто вставляєм її в текст
    switch(keyCode){
    case Qt::Key_Up:
        qDebug() << "on_Key_UP";
        break;
    case Qt::Key_Down:
        qDebug() << "on_Key_DOWN";
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
    default:
        if(keyChar.length()>0) {
            textInField +=keyChar;
        }
        break;
    }

     destination->setPlainText(textInField);
     previousCursorPosition=textCursor().position();
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

