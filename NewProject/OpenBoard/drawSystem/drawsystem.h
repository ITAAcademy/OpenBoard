#ifndef DRAWSYSTEM
#define DRAWSYSTEM
#pragma once
#include "drawtext.h"
#include "drawimage.h"
#include "drawbrush.h"

static inline QString mSuffixFromFilter(const QString &filter, QString name)
{
    qDebug() << name;
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
    qDebug() << "format   " << format;

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
