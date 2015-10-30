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
    decoder.restart(0);
    pDrawWidget->clearAudioList();
}

void DrawAudioElm::pause()
{
    qDebug() << "pause";
    DrawElement::pause();
    keyCouter = 0;
    decoder.restart(0);
    pDrawWidget->clearAudioList();
}

DrawAudioElm::DrawAudioElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("audio");
    setTypeId(Element_type::Audio);
    delta = 0;
    decoder.setType(AudioType);

}

long DrawAudioElm::getDuration()
{
    return decoder.getDuration();
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
    if(!init)
        return;

    if(!bPause && pDrawWidget->getTimeLine()->getPlayTime() > 0 ) /// NEED FIX FOR SECOND BLOCK
    {
        //pDrawWidget->clearFrameBuffer(fboWrapper);
        FFmpegHelp::Frame frame = decoder.getNextFrame(pDrawWidget->getTimeLine()->getPlayTime() - startDrawTime);
        //pDrawWidget->drawQImage(0, 0, frame.videoFrame, z);
        //pDrawWidget->drawQImageFromTexture(0, 0, frame.videoFrame, textureIndex, z);
        if(frame.audioFrame.size() > 0)
        {
            pDrawWidget->encoderAddWaitFrame();
            pDrawWidget->addAudioToList(this, frame.audioFrame);
        }

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
        init = true;
    }
    playTimeUntilFreeze = decoder.getDuration();
    if(lifeTime < 1000)
        lifeTime = decoder.getDuration();
}

bool DrawAudioElm::load_add(QDataStream &stream, QString projectPATH, float version)
{
    QDir dir(projectPATH);

    stream >> audioPath;
    QFileInfo path(audioPath);
    if(path.isRelative())
        audioPath = dir.absoluteFilePath(audioPath);
 //   qDebug() << audioPath;
    setAudioFile(audioPath);
}

bool DrawAudioElm::save_add(QDataStream &stream, QString projectPATH)
{
    QDir dir(projectPATH);
    stream << dir.relativeFilePath(audioPath);
}

QString DrawAudioElm::getFilePath()
{
    return audioPath;
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

