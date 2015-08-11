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
 connect(this, SIGNAL(textChanged()),this, SLOT(tabTo4Spaces()));
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
     if(isEnabled())
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

      QTextCursor cursor = textCursor();
      cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
      cursor.movePosition(QTextCursor::Start, QTextCursor::KeepAnchor);
      QTextCharFormat textFormat;
      textFormat.setForeground(QColor(value));
      cursor.mergeCharFormat(textFormat);
 }
 /*
 void MyTextEdit::onEditText()
 {
     /*int parserOutEmulated=qrand()%document()->characterCount();
     textColorSet(0);/*СИМУЛЯЦІЯ, В ЦЮ ФУНКЦЦІЮ
 ПОДАЄТЬСЯ ВИВІД ПАРСЕРСА,що вказує на індекс помилки*/


 void MyTextEdit::keyPressEvent(QKeyEvent *e) {
        quint32 scanCode = e->nativeScanCode();
         int keyCode = e->key();
 if(e->type() == QKeyEvent::KeyPress)
 {
 if(e->matches(QKeySequence::Undo))
 undom();
 else
     if(e->matches(QKeySequence::Redo))
     rendom();
 else
 QTextEdit::keyPressEvent(e);

 if(e->modifiers() & Qt::ControlModifier)
 {

     if (scanCode==SCAN_KEY_V)
     {
         if (keyCode!=Qt::Key_V){
             QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_V,Qt::ControlModifier);
             QCoreApplication::postEvent (this, event);
         }
     }
     else
     if (scanCode==SCAN_KEY_X)
     {
         if (keyCode!=Qt::Key_X)
         {
             QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_X,Qt::ControlModifier);
             QCoreApplication::postEvent (this, event);
         }
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
         else
         if (scanCode==SCAN_KEY_Z)
         {
             if (keyCode!=Qt::Key_Z)
             {
                 QKeyEvent *e = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Z,Qt::ControlModifier);
                 QCoreApplication::postEvent (this, e);
             }

         }  

 }



 }
 }

 void MyTextEdit::showEvent(QShowEvent *event)
 {

 }

 void MyTextEdit::hideEvent(QHideEvent *event)
 {

 }

 void MyTextEdit::undom()
{
     emit doUndoRedoStart();
     if (undo_changes.size() >0)
     {
        //  // qDebug() << "undom";
         CursorCymbol backup;
         backup.cursor = this->textCursor().position();
         backup.cymbol = this->toPlainText();
       //  // qDebug() <<  backup.cymbol;
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
    this->setPlainText(change.cymbol);
    t_cursor.setPosition(change.cursor);
    this->setTextCursor(t_cursor);

    emit doUndoRedoEnd();
 }
 }

 void MyTextEdit::appendNoNL( QString text )
 {
     /*QTextCursor cursor(textCursor());
     cursor.setPosition(QTextCursor::End, QTextCursor::MoveAnchor);
     //I have to do this too. - I was forgetting this!!!!
     moveCursor (QTextCursor::End);
     setTextCursor(cursor);
     insertPlainText (text);*/
     emit doUndoRedoStart();
     setPlainText(toPlainText() + text);
     emit doUndoRedoEnd();

 }

  void MyTextEdit::tabTo4Spaces()
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

 void MyTextEdit::saveChanges()
 {

     {
      undo_changes.push(changebuf);
     changebuf.cursor = this->textCursor().position();
     changebuf.cymbol = this->toPlainText();

   /*  // qDebug() << "\nundo";  for (int i=0; i< undo_changes.size(); i++)
      {
         // qDebug() << undo_changes[i].cymbol;
          // qDebug() << undo_changes[i].cursor;
      }*/
  //   // qDebug() << "\nredo"; for (int i=0; i< redo_changes.size(); i++)           // qDebug() << redo_changes[i].cymbol;
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
     undo_changes.clear();
     redo_changes.clear();
     clear();
 }
