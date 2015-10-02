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
    GLuint textureIndex = -1;
    int failedLoad = 10;
    QString videPath;
    bool videoValid = false;
public:
   bool isVidePathValid();
    explicit DrawVideoElm( OGLWidget *drawWidget, QObject *parent = 0);
    ~DrawVideoElm();
    void draw();

    void setVideoFile( QString path);
    bool load_add(QDataStream &stream, float version);
    bool save_add(QDataStream &stream);
    bool setDrawWidget(OGLWidget *value);
    QString getVidePath() const;
    void setVidePath(const QString &value);

public slots:
    void start();
    void stop();

};

#endif // VIDEO_H
