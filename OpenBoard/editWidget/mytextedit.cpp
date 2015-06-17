#include "mytextedit.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QColor>
#include <QColorDialog>
#include <QTextStream>
#include <QDebug>
#include "QTime"
#include <QTextBlock>


MyTextEdit::MyTextEdit(QColor originalColor,QColor specifiedColor,QWidget *parent) :
    QTextEdit(parent)
{
 //connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(onEditText()));
  colSelection=specifiedColor;
  colOrigin=originalColor;
 specefiedFormat.setForeground(colSelection);
 textFormat.setForeground(colOrigin);
 //Для емуляції парсера
 QTime midnight(0,0,0);
 qsrand(midnight.secsTo(QTime::currentTime()));

}

 void MyTextEdit::mergeFormatOnWordOrSelection(int position)
 {
     if (charCount==document()->characterCount()) return;
charCount=document()->characterCount();
     QTextCursor cursor = textCursor();
     cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
     cursor.movePosition(QTextCursor::Start, QTextCursor::KeepAnchor);
     cursor.mergeCharFormat(textFormat);

     if (position>=0 && position<=document()->characterCount()){
         cursor.setPosition(position);
         cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor,3);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor,6);
     cursor.mergeCharFormat(specefiedFormat);
}
 }


 void MyTextEdit::textColorSet(int position)
 {
     mergeFormatOnWordOrSelection(position);
 }
 
 QColor MyTextEdit::getColOrigin() const
 {
     return colOrigin;
 }
 
 void MyTextEdit::setColOrigin(const QColor &value)
 {
      textFormat.setForeground(value);
 }
 void MyTextEdit::onEditText()
 {
     int parserOutEmulated=qrand()%document()->characterCount();
     textColorSet(0);/*СИМУЛЯЦІЯ, В ЦЮ ФУНКЦЦІЮ
 ПОДАЄТЬСЯ ВИВІД ПАРСЕРСА,що вказує на індекс помилки*/
 }

 void MyTextEdit::keyPressEvent(QKeyEvent *e) {
 if(e->type() == QKeyEvent::KeyPress) {
 if(e->matches(QKeySequence::Undo))
 undom();
 else
     if(e->matches(QKeySequence::Redo))
     rendom();
     else
 QTextEdit::keyPressEvent(e);
 }
 }

 void MyTextEdit::undom()
{
     QTextCursor cursor = this->textCursor();
     QString text = cursor.block().text();
     CursorCymbol change;
     change.cursor = cursor;
     change.cymbol = text.at(text.size()-1);
     undo_changes.push(change);
     QTextEdit::undo();
     QTextEdit::undo();
     QTextEdit::undo();
     this->setTextCursor(cursor);
}

 void MyTextEdit::rendom()
 {
     if (undo_changes.isEmpty()==false)
     {
     CursorCymbol change = undo_changes.pop();
     this->setTextCursor(change.cursor);
     QClipboard *clipboard = QApplication::clipboard();
     QString ss; ss.append(change.cymbol);
     clipboard->setText(ss);
     paste();
     }
 }
