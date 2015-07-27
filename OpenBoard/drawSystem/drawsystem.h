#ifndef DRAWSYSTEM
#define DRAWSYSTEM
#pragma once
#include "drawtext.h"
#include "drawimage.h"


static DrawElement *GenerationDrawElement( QString path, OGLWidget *drawWidget = NULL, QObject *parent = NULL )
{
    QFileInfo target(path);
    if(!target.exists())
        return NULL;
    QString format = target.suffix();
    qDebug() << "format   " << format;

    /*
     *
     * IMAGE
     */
    if(format == "image")
    {
        DrawImageElm *elm = new DrawImageElm(drawWidget, parent);
        elm->load(path);
        return (DrawElement*) elm;
    }
    if(format == "jpg" || format == "png" || format == "gif")
    {
        DrawImageElm *elm = new DrawImageElm(drawWidget, parent);
        elm->setDrawImage(QImage(path));
        return (DrawElement*) elm;
    }


    /*
     * TEXT
     */
    if(format == "txt" || format == "doc")
    {
        DrawTextElm *elm = new DrawTextElm(drawWidget, parent);
        QFile file(path);
        file.open(QFile::ReadOnly);
        QString data(file.readAll());
        elm->setUnParsestring(data);
        return (DrawElement*) elm;
    }
    if(format == "text")
    {
        DrawTextElm *elm = new DrawTextElm(drawWidget, parent);
        elm->load(path);
        return (DrawElement*) elm;
    }
    return NULL;
}

#endif // DRAWSYSTEM

/*
class drawImage :public DrawElement
{
    Q_OBJECT
public:
    explicit drawImage( OGLWidget *drawWidget, QObject *parent = 0);
    ~drawImage();
    void draw();
    bool load_add(QDataStream &stream);
    bool save_add(QDataStream &stream);
};
*/
