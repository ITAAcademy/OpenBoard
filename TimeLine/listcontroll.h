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
#include <QFileDialog>

//#include <QDeclarativeContext>
#include <../OpenBoard/drawSystem/drawsystem.h>
#include "../Brush/imageclone.h"

class DrawTextElm;
class DrawBrushElm;
class DrawElement;

#define minBlockTime 1000


struct Element {
    QString key;
   // int lifeTime;

    //QImage icon;
//    int startDrawTime;
//    int x, y, z, width, height; //on canva
    //Element_type type;
    DrawElement *draw_element;

    Element( QString key, int time,int x = 0, int y = 0, int z = 0, int width = minBlockTime, int height = 100) {
        this->key = key;
        draw_element = new DrawElement((OGLWidget *)NULL, NULL);
         draw_element->setLifeTime(time);
        draw_element->setX(x);
         draw_element->setY(y);
         draw_element->setZ(z);
         draw_element->setSize(width, height);

         draw_element->setIcon(QImage("qrc:/Block/file.png")); //for testing!!!!!!!!!!! delete after

    }
    Element() {
        this->key = "key";
        draw_element = new DrawElement((OGLWidget *)NULL, NULL);
          draw_element->setLifeTime(minBlockTime);
         draw_element->setX(0);
          draw_element->setY(0);
          draw_element->setZ(0);
          draw_element->setSize(100, 100);
           draw_element->setStartDraw( 0);
    }
    Element(DrawElement *element) {
        this->key = element->getKey();
        draw_element = element;
          draw_element->setLifeTime(minBlockTime);
         draw_element->setX(0);
          draw_element->setY(0);
          draw_element->setZ(0);
          draw_element->setSize(100, 100);
          draw_element->setStartDraw( element->getStartDrawTime());

    }
    ~Element() {

    }
    void clear()
    {
        if(draw_element != NULL)
            delete draw_element;
        draw_element = NULL;
    }
    bool save(QIODevice* device)
    {
        QDataStream stream(device);
        stream << key ;
       draw_element->save(device);
       return true;
    }

    bool load(QIODevice* device)
    {
        QDataStream stream(device);
        stream >> key ;
        draw_element->loadTypeId(device);


       Element_type typeId = draw_element->getTypeId();// Element_type::Image;//static_cast<Element_type>(temp_type);

        if(typeId == Element_type::Text)
        {
            DrawTextElm *elm = new DrawTextElm(NULL);
                    elm->loadRest(device);
                    delete  draw_element;
                    draw_element = (DrawElement*) elm;
        }
        else
        if(typeId == Element_type::Image)
        {
           DrawImageElm *elm = new DrawImageElm(NULL,NULL);
                    elm->loadRest(device);
                    delete  draw_element;
                    elm->setDrawImage(elm->getIcon());
                    draw_element = (DrawElement*) elm;
                    //draw_element->getIcon().save("blaaaaaaaaaaaaaaaaaaaaaa.jpg");

        }
        else
        if(typeId == Element_type::Brushh)
        {
           DrawBrushElm *elm = new DrawBrushElm(NULL,NULL);
                    elm->loadRest(device);
                    delete  draw_element;
                    draw_element = (DrawElement*) elm;
        }
        else
        if(typeId == Element_type::Empty)
        {
           DrawElement *elm = new DrawElement(NULL,NULL);
                    elm->loadRest(device);
                    delete  draw_element;
                    draw_element = (DrawElement*) elm;
        }
        if(typeId == Element_type::Video)
        {
           DrawVideoElm *elm = new DrawVideoElm(NULL,NULL);
                    elm->loadRest(device);
                    delete  draw_element;
                    draw_element = (DrawElement*) elm;
        }
        return true;
    }

};

struct Track {
    unsigned int time;
    QList <Element> block;
    Track() { }
    Track( int time ,QList <Element> block ) {
        this-> time = time;
        this-> block = block;
    }
    void deleteClearBlocks ( ) {      
           while(block.size())
           {
          block.last().clear();
          block.pop_back();
           }

    }
    void appendBlockAt(int ind,Element block_val)
    {
       block.append(block_val);
       block.move( block.size()-1,ind);


       time += block_val.draw_element->getLifeTime();
      // testWidth[col].append(200);
       //testColumnWidth[col]+=200;
     //  // //qDebug() << "SIZE   " << test.size();

    }

