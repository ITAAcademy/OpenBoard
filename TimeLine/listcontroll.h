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

struct Element {
    QString key;
    int time;
    Element( QString key, int time) {
        this->key = key;
         this->time = time;
    }
    Element() {
        this->key = "key";
         this->time = 200;
    }
};

struct Track {
    int time;
    QList <Element> block;
    Track() {
    };
    Track( int time ,QList <Element> block ) {
        this-> time = time;
        this-> block = block;

    };
};



class ListControll : public QObject
{
    Q_OBJECT
 int maxTrackTime ;
    QQuickView view;
  // QVector< QList <QString> > test;
  //  QVector< QList <int> > testWidth;

     QVector< Track > tracks;

   //  QVector< int > testColumnWidth;
     void recountMaxTrackTime();
public:
    explicit ListControll(QObject *parent = 0);
    ~ListControll();

    void show();
    Q_INVOKABLE int getTrackSize(int col) const;
    Q_INVOKABLE QString getBlockKey(int col, int i) const;
    Q_INVOKABLE void addNewBlock(int col, QString str );
    Q_INVOKABLE void addNewTrack( );
    Q_INVOKABLE bool removeLastBlock(int col);
     Q_INVOKABLE bool removeLastTrack();
    Q_INVOKABLE void reverseBlocks(int col, int init_pos, int end_pos);
    void setBlocks(int col,const  QList <Element> &value);
Q_INVOKABLE   void setBlockKey(int col, int i, QString name);\
     Q_INVOKABLE void setBlockTime(int col, int i, int value);
    Q_INVOKABLE   void removeBlock(int col, int i);
    Q_INVOKABLE int getBlockTime(int col, int i) const;
    Q_INVOKABLE int getTrackTime(int col) const;
    Q_INVOKABLE int getMaxTrackTime( ) const;




signals:

public slots:
};

#endif // LISTCONTROLL_H
