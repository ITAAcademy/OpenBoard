#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QColor>
#include <QStack>
#include <QClipboard>
#include <QApplication>

struct CursorCymbol{
    QTextCursor cursor;
    QChar cymbol;
};

class MyTextEdit : public QTextEdit
{
    Q_OBJECT
private:

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
public slots:
  void onEditText();
public:
  void undom();
  void rendom();
    void keyPressEvent(QKeyEvent *e);
    explicit MyTextEdit(QColor originalColor, QColor specifiedColor, QWidget *parent = 0);
    void textColorSet(int position);
   void mergeFormatOnWordOrSelection(int position);

   QColor getColOrigin() const;
   void setColOrigin(const QColor &value);

public slots:

};

#endif // MYTEXTEDIT_H
