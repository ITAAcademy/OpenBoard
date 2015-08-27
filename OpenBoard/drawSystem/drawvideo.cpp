#include "drawvideo.h"
#include "../TimeLine/listcontroll.h"

void DrawVideoElm::start()
{
    qDebug() << "starttttttttttttttttttttttttttttttt";
    DrawElement::start();
    decoder.restart();
}

DrawVideoElm::DrawVideoElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("video");
    setTypeId(Element_type::Video);
    bPlay = false;
    delta = 0;

}

DrawVideoElm::~DrawVideoElm()
{

}

void DrawVideoElm::draw()
{
  //  int k = qFloor(pDrawWidget->getTimeLine()->getScalePointerPos()/(1000/40));
   // qDebug () << k << " " << keyCouter;
   // while( k > keyCouter)
    if((40 + delta) <= 0)
        delta = -1;

    int k = qCeil(pDrawWidget->getTimeLine()->getScalePointerPos()/((40 + delta)));
    if(bPlay && keyCouter < k) /// NEED FIX FOR SECOND BLOCK
    {
        pDrawWidget->clearFrameBuffer(fboWrapper);
        pDrawWidget->drawQImage(0, 0, decoder.getNextFrame());
        qDebug() << keyCouter;
        keyCouter++;
    }
    if(keyCouter > decoder.getPTS())
        delta--;
    else
        delta++;

}

void DrawVideoElm::setVideoFile(QString path)
{
    QFile file(path);
    if(file.exists())
    {
        if(decoder.initFF(path) != NULL)
            lastPath = path;

    }
  //  lifeTime = decoder.getDuration();
}

bool DrawVideoElm::load_add(QDataStream &stream)
{

}

bool DrawVideoElm::save_add(QDataStream &stream)
{

}


bool DrawVideoElm::setDrawWidget(OGLWidget *value)
{
    DrawElement::setDrawWidget(value);
}

