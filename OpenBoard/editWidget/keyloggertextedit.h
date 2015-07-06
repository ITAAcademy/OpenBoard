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

MyTextEdit *destination;
public slots:
   // void onEditText();
public:
    void keyPressEvent(QKeyEvent *e);
    explicit KeyloggerTE(MyTextEdit *destination);

signals:
};
#endif // MYTEXTEDIT_H

