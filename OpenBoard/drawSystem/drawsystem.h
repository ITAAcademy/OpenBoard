#ifndef DRAWSYSTEM
#define DRAWSYSTEM
#pragma once
#include "drawtext.h"
#include "drawimage.h"
#include "drawbrush.h"
#include "drawvideo.h"
#include "drawaudio.h"

static inline QString mSuffixFromFilter(const QString &filter, QString name)
{
    //qDebug() << name;
    if(name.indexOf('.') != -1)
        return name;
    int suffixPos = filter.indexOf(QLatin1String("*."));
    if (suffixPos < 0)
        return QString();
    suffixPos += 2;
    int endPos = filter.indexOf(QLatin1Char(' '), suffixPos + 1);
    if (endPos < 0)
        endPos = filter.indexOf(QLatin1Char(';'), suffixPos + 1);
    if (endPos < 0)
        endPos = filter.indexOf(QLatin1Char(')'), suffixPos + 1);
    return endPos >= 0 ? name + "." + filter.mid(suffixPos, endPos - suffixPos) : QString();
}

static DrawElement *GenerationDrawElement( QString path, OGLWidget *drawWidget = NULL, QObject *parent = NULL )
{
    QFileInfo target(path);
    if(!target.exists())
        return NULL;
    QString format = target.suffix().toLower();
    //qDebug() << "format   " << format;

    /*
     *
     * IMAGE
     */
    if(format == "image")
    {
        DrawImageElm *elm = new DrawImageElm(drawWidget, parent);

        elm->load(path);
        elm->setTypeId(Element_type::Image);
        elm->setKey(target.baseName());
        return (DrawElement*) elm;
    }
    if(format == "jpg" || format == "png" || format == "gif")
    {
        DrawImageElm *elm = new DrawImageElm(drawWidget, parent);
        elm->setDrawImage(QImage(path));
        elm->setLastPath(path);
        if(format == "gif")
        {
            QMovie *movie = new QMovie(path);
            elm->setGif(movie);
            elm->setGIF(true);
        }
        elm->setTypeId(Element_type::Image);
        elm->setKey(target.baseName());
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
        data.replace('\t', "    ");
        elm->setUnParsestring(data, data);
        elm->setTypeId(Element_type::Text);
        elm->setKey(target.baseName());
        return (DrawElement*) elm;
    }
    if(format == "text")
    {
        DrawTextElm *elm = new DrawTextElm(drawWidget, parent);
        elm->load(path);
        elm->setTypeId(Element_type::Text);
        return (DrawElement*) elm;
    }
    if(format == "paint"){
        DrawBrushElm *elm = new DrawBrushElm(drawWidget, parent);
        elm->load(path);
        elm->setTypeId(Element_type::Brushh);
        elm->setKey(target.baseName());
        return (DrawElement*) elm;
    }
    if(format == "avi" || format == "mp4" || format == "mkv")
    {
        DrawVideoElm *elm = new DrawVideoElm(drawWidget, parent);
        elm->setVideoFile(path);
        elm->setTypeId(Element_type::Video);
        elm->setKey(target.baseName());
        qDebug() << "Create video object successful";
        return (DrawElement*) elm;
    }

    if(format == "mp3" || format == "flac" || format == "wav")
    {
        DrawAudioElm *elm = new DrawAudioElm(drawWidget, parent);
        elm->setAudioFile(path);
        elm->setTypeId(Element_type::Audio);
        elm->setKey(target.baseName());
        qDebug() << "Create audio object successful";
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
