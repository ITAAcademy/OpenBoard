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
#include "../FileManager/filecontroll.h"

#include "group.h"
#include <../OpenBoard/drawSystem/drawsystem.h>

#include "../Brush/imageclone.h"
#include <QMessageBox>

class DrawTextElm;
class DrawBrushElm;
class DrawElement;

#define minBlockTime 1000
#define VERSION 2.8

bool isFileExists(QString path) ;

struct Track {
private:
    unsigned long int time = 0 ;
    unsigned long int prev_time =  0;
    unsigned long int time_change =  0;

public:
    void setTime(unsigned long int value)
    {
        prev_time = time;
        time = value;
    }
    void addTime(unsigned long int value)
    {
        prev_time = time;
        time += value;
    }
    unsigned long int getTime()
    {
        return time;
    }
    unsigned long int getTimeChange()
    {
        return time_change;
    }

    unsigned long int calcTimeChange()
    {
        time_change = time - prev_time;
        return time_change;
    }

    void setTimeChange(unsigned long int value)
    {
        time_change = value;
    }




    QList <DrawElement *> block;
    Track()
    {

    }
    Track( int time ,QList <DrawElement *> block ) {
        this-> time = time;
        this-> block = block;
    }
    void deleteClearBlocks ( ) {
        while(block.size())
        {
            delete block.last();
            block.pop_back();
        }

    }
    void appendBlockAt(int ind,DrawElement *  block_val)
    {
        block.append(block_val);
        block.move( block.size()-1,ind);


        time += block_val->getLifeTime();
        // testWidth[col].append(200);
        //testColumnWidth[col]+=200;
        //  // //qDebug() << "SIZE   " << test.size();

    }

    bool save(QIODevice* device)
    {
        QDataStream stream(device);
        stream << block.size() ;
        stream.writeRawData((char*)&time, sizeof(unsigned long int));
        qDebug() << "num of saved blocks " << block.size();
        for (int i=0; i< block.size(); i++)
        {
            qDebug() << "block[i]:  " << i;
            block[i]->save(device);
        }

        return true;
    }

    bool load(QIODevice* device, float version)
    {
        block.clear();
        time = 0;
        int blocks_size;
        QDataStream stream(device);
        stream >> blocks_size ;
        stream.readRawData((char*)&time, sizeof(unsigned long int));
        //qDebug() << "Track::load  blocks_size = " << blocks_size;
        //return true;
        for (int i=0; i< blocks_size; i++)
        {
            block.append(loadDrawElement(device, version));
        }
        // qDebug() << "block size" << block.size();
        return true;
    }
    void clear()
    {
        for (int i=0; i< block.size(); i++)
        {
            qDebug()<<"clear i:"<<i;
            if(block[i] != NULL)
            {
                qDebug() << "block[i]:"<< block[i];
                delete block[i];
            }
            block[i] = NULL;

        }
        block.clear();
        time = 0;
    }

};



class ListControll : public QObject, public QQuickImageProvider
{
    Q_OBJECT

     int spaces_to_add = -1;
    QPoint curent_block = QPoint(-1,-1);
    bool load_from_file_or_library;
    QMessageBox mess_box;
    FileManager f_manager;
    OGLWidget *drawWidget;
    int curent_block_group_num = -1;
    QList <Group> block_groups;
    Group test_group;
    Group *curent_group = NULL;
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
    QList <DrawElement *> pointed_block;
    // QList <Element> pointed_time_blocks;
    //  QVector< int > testColumnWidth;
    void recountMaxTrackTime();
    ImageClone *cloneImg;
    int group_changed = false;
    //QElapsedTimer timer;
    unsigned long int timerValue;
    unsigned long int time_sum;
    DrawElement * block_in_buffer = NULL;
    int life_time_in_buffer;
    bool buffer_is_full;
    QRect yellow_rec;
    int spacing_btw_blocks = 0;
    bool ctrl_pressed = false;
    bool glWindInited = false;

    bool isGroupChanged = false;
public:

    Q_INVOKABLE QPoint getCurentBlock();
   Q_INVOKABLE void setCurentBlock (QPoint value);
    Q_INVOKABLE void setCurentBlock (int col, int ind);
    int isPlayPauseStop = 3;
    static const int blockHeightPlusSpacing = 102;


    bool save(QIODevice* device);
    bool load(QIODevice* device);


    volatile bool isBlocked = false;
    volatile int countBlocked = 0;

