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

struct Element {
    QString key;
    int lifeTime;

    QImage icon;
    int startDrawTime;
    int x, y, z, width, height; //on canva

    Element( QString key, int time,int x = 0, int y = 0, int z = 0, int width = 100, int height = 100) {
        this->key = key;
         this->lifeTime = time;
        this->x=x;
         this->y = y;
         this->z = z;
         this->width = width;
         this->height = height;

    }
    Element() {
        this->key = "key";
         this->lifeTime = 100;
         x= y= z=0;  width=height=100;
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

signals:

public slots:
};

#endif // LISTCONTROLL_H
