#ifndef LISTCONTROLL_H
#define LISTCONTROLL_H

#include <QObject>
#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView> //Not using QQmlApplicationEngine because many examples don't have a Window{}
#include <QQmlContext>
#include <QList>
#include <QDebug>

class ListControll : public QObject
{
    Q_OBJECT
 int maxwidth ;
    QQuickView view;
   QVector< QList <QString> > test;
    QVector< QList <int> > testWidth;
     QVector< int > testColumnWidth;
     void recountMaxColumnWidth();
public:
    explicit ListControll(QObject *parent = 0);
    ~ListControll();

    void show();
    Q_INVOKABLE int getColumnSize(int col) const;
    Q_INVOKABLE QString getTest(int col, int i) const;
    Q_INVOKABLE void addNewTest(int col, QString str );
    Q_INVOKABLE void addNewColumn( );
    Q_INVOKABLE bool removeLastTest(int col);
     Q_INVOKABLE bool removeLastColumn();
    Q_INVOKABLE void reverseTests(int col, int init_pos, int end_pos);
    void setTest(int col,const QList<QString> &value);
Q_INVOKABLE   void setTestName(int col, int i, QString name);
    Q_INVOKABLE   void removeTest(int col, int i);
    Q_INVOKABLE int getTestWidth(int col, int i) const;
    Q_INVOKABLE int getColumnWidth(int col) const;
    Q_INVOKABLE int getMaxTestWidth( ) const;

    Q_INVOKABLE void setTestWidth(int col, int i, int value);

signals:

public slots:
};

#endif // LISTCONTROLL_H
