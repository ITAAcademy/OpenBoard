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
int previousCursorPosition = 0;
int lastSlashPosInDestination = -1;
QString textAfterBackSlash="";
MyTextEdit *destination;
public slots:

public:
    void keyPressEvent(QKeyEvent *e);
     void mousePressEvent(QMouseEvent *eventPress);
     void mouseReleaseEvent(QMouseEvent *eventPress);
    explicit KeyloggerTE(MyTextEdit *destination,QWidget *parent = 0);

signals:
};
#endif // MYTEXTEDIT_H