    bool save(QIODevice* device)
    {
        QDataStream stream(device);
        stream << block.size() << time ;
         qDebug() << "num of saved blocks " << block.size();
        for (int i=0; i< block.size(); i++)
        {
             qDebug() << "block[i]:  " << i;
            block[i].save(device);
         }
        return true;
    }

    bool load(QIODevice* device)
    {
        block.clear();
        time = 0;
        int blocks_size;
        QDataStream stream(device);
        stream >> blocks_size >> time ;
    qDebug() << "Track::load  blocks_size = " << blocks_size;
    //return true;
        for (int i=0; i< blocks_size; i++)
        {
            Element temp;
             temp.load(device);
            block.append(temp);
            qDebug() << "load block[i]:  " << i;
        }
        qDebug() << "bool load(QIODevice* device) finished";
        return true;
    }
    void clear()
    {
        for (int i=0; i< block.size(); i++)
            block[i].clear();
        block.clear();
        time = 0;
    }

};



class ListControll : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    bool isEditBlockShow = false;
    bool isProjectChange = false;
    unsigned long int maxTrackTime ;
    float scale_scroll_children = 10.0;
    float zoom_speed = 1.0;
    QQuickView view;
    QPoint framaMousePosition;
     QPoint prevMousePosition;
    // QVector< QList <QString> > test;
    //  QVector< QList <int> > testWidth;

    QVector< Track > tracks;
   // Element selectedBlock;
    QPoint selectedBlockPoint;
    int def_min_block_width = minBlockTime;
    int scale_pointer_pos = 0;
    QList <Element> pointed_block;
   // QList <Element> pointed_time_blocks;
    //  QVector< int > testColumnWidth;
    void recountMaxTrackTime();
    ImageClone *cloneImg;

    //QElapsedTimer timer;
      qint64 timerValue;
    qint64 time_sum;
    Element block_in_buffer;
    int life_time_in_buffer;
    bool buffer_is_full;

public:
     int isPlayPauseStop = 3;


    bool save(QIODevice* device);
    bool load(QIODevice* device);

   Q_INVOKABLE void loadCurrentTextInTheFirstBlockWhenInit();
    volatile bool isBlocked = false;
    volatile int countBlocked = 0;

    explicit ListControll(QObject *parent = 0);
    ~ListControll();

    void show();
    void close();
    void hide();
    void setFocus();
    void setViewPosition(QPoint pos); //1234
    Q_INVOKABLE QPoint getViewPosition();
    bool isVisible();
    bool isActiveWindow();
    Q_INVOKABLE  bool isProjectChanged();
    Q_INVOKABLE  void setIsProjectChanged(bool);
    Q_INVOKABLE int getTrackSize(int col);
    Q_INVOKABLE QString getBlockKey(int col, int i) ;
    Q_INVOKABLE void addNewBlock(int col, QString str , DrawElement *element = NULL);
    Q_INVOKABLE void addNewTrack( );
    Q_INVOKABLE void loadFromFile();
    Q_INVOKABLE bool removeLastBlock(int col);
    Q_INVOKABLE bool removeLastTrack();
    Q_INVOKABLE bool removeTrack(int col);
    Q_INVOKABLE void reverseBlocks(int col, int init_pos, int end_pos);
    void setBlocks(int col,const  QList <Element> &value);
    Q_INVOKABLE   void setBlockKey(int col, int i, QString name);\
    Q_INVOKABLE void setBlockTime(int col, int i, int value);
    Q_INVOKABLE void setBlockStartTime(int col, int i, int value);
    Q_INVOKABLE int getBlockStartTime(int col, int i);
    Q_INVOKABLE bool setBlockDrawElemet(DrawElement *elm, int col, int i);
    Q_INVOKABLE   void removeBlock(int col, int i);
    Q_INVOKABLE int getBlockTime(int col, int i) ;
    Q_INVOKABLE Element getBlock(int col, int i) ;
    Q_INVOKABLE Element getBlock(QPoint point) ;
    Q_INVOKABLE int getTrackTime(int col) ;
    Q_INVOKABLE int getMaxTrackTime( ) ;

  Q_INVOKABLE void moveBlockFromTo(int col,int ind0, int ind1);
    Q_INVOKABLE void  moveBlockFromTo(int col0,int ind0,int col1, int ind1);

    Q_INVOKABLE void moveWindow( ) ;
    Q_INVOKABLE void resizeWindowWidth(bool left) ;
    Q_INVOKABLE void resizeWindowHeight(bool up) ;

    Q_INVOKABLE void  setFramaMousePosition( const int x,const int y) ;
    Q_INVOKABLE void setFramaMousePosition( const QPoint x);

     Q_INVOKABLE QPoint  getMousePosition();

  //  Q_INVOKABLE void setSelectedBlock(int col, int i);
   // Q_INVOKABLE Element getSelectedBlock() ;

    Q_INVOKABLE void setScalePointerPos( int x);
    Q_INVOKABLE int getScalePointerPos( );

    Q_INVOKABLE void calcPointedBlocks( );

   Q_INVOKABLE  void calcPointedBlocksAtTime(int ms );
    Q_INVOKABLE  void calcPointedBlocksAtTime( );

  Q_INVOKABLE  QList <Element> getPointedBlocksAtTime( );
    Q_INVOKABLE QList <Element> getPointedBlocks( );
    QList <DrawElement*> getPointedBlocksDE( );

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
    Q_INVOKABLE QRect getDrawRect(int col, int i);

    Q_INVOKABLE void  play();
    Q_INVOKABLE void  pause();
    Q_INVOKABLE void  stop();
    Q_INVOKABLE qint64 getPlayTime();
     Q_INVOKABLE void setPlayTime(qint64);

    QImage requestImage(const QString & id, QSize * size, const QSize & requestedSize);


   Q_INVOKABLE QPoint getSelectedBlockPoint() const;
  Q_INVOKABLE  void setSelectedBlockPoint(const QPoint &value);
  Q_INVOKABLE  void setSelectedBlockPoint(int col, int ind);

    Q_INVOKABLE void  setPrevMousePosition();
    Q_INVOKABLE QPoint  getPrevMousePosition();
    Q_INVOKABLE void  update();
   Q_INVOKABLE void emitUpdateSignal();
   Q_INVOKABLE void  emitUpdateTrackAt(int col);

    Q_INVOKABLE int  getTracksNumber();

    Q_INVOKABLE int  resetProjectToDefault();
    Q_INVOKABLE void convertCurentBlockToText();

    Q_INVOKABLE void addBlockAt(int col, int ind, DrawElement *element = NULL);

  void sendUpdateModel();

 Q_INVOKABLE  float getScaleScrollChildren() const;
 Q_INVOKABLE  void setScaleScrollChildren(const float &value);
 Q_INVOKABLE  void changeScaleScrollChildren(const float &value);

  Q_INVOKABLE  void videoSignalHAHAHAA(QString addrW)
{
  //QDesktopServices::openUrl(QUrl(QString("E:/Adele - Someone Like You.mp4")));
 // QDesktopServices::openUrl(QUrl::FromLocalFile(addrW, QUrl::TolerantMode));
}

