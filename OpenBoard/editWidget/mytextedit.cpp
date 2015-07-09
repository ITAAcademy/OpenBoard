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

 //connect(this, SIGNAL(textChanged()),this, SLOT(saveChanges()));
 pair_change=false;
 t_cursor = this->textCursor();
 newText();\

}
void MyTextEdit::focusInEvent( QFocusEvent * ev )
{
    emit MyTextEdit::setFocus() ;
    QTextEdit::focusInEvent(ev);
}
 void MyTextEdit::mergeFormatOnWordOrSelection(int position)
 {
    if (charCount==document()->characterCount()) return;
charCount=document()->characterCount();
     QTextCursor cursor = textCursor();
     cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
     cursor.movePosition(QTextCursor::Start, QTextCursor::KeepAnchor);
     cursor.mergeCharFormat(textFormat);

     if (position>=0 && position<=document()->characterCount())
     {
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
      colOrigin = value;
      textFormat.setForeground(value);
 }
 /*
 void MyTextEdit::onEditText()
 {
     /*int parserOutEmulated=qrand()%document()->characterCount();
     textColorSet(0);/*СИМУЛЯЦІЯ, В ЦЮ ФУНКЦЦІЮ
 ПОДАЄТЬСЯ ВИВІД ПАРСЕРСА,що вказує на індекс помилки*/


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
     emit doUndoRedoStart();
     if (undo_changes.size() >0)
     {
        //  qDebug() << "undom";
         CursorCymbol backup;
         backup.cursor = this->textCursor().position();
         backup.cymbol = this->toPlainText();
       //  qDebug() <<  backup.cymbol;
         redo_changes.push_back(backup);



        CursorCymbol change ;

       change = undo_changes.pop();
      // curs.setPosition(change.cursor);
       this->clear();
        this->append(change.cymbol);
       t_cursor.setPosition(change.cursor);
this->setTextCursor(t_cursor);
     }
     else this->clear();

 emit doUndoRedoEnd();
}

 void MyTextEdit::rendom()
 {

 if (redo_changes.size() >0)
 {
    emit doUndoRedoStart();

    CursorCymbol backup;
    backup.cursor = this->textCursor().position();
    backup.cymbol = this->toPlainText();
    undo_changes.push_back(backup);

    CursorCymbol change ;
    change = redo_changes.pop();
    this->setText(change.cymbol);
    t_cursor.setPosition(change.cursor);
    this->setTextCursor(t_cursor);

    emit doUndoRedoEnd();
 }
 }

 void MyTextEdit::saveChanges()
 {


     {
      undo_changes.push(changebuf);
     changebuf.cursor = this->textCursor().position();
     changebuf.cymbol = this->toPlainText();

   /*  qDebug() << "\nundo";  for (int i=0; i< undo_changes.size(); i++)
      {
         qDebug() << undo_changes[i].cymbol;
          qDebug() << undo_changes[i].cursor;
      }*/
  //   qDebug() << "\nredo"; for (int i=0; i< redo_changes.size(); i++)           qDebug() << redo_changes[i].cymbol;
     }
 }

 void MyTextEdit::openText()
 {
     changebuf.cursor = 1;
     changebuf.cymbol = this->toPlainText();
 }

 void MyTextEdit::newText()
 {
     changebuf.cursor = 0;
     changebuf.cymbol = "";
 }
