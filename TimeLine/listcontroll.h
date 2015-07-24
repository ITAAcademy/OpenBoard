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
//#include <QDeclarativeContext>
#include <../OpenBoard/drawSystem/drawsystem.h>
#include "imageprovider.h"

struct Element {
    QString key;
   // int lifeTime;

    //QImage icon;
//    int startDrawTime;
//    int x, y, z, width, height; //on canva

    DrawElement *draw_element;

    Element( QString key, int time,int x = 0, int y = 0, int z = 0, int width = 100, int height = 100) {
        this->key = key;
        draw_element = new DrawElement(NULL);
         draw_element->setLifeTime(time);
        draw_element->setX(x);
         draw_element->setY(y);
         draw_element->setZ(z);
         draw_element->setSize(width, height);

         draw_element->setIcon(QImage("qrc:/Block/file.png")); //for testing!!!!!!!!!!! delete after

    }
    Element() {
        this->key = "key";
 draw_element = new DrawElement(NULL);
          draw_element->setLifeTime(100);
         draw_element->setX(0);
          draw_element->setY(0);
          draw_element->setZ(0);
          draw_element->setSize(100, 100);

    }
    ~Element() {
        //delete draw_element;
    }

};

struct Track {
    int time;
    QList <Element> block;
    Track() { };
    Track( int time ,QList <Element> block ) {
        this-> time = time;
        this-> block = block;
    }
};



class ListControll : public QObject
{
    Q_OBJECT
    ImageProvider image_provider;
   // ImageProvider imageProvider;
 int maxTrackTime ;
    QQuickView view;
    QPoint prevMousePosition;
  // QVector< QList <QString> > test;
  //  QVector< QList <int> > testWidth;

     QVector< Track > tracks;
     Element selectedBlock;
int def_min_block_width = 100;
int scale_pointer_pos = 0;
QList <Element> pointed_block;
   //  QVector< int > testColumnWidth;
     void recountMaxTrackTime();
public:
    explicit ListControll(QObject *parent = 0);
    ~ListControll();

    void show();
    void close();
    void hide();
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
    Q_INVOKABLE void setBlockStartTime(int col, int i, int value);
    Q_INVOKABLE int getBlockStartTime(int col, int i);
    Q_INVOKABLE   void removeBlock(int col, int i);
    Q_INVOKABLE int getBlockTime(int col, int i) const;
     Q_INVOKABLE Element getBlock(int col, int i) const;
    Q_INVOKABLE int getTrackTime(int col) const;
    Q_INVOKABLE int getMaxTrackTime( ) const;
  Q_INVOKABLE void moveWindow( const int x,const int y) ;
   Q_INVOKABLE void  setPrevMousePosition( const int x,const int y) ;
   Q_INVOKABLE void setPrevMousePosition( const QPoint x);

    Q_INVOKABLE void setSelectedBlock(int col, int i);
    Q_INVOKABLE Element getSelectedBlock() ;

     Q_INVOKABLE void setScalePointerPos( int x);
Q_INVOKABLE int getScalePointerPos( );

    Q_INVOKABLE void calcPointedBlocks( );
    Q_INVOKABLE QList <Element> getPointedBlocks( );

    Q_INVOKABLE void setBlockIcon(int col, int i, QImage icon);
    Q_INVOKABLE QImage getBlockIcon(int col, int i);

     Q_INVOKABLE void setDrawX(int col, int i, int value);
     Q_INVOKABLE int getDrawX(int col, int i);
    Q_INVOKABLE void setDrawY(int col, int i, int value);
    Q_INVOKABLE int getDrawY(int col, int i);
    Q_INVOKABLE void setDrawZ(int col, int i, int value);
    Q_INVOKABLE int getDrawZ(int col, int i);
    Q_INVOKABLE void setDrawSize(int col, int i, int width, int height);
    Q_INVOKABLE QSize getDrawSize(int col, int i);

    Q_INVOKABLE void  play();
    Q_INVOKABLE void  pause();
    Q_INVOKABLE void  stop();


signals:
    void playSignal();
    void pauseSignal();
    void stopSignal();

public slots:
};

#endif // LISTCONTROLL_H
