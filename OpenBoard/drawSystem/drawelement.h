#ifndef DrawElement_H
#define DrawElement_H
#pragma once
#include <QObject>
#include <QImage>
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QPoint>
#include <QSize>
#include <QRect>
#include "../openglwidget.h"

class DrawElement : public QObject
{

    Q_OBJECT

protected:
    QImage icon;
    QString key;
    int lifeTime;
    int tickTime;
    int startDrawTime;
    int x, y, z, width, height;
    int keyCouter;
    QTimer lifeTimer;
    QElapsedTimer tickTimer;
    char type[50];
    OGLWidget *pDrawWidget;
    bool bPause;

    QString lastPath;
public:
    explicit DrawElement( OGLWidget *drawWidget, QObject *parent = 0);
    virtual ~DrawElement();
    virtual void draw();
    bool load(QString path);
    bool save(QString path);
    bool reloadLastDone();

    QRect getRect();












    void setPosition(QPoint pos);
    void setPosition( int x, int y);

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

    virtual int getTickTime() const;
    virtual void setTickTime(int value);

    OGLWidget *getDrawWidget() const;
    virtual void setDrawWidget(OGLWidget *value);

    QString getKey() const;
    void setKey(const QString &value);

signals:

public slots:


private slots:
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
