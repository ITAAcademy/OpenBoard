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

    QQuickView view;
    QList <QString> test;
    QList <int> testWight;
public:
    explicit ListControll(QObject *parent = 0);
    ~ListControll();

    void show();
    Q_INVOKABLE int getTestSize() const;
    Q_INVOKABLE QString getTest(int i) const;
    Q_INVOKABLE void addNewTest( QString str );
    void setTest(const QList<QString> &value);

    Q_INVOKABLE int getTestWight( int i) const;
    Q_INVOKABLE void setTestWight( int value, int i);

signals:

public slots:
};

#endif // LISTCONTROLL_H