    explicit ListControll(/*OGLWidget *drawWidget = NULL ,*/QObject *parent = 0);
    ~ListControll();

    void updateBlocksStartTimesFrom(int col0, int ind0, bool withGroup = false);
    Q_INVOKABLE bool balanceBlocksIfIsGroups(int col0, int ind0, bool calc_time_change = true);
    Q_INVOKABLE bool checkBlockValidGroup(DrawElement *elm);
    void updateBlocksIndexFrom(int col, int ind);
    void show();
    void close();
    void hide();
    void setFocus();
    void setViewPosition(QPoint pos); //1234
    Q_INVOKABLE QPoint getViewPosition();
    bool isVisible();
    bool isActiveWindow();
    Q_INVOKABLE bool attachBlock(int col, int index, int value);

    Q_INVOKABLE bool addBlockToGroup(DrawElement* block);
    Q_INVOKABLE bool addBlockToGroup(int col,int ind);
    Q_INVOKABLE bool removeBlockFromGroup(DrawElement* block);
    Q_INVOKABLE void setCtrlPressed(bool value);
    Q_INVOKABLE bool getCtrlPressed();

    Q_INVOKABLE bool setSpacingBtwBlocks(int);
    Q_INVOKABLE int getSpacingBtwBlocks();
    Q_INVOKABLE  bool isProjectChanged();
    Q_INVOKABLE  QRect getYellowRect();
    Q_INVOKABLE  void setIsProjectChanged(bool);
    Q_INVOKABLE int getTrackSize(int col);
    Q_INVOKABLE QString getBlockKey(int col, int i) ;
    Q_INVOKABLE void addNewBlock(int col, QString str = QString("block"+ QString::number(qrand())), DrawElement *element = NULL);


    Q_INVOKABLE   int getBlockTypeId(int col,int ind);
    Q_INVOKABLE   int getBlockTypeIdInt(int col,int ind);
    Q_INVOKABLE void addNewTrack( );
    Q_INVOKABLE int lastNotEmptyBlockIndexBeginFrom(int col, int ind );
    Q_INVOKABLE bool removeLastBlock(int col);
    Q_INVOKABLE bool removeLastTrack();
    Q_INVOKABLE bool removeTrack(int col);
    Q_INVOKABLE void reverseBlocks(int col, int init_pos, int end_pos);
    void setBlocks(int col,const  QList <DrawElement * > &value);
    Q_INVOKABLE   void setBlockKey(int col, int i, QString name);\
    Q_INVOKABLE void setBlockTime(int col, int i, int value, bool resize_next_empty = false);
    Q_INVOKABLE void setBlockTimeWithUpdate(int col, int i, int value, bool visual);
    Q_INVOKABLE void setBlockStartTime(int col, int i, int value);
    Q_INVOKABLE int getBlockStartTime(int col, int i);
    //Q_INVOKABLE bool setBlockDrawElemet(DrawElement *elm, int col, int i);
    Q_INVOKABLE   bool removeBlock(int col, int i, bool copy_in__buffer = true );
    Q_INVOKABLE int getBlockTime(int col, int i) ;
    Q_INVOKABLE DrawElement *  getBlock(int col, int i) ;
    Q_INVOKABLE DrawElement *  getBlock(QPoint point) ;
    Q_INVOKABLE int getTrackTime(int col) ;
    Q_INVOKABLE int getMaxTrackTime( ) ;

    Q_INVOKABLE void moveBlockFromTo(int col,int ind0, int ind1);
    Q_INVOKABLE void  moveBlockFromTo(int col0,int ind0,int col1, int ind1);
    Q_INVOKABLE void  cloneBlock(DrawElement *origin, DrawElement *clone);
    Q_INVOKABLE void cloneDrawElement (DrawElement *origin, DrawElement *clone);

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

    Q_INVOKABLE  QList <DrawElement * > getPointedBlocksAtTime( );
    Q_INVOKABLE QList <DrawElement * > getPointedBlocks( );
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
    Q_INVOKABLE void  setBlockAnimation(int col, int ind,int state, int time);
    Q_INVOKABLE void  setBlockAnimationTime(int col, int ind, int time);
    Q_INVOKABLE void  setBlockAnimationState(int col, int ind,int state);
    Q_INVOKABLE QPoint  getBlockAnimation(int col, int ind);


    Q_INVOKABLE QPoint  getPrevMousePosition();
    Q_INVOKABLE void  update();
    Q_INVOKABLE void emitUpdateSignal();
    Q_INVOKABLE void  emitUpdateTrackAt(int col);

