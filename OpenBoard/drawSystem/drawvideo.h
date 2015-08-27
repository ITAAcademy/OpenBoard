#ifndef VIDEO_H
#define VIDEO_H
#pragma once
#include "drawelement.h"
#include "../encoder/ffmpeghelp.h"

class DrawVideoElm  :public DrawElement
{
    Q_OBJECT
    QImage image;
    FFmpegHelp decoder;
    int delta;

public:
    explicit DrawVideoElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawVideoElm();
    void draw();
    void stop();
    void setVideoFile( QString path);
    bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
    bool setDrawWidget(OGLWidget *value);
protected slots:
    void start();

};

#endif // VIDEO_H
