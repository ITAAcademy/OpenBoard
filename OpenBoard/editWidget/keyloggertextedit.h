#ifndef KEYLOGGERTEXTEDIT_H
#define KEYLOGGERTEXTEDIT_H

#include <QTextEdit>
#include <QColor>
#include <QStack>
#include <QClipboard>
#include <QApplication>
#include "mytextedit.h"
struct CursorSymbolExtended{
int cursor;
QString cymbol;
int changeSize;
};
class KeyloggerTE : public QTextEdit
{
    Q_OBJECT
private:
    enum SCAN_CODE_TABLE {SCAN_KEY_Z=44,SCAN_KEY_V=47,SCAN_KEY_X=45,SCAN_KEY_C=46,SCAN_KEY_A=30};
      CursorSymbolExtended changebuf;
     QTextCursor t_cursor;
 QStack<CursorSymbolExtended> undo_changes;

  QStack<CursorSymbolExtended> redo_changes;
int lastSlashPosInDestination = -1;
QString textAfterBackSlash="";
MyTextEdit *destination;

public slots:

public:
//QStack<int> changesSize;
bool changesDetected = false;
int previousCursorPosition = 0;
    void keyPressEvent(QKeyEvent *e);
     void mousePressEvent(QMouseEvent *eventPress);
     void mouseReleaseEvent(QMouseEvent *eventPress);
    explicit KeyloggerTE(MyTextEdit *destination,QWidget *parent = 0);
    void focusInEvent( QFocusEvent * ev ) ;
    void undo();
    void redo();
    void saveChanges(int sizeOfChange);
signals:
      void setFocus() ;
};
#endif // MYTEXTEDIT_H

