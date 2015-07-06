#include "keyloggertextedit.h"
#include "qdebug.h"
#include <QKeyEvent>
#include <QTextEdit>
KeyloggerTE::KeyloggerTE(MyTextEdit *destination){
this->destination=destination;
}
void KeyloggerTE::keyPressEvent(QKeyEvent *event){
    event->accept();
    int keyCode = event->key();
    QString keyChar(event->text());
    QTextEdit::keyPressEvent(event);
            QString textInField = destination->toPlainText();
    //Якщо буква то просто вставляєм її в текст
    switch(keyCode){
    case Qt::Key_Up:
        qDebug() << "on_Key_UP";
        break;
    case Qt::Key_Down:
        qDebug() << "on_Key_DOWN";
        break;
    case Qt::Key_Left:
        qDebug() << "on_KEY_LEFT";
        break;
    case Qt::Key_Right:
        qDebug() << "on_KEY_RIGHT";
        break;
    case Qt::Key_Backspace:
        qDebug() << "on_KEY_BACKSPACE";
        textInField +="\\<";
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        qDebug() << "on_KEY_ENTER";
        textInField +="\\n";
        break;
    default:
        if(keyChar.length()>0) {
            textInField +=keyChar;
        }
        break;
    }
     destination->setPlainText(textInField);
}


