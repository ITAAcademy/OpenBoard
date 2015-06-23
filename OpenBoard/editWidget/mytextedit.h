#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QColor>
#include <QStack>
#include <QClipboard>
#include <QApplication>

struct CursorCymbol{
    int cursor;
    QString cymbol;
};

class MyTextEdit : public QTextEdit
{
    Q_OBJECT
private:
      QTextCursor t_cursor;
bool pair_change;
bool undo_redo;
bool undo1;
CursorCymbol changebuf;
    // void cursorPositionChanged();
     int previousCharPosition = -1;
     QTextCharFormat previousCharFormat;
     QTextCursor previousCursor;
     QTextCharFormat specefiedFormat;
     QTextCharFormat textFormat;
     QColor colSelection;
     QColor colOrigin;
     int charCount = 0;
     QStack<CursorCymbol> undo_changes;
     QStack<CursorCymbol> redo_changes;
     CursorCymbol strtempo;
public slots:
 // void onEditText();
    void saveChanges();
public:
 void openText();
 void newText();
  void undom();
  void rendom();
    void keyPressEvent(QKeyEvent *e);
    explicit MyTextEdit(QColor originalColor, QColor specifiedColor, QWidget *parent = 0);
    void textColorSet(int position);
   void mergeFormatOnWordOrSelection(int position);

   QColor getColOrigin() const;
   void setColOrigin(const QColor &value);

 signals:
   void doUndoRedoStart();
void doUndoRedoEnd();
};

#endif // MYTEXTEDIT_H
