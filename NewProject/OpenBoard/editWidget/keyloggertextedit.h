#ifndef KEYLOGGERTEXTEDIT_H
#define KEYLOGGERTEXTEDIT_H

#include <QTextEdit>
#include <QColor>
#include <QStack>
#include <QClipboard>
#include <QPlainTextEdit>
#include <QApplication>
#include "mytextedit.h"
struct CursorSymbolExtended{
int cursor;
QString cymbol;
int changeSize;
};
class KeyloggerTE : public QPlainTextEdit
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
    void tabTo4Spaces();
    void newText();
public:
//QStack<int> changesSize;
    void openText();
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
    int getPreviousCursorPosition() const;
    void setPreviousCursorPosition(const int &value);
    void hideEvent(QHideEvent *)
    {
        // 'false' means hidden..
        emit widgetVisibilityChanged(false);
    }

    void showEvent(QShowEvent *)
    {
        // 'true' means visible..
        emit widgetVisibilityChanged(true);
    }
    void setEnabled(bool state);
    void setDisabled(bool state);

signals:
    void setFocus() ;
    void widgetVisibilityChanged(bool state);
};
#endif // MYTEXTEDIT_H

