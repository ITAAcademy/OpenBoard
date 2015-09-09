#include "drawaudio.h"
#include "../TimeLine/listcontroll.h"

void DrawAudioElm::start()
{
    qDebug() << "starttttttttttttttttttttttttttttttt";
    DrawElement::start();
}

void DrawAudioElm::stop()
{
    DrawElement::stop();
    decoder.restart();
    pDrawWidget->clearAudioList();
}

DrawAudioElm::DrawAudioElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("audio");
    setTypeId(Element_type::Audio);
    bPlay = false;
    delta = 0;

}

DrawAudioElm::~DrawAudioElm()
{

}

void DrawAudioElm::draw()
{
  //  int k = qFloor(pDrawWidget->getTimeLine()->getScalePointerPos()/(1000/40));
   // qDebug () << k << " " << keyCouter;
   // while( k > keyCouter)
    int k = 0;
    pDrawWidget->encoderAddWaitFrame();
    if(bPlay && !bPause && pDrawWidget->getTimeLine()->getPlayTime() > 0 ) /// NEED FIX FOR SECOND BLOCK
    {
        //pDrawWidget->clearFrameBuffer(fboWrapper);
        FFmpegHelp::Frame frame = decoder.getNextFrame(pDrawWidget->getTimeLine()->getPlayTime() - startDrawTime);
        //pDrawWidget->drawQImage(0, 0, frame.videoFrame, z);
        //pDrawWidget->drawQImageFromTexture(0, 0, frame.videoFrame, textureIndex, z);
        pDrawWidget->addAudioToList(this, frame.audioFrame);
   //     qDebug() << "KEY    " << keyCouter;
        keyCouter++;
     /*   double qwe = (double)keyCouter/(decoder.getPTS() + 1);// for test :)
        qDebug() << qwe;
        if(k++ >= qFloor(qwe))
            break;*/
    }

}

void DrawAudioElm::setAudioFile(QString path)
{
    QFile file(path);
    if(file.exists())
    {
        if(decoder.initFF(path) != NULL)
            audioPath = path;

    }
    if(lifeTime < 1000)
        lifeTime = decoder.getDuration();
}

bool DrawAudioElm::load_add(QDataStream &stream)
{
    stream >> audioPath;
    setAudioFile(audioPath);
}

bool DrawAudioElm::save_add(QDataStream &stream)
{
    stream << audioPath;
}


bool DrawAudioElm::setDrawWidget(OGLWidget *value)
{
    DrawElement::setDrawWidget(value);
    if(((!DrawElement::setDrawWidget(value) && textureIndex != 4294967295) || failedLoad < 0) || (!pDrawWidget->isVisible() || !pDrawWidget->isInit()))
    {
        return 0;
    }
    textureIndex = pDrawWidget->loadTexture(QImage(decoder.getSize(), QImage::Format_ARGB32_Premultiplied));
    if(textureIndex == 4294967295)
        failedLoad--;
}

