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
    int lifeTime;
    int tickTime;
    int startDrawTime;
    int x, y, z, width, height;
    int keyCouter;
    QTimer lifeTimer;
    QElapsedTimer tickTimer;

    OGLWidget *pDrawWidget;
    bool bPause;
public:
    explicit DrawElement( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawElement();

    virtual void draw();

    void setPosition(QPoint pos);
    void setPosition( int x, int y);

    void setSize( QSize pos );
    void setSize( int width, int height);

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

    virtual int getTickTime() const;
    virtual void setTickTime(int value);

signals:

public slots:

private slots:
    void pause();
    void stop();
    void start();

};

#endif // DrawElement_H
