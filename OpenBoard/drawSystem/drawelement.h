#ifndef DrawElement_H
#define DrawElement_H
//#pragma once
#include <QObject>
#include <QImage>
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <qvector.h>
#include <shadereffect.h>
#include "../openglwidget.h"
//#include "../TimeLine/group.h"

class Group;

enum Element_type { Text, Video, Audio, Image,Brushh,Empty};

struct AnimStateTime{
    int state; //no anim = 0,begin = 1,end = 2, begin & end =3
    int time;
    AnimStateTime(int a,int b)
    {
        state = a;
        time = b;
    }
    AnimStateTime()
    {
        state = 0;
        time = 10;
    }
};


class DrawElement : public QObject
{

    Q_OBJECT

protected:

    QString block_border_color = "white";
    Group *group_wich_el_belong = NULL;
    int blockIndex = -1;
    int blockColumn = -1;
    AnimStateTime anim_state_time;
    FBOWrapper fboWrapper;
    QImage icon;
    QString key;
    QVector<ShaderEffect> effects;
    int lifeTime = 0;
    int tickTime;
    int delay;
    int startDrawTime;
    int x, y, z, width, height;
    int keyCouter;
    bool aspectRatio = false;
    QTimer lifeTimer;
    QElapsedTimer tickTimer;
    char type[50];
    Element_type typeId;
    OGLWidget *pDrawWidget;
    bool bPause;
    bool bPlay;
    bool effectChange = false;

    QString lastPath;
    virtual void draw();
public:
    void setAnimStateTime(AnimStateTime);
    void setAnimStateTime(int , int);
    void setAnimStateTime(QPoint);
    void setAnimState(int);
    void setAnimTime(int);
    QPoint getAnimStateTimePoint();
    AnimStateTime getAnimStateTime();

    FBOWrapper getFBOWrapper();
    explicit DrawElement(OGLWidget *drawWidget, QObject *parent);
    virtual ~DrawElement();
    void paint(); //new use
    bool load(QString path);
    bool save(QString path);
    void clear();
    bool reloadLastDone();

    void setLastPath(QString path);
    bool load(QIODevice* device);
    bool loadTypeId(QIODevice* device);
    bool loadRest(QIODevice* device);
 bool save(QIODevice* device);

    QRect getRect();

    DrawElement* getCopy(QObject parentamana);

    void setPosition(QPoint pos);
    void setPosition( int x, int y);
    void setDelay(int d);
    void setSize( QSize pos );
    void setSize( int width, int height);
    QSize getSize();

    void setRect (QRect rect);
    void setRect ( int x, int y, int width, int height);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getZ() const;
    void setZ(int value);

    virtual int getLifeTime() const;
    virtual void setLifeTime(int value, bool feedBack = false);

    int getStartDrawTime() const;
    void setStartDraw(int value);

    QImage getIcon() const;
    void setIcon(const QImage &value);

    bool getPause() const;
    void setPause(bool value);

    void setType( const char name[]);
    QString getType();

    void setTypeId( Element_type);
    Element_type getTypeId();

    virtual int getTickTime() const;
    virtual void setTickTime(int value);

    OGLWidget *getDrawWidget() const;
    virtual bool setDrawWidget(OGLWidget *value);

    QString getKey() const;
    void setKey(const QString &value);

    void copy(DrawElement *elm);
    setFBOWrapper(FBOWrapper wrapper);
    bool save_image(QDataStream &stream, QString filePath,QImage::Format format = QImage::Format_ARGB32);
    int getBlockIndex() const;
    void setBlockIndex(int value);

    int getBlockColumn() const;
    void setBlockColumn(int value);

    Group *getGroupWichElBelong() const;
    void setGroupWichElBelong(Group *value);

    QString getBlockBorderColor() const;
    void setBlockBorderColor(const QString &value);

signals:
    void borderColorChangedSignal(int col, int ind ,QString color);
    void sizeChangedSignal(int col, int ind, int newSize);

public slots:


    QMovie *load_Movie(QDataStream &stream);
protected slots:
    void pause();
    void stop();
    void start();
    void restart();

    bool save_image(QDataStream &stream, QImage img);
    QImage load_image(QDataStream &stream);

protected:
    virtual bool load_add(QDataStream &stream);
    virtual bool save_add(QDataStream &stream);


};

#endif // DrawElement_H