Q_INVOKABLE  float getZoomSpeed() const;
 Q_INVOKABLE void setZoomSpeed(float value);

Q_INVOKABLE  bool getIsEditBlockShow() const;
Q_INVOKABLE  void setIsEditBlockShow(bool value);

  volatile bool getBlocked() const;
  void setBlocked(volatile bool value);

signals:
  void loadFromFileSignal();
  void playSignal();
  void pauseSignal();
  void stopSignal();
    void updateSignal();
    void updateTrackAt(int);
    void updateModel();
    void blockEditedSignal();

    void updateSelectedBlock(QPoint point);

    void newProjectSignel();
    void openProjectSignel();
    void saveProjectSignel();
    void resetProjectSignel();

    void focusLostSignal();
    void focusFoundSignal();
    void imageLoadedPictureSizeSignal(QSize);

//void setScalePointerPosSignal(int value);
public slots:
    void addMsToTimerValue(int ms);
Q_INVOKABLE void emitNewProject();
   Q_INVOKABLE void  copyBlockToBuffer();
     Q_INVOKABLE void  pasteBlockFromBuffer();
     Q_INVOKABLE void setBlockTimeFromBuffer();
  Q_INVOKABLE void emitOpenProject();
  Q_INVOKABLE void emitSaveProject();
 Q_INVOKABLE void  emitBlockEditedSignal();
Q_INVOKABLE void  emitPlaySignal();
Q_INVOKABLE void  emitPauseSignal();
Q_INVOKABLE void  emitStopSignal();
    Q_INVOKABLE   void emitResetProject();
  Q_INVOKABLE  void emitFocusLostSignal();
  Q_INVOKABLE  void emitFocusFoundSignal();

    Q_INVOKABLE void zoomMinus();
    Q_INVOKABLE void zoomPlus();
    Q_INVOKABLE bool testIndexs(const int col, const int index);
};

#endif // LISTCONTROLL_H