    Q_INVOKABLE int  getTracksNumber();

    Q_INVOKABLE int  resetProjectToDefault();
    Q_INVOKABLE void convertCurentBlockToText();


    Q_INVOKABLE void addBlockAt(int col, int ind, DrawElement *element = NULL , int life_time = -1,bool need_balance = false );
    Q_INVOKABLE void addBlockWithSpaceAt(int col, int ind,int space, DrawElement *element = NULL , int life_time = -1,bool need_balance = false );
    Q_INVOKABLE void addBlockWithSpaceFromBufferAt(int col, int ind,int space,   int life_time = -1 ,bool need_balance = false);


    Q_INVOKABLE DrawElement* getBlockFromBuffer();
    Q_INVOKABLE getBlockIndToAddFromPos(int col,int ind, int pos);
    Q_INVOKABLE getBlockSpaceToAddFromPos(int col,int ind); //call after getBlockIndToAddFromPos
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

    Q_INVOKABLE QString getBlockBorderColor(int col,int ind);

    Q_INVOKABLE  bool getIsEditBlockShow() const;
    Q_INVOKABLE  void setIsEditBlockShow(bool value);

    volatile bool getBlocked() const;
    void setBlocked(volatile bool value);

    int getBlockHeightPlusSpacing() const;

    bool getGlWindInited() const;
    void setGlWindInited(bool value);

    Q_INVOKABLE bool getCurent_group() const;
    Q_INVOKABLE bool createEmptyBlock(int col);
    Q_INVOKABLE bool getCurent_group(int col, int index) ;
    Q_INVOKABLE long tryResizeCurentGroup(int shift);
    Q_INVOKABLE long tryResizeMemberInCurentGroup(int shift, int col, int index);
    Q_INVOKABLE QPoint getCurent_groupMembers(int index);
    Q_INVOKABLE int getCurent_groupMembersSize();

    Q_INVOKABLE void showF_manager(int x,int y);
    Q_INVOKABLE void showF_manager(QPoint pos);
    Q_INVOKABLE void showF_manager();
    Q_INVOKABLE void setLoadF_manager(bool file_or_library);
    Q_INVOKABLE void setPosF_manager(QPoint pos);
    Q_INVOKABLE void setPosF_manager(int x,int y);
    Q_INVOKABLE void setPosDefaultF_manager();
    Q_INVOKABLE void hideF_manager();


signals:
    void borderColorChangedSignal(int col,int ind, QString color);
    // void sizeChangedSignal(int,int,unsigned long);
    void loadFromFileSignal();
    void drawRectangleSignal();
    void removeRectangleSignal();

    void playSignal();
    void pauseSignal();
    void stopSignal();
    void showEffectsSignal();
    void hideEffectsSignal();
    void updateSignal();
    void updateTrackAt(int);
    void updateModel();
    void blockEditedSignal();

    void updateSelectedBlock(QPoint point);

    void newProjectSignel();
    void openProjectSignel();
    void saveProjectSignel();
    void resetProjectSignel();
    void blockTimeSignel(int col, int index, int time);

    void focusLostSignal();
    void focusFoundSignal();
    void imageLoadedPictureSizeSignal(QSize);

    //void setScalePointerPosSignal(int value);
public slots:
    Q_INVOKABLE bool addNewBlockFromLibrary(int col, QString str , DrawElement *element = NULL);
    Q_INVOKABLE bool addNewBlockFromLibrary( QString str , DrawElement *element = NULL);
    Q_INVOKABLE DrawElement* loadFromFile(int col, int ind, QString path = "",bool emit_update = true);
    Q_INVOKABLE DrawElement* loadFromFile( QString path = "");
    void addMsToTimerValue(int ms);
    Q_INVOKABLE void emitNewProject();
    Q_INVOKABLE void emitOpenEffects();
    Q_INVOKABLE void emitHideEffects();

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
    Q_INVOKABLE void drawYellowRectangle(int ,int , int , int );
    Q_INVOKABLE bool updateYellowRectangle(int x, int y, int width, int height);
    Q_INVOKABLE void removeRectangle();
    Q_INVOKABLE bool testIndexs(const int col, const int index);
    Q_INVOKABLE bool blockValid(const int col, const int index);
    Q_INVOKABLE bool blockValid(QPoint point);
private slots:
    void drawYellowRectangle(QRect rect);
};

#endif // LISTCONTROLL_H
