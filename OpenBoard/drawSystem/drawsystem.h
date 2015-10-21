#ifndef DRAWSYSTEM
#define DRAWSYSTEM
#pragma once
#include "drawtext.h"
#include "drawimage.h"
#include "drawbrush.h"
#include "drawvideo.h"
#include "drawaudio.h"


static bool isFileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

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
    else
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
        else

            /*
     * TEXT
     */
            if(format == "txt" || format == "doc")
            {
                DrawTextElm *elm = new DrawTextElm(drawWidget, parent);
                QFile file(path);
                file.open(QFile::ReadOnly);
                QString data(file.readAll());
                file.close();


                file.open(QFile::ReadOnly);
                QTextStream instream(&file);
                QString line = instream.readLine();

                data.replace('\t', "    ");
                qDebug() << "AAAAA " << line;
                elm->setUnParsestring(data, data);
                elm->setTypeId(Element_type::Text);
                elm->setKey(target.baseName());
                return (DrawElement*) elm;
            }
            else
                if(format == "text")
                {
                    DrawTextElm *elm = new DrawTextElm(drawWidget, parent);
                    elm->load(path);
                    elm->setTypeId(Element_type::Text);
                    return (DrawElement*) elm;
                }
                else
                    if(format == "paint"){
                        DrawBrushElm *elm = new DrawBrushElm(drawWidget, parent);
                        elm->load(path);
                        elm->setTypeId(Element_type::Brushh);
                        elm->setKey(target.baseName());
                        return (DrawElement*) elm;
                    }
                    else
                        if(format == "avi" || format == "mp4" || format == "mkv")
                        {
                            DrawVideoElm *elm = new DrawVideoElm(drawWidget, parent);
                            if (elm->setVideoFile(path) == false)
                            {
                                delete elm;
                                return NULL;
                            }
                            elm->setTypeId(Element_type::Video);
                            elm->setKey(target.baseName());
                            qDebug() << "Create video object successful";
                            return (DrawElement*) elm;
                        }
                        else
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

static DrawElement *loadDrawElement(QIODevice *device, float version)
{
    DrawElement *draw_element  = new DrawElement(NULL,NULL);

    draw_element->loadTypeId(device);

    Element_type typeId = draw_element->getTypeId();// Element_type::Image;//static_cast<Element_type>(temp_type);
   /* if (typeId >= Element_type::Last_forProtect)
    {
        typeId = (Element_type::Text);
        draw_element->setTypeId(typeId);
    }*/

    if(typeId == Element_type::Text)
    {
        DrawTextElm *elm = new DrawTextElm(NULL,NULL);
        elm->loadRest(device, version);
        delete  draw_element;
        draw_element = (DrawElement*) elm;
    }
    else
        if(typeId == Element_type::Image)
        {
            DrawImageElm *elm = new DrawImageElm(NULL,NULL);
            elm->loadRest(device, version);
            delete  draw_element;
            elm->setDrawImage(elm->getIcon());
            draw_element = (DrawElement*) elm;
            //draw_element->getIcon().save("blaaaaaaaaaaaaaaaaaaaaaa.jpg");

        }
        else
            if(typeId == Element_type::Brushh)
            {
                DrawBrushElm *elm = new DrawBrushElm(NULL,NULL);
                elm->loadRest(device, version);
                delete  draw_element;
                draw_element = (DrawElement*) elm;
            }
            else
                if(typeId == Element_type::Empty)
                {
                    DrawElement *elm = new DrawElement(NULL,NULL);
                    elm->loadRest(device, version);
                    if (version < 2.95)
                    {
                        DrawTextElm *elm_t = new DrawTextElm(NULL,NULL);
                        elm_t->copy(elm);
                        elm_t->setKey(elm->getKey());
                         delete  draw_element;
                        draw_element = (DrawTextElm*) elm_t;
                        delete elm;
                    }
                    else
                    {
                         delete  draw_element;
                        draw_element = (DrawElement*) elm;
                    }

                }
                else
                    if(typeId == Element_type::Video)
                    {
                        DrawVideoElm *elm = new DrawVideoElm(NULL,NULL);
                        elm->loadRest(device, version);
                        //delete  draw_element;
                        // if (elm->isVidePathValid())
                        if (isFileExists(elm->getVidePath()))
                        {
                             delete  draw_element;
                            draw_element = (DrawElement*) elm;
                        }
                        else
                        {
                            /* draw_element = new DrawElement(NULL,NULL);
                            draw_element->copy(elm);
                            draw_element->setKey(elm->getKey());
                            delete elm;*/
                            DrawTextElm *elm_t = new DrawTextElm(NULL,NULL);
                            elm_t->copy(elm);
                            elm_t->setKey(elm->getKey());
                             delete  draw_element;
                            draw_element = (DrawElement *) elm_t;
                            delete elm;
                        }
                    }
                    else
                        if(typeId == Element_type::Audio)
                        {
                            DrawAudioElm *elm = new DrawAudioElm(NULL,NULL);
                            elm->loadRest(device, version);
                            //delete  draw_element;
                            if (isFileExists(elm->getFilePath()))
                            {
                                 delete  draw_element;
                                draw_element = (DrawElement*) elm;
                            }
                            else
                            {
                                /*draw_element = new DrawElement(NULL,NULL);
                                draw_element->copy(elm);
                                draw_element->setKey(elm->getKey());
                                delete elm;*/
                                DrawTextElm *elm_t = new DrawTextElm(NULL,NULL);
                                elm_t->copy(elm);
                                elm_t->setKey(elm->getKey());
                                 delete  draw_element;
                                draw_element = (DrawElement *) elm_t;
                                delete elm;
                            }


                        }
    /*if (version > 3.001)
    {
        int border;
        QDataStream stream(device);
        stream >> border;
        draw_element->setBorder(border);
    }*/
    return draw_element;
    //qDebug() << "load block[i]:  " << i;
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
    bool load_add(QDataStream &stream, float version);
    bool save_add(QDataStream &stream);
};
*/
