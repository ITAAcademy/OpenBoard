#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QColor>

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
public slots:
  void onEditText();
public:
    explicit MyTextEdit(QColor originalColor, QColor specifiedColor, QWidget *parent = 0);
    void textColorSet(int position);
   void mergeFormatOnWordOrSelection(int position);

public slots:

};

#endif // MYTEXTEDIT_H
