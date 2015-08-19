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
#include "../openglwidget.h"

enum Element_type { Text,Image,Brushh};

class DrawElement : public QObject
{

    Q_OBJECT

protected:
    FBOWrapper fboWrapper;
    QImage icon;
    QString key;
    int lifeTime = 0;
    int tickTime;
    int delay;
    int startDrawTime;
    int x, y, z, width, height;
    int keyCouter;
    QTimer lifeTimer;
    QElapsedTimer tickTimer;
    char type[50];
    Element_type typeId;
    OGLWidget *pDrawWidget;
    bool bPause;
    bool bPlay;

    QString lastPath;
    virtual void draw();
public:
    FBOWrapper getFBOWrapper();
    explicit DrawElement(OGLWidget *drawWidget, QObject *parent);
    virtual ~DrawElement();
    void paint(); //new use
    bool load(QString path);
    bool save(QString path);
    void clear();
    bool reloadLastDone();

    bool load(QIODevice* device);
    bool loadTypeId(QIODevice* device);
    bool loadRest(QIODevice* device);
 bool save(QIODevice* device);

    QRect getRect();

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
    virtual void setLifeTime(int value);

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
signals:

public slots:


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
