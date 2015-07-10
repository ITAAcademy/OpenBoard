#ifndef KEYLOGGERTEXTEDIT_H
#define KEYLOGGERTEXTEDIT_H

#include <QTextEdit>
#include <QColor>
#include <QStack>
#include <QClipboard>
#include <QApplication>
#include "mytextedit.h"

class KeyloggerTE : public QTextEdit
{
    Q_OBJECT
private:

int lastSlashPosInDestination = -1;
QString textAfterBackSlash="";
MyTextEdit *destination;

public slots:

public:
int previousCursorPosition = 0;
    void keyPressEvent(QKeyEvent *e);
     void mousePressEvent(QMouseEvent *eventPress);
     void mouseReleaseEvent(QMouseEvent *eventPress);
    explicit KeyloggerTE(MyTextEdit *destination,QWidget *parent = 0);
    void focusInEvent( QFocusEvent * ev ) ;
signals:
      void setFocus() ;
};
#endif // MYTEXTEDIT_H

