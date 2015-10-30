#include "drawvideo.h"
#include "../TimeLine/listcontroll.h"

void DrawVideoElm::start()
{
    qDebug() << "starttttttttttttttttttttttttttttttt";
    DrawElement::start();
}

void DrawVideoElm::stop()
{
    DrawElement::stop();
    decoder.restart(0);
    pDrawWidget->clearAudioList();
}

void DrawVideoElm::pause()
{
    stop();
}


QString DrawVideoElm::getVidePath() const
{
    return videPath;
}

void DrawVideoElm::setVidePath(const QString &value)
{
    videPath = value;
}

long DrawVideoElm::getDuration()
{
    return decoder.getDuration();
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
    int k = 0;

    if(videoValid && bPlay && !bPause && pDrawWidget->getTimeLine()->getPlayTime() > 0 ) /// NEED FIX FOR SECOND BLOCK
    {
        pDrawWidget->clearFrameBuffer(fboWrapper);
        FFmpegHelp::Frame frame = decoder.getNextFrame(pDrawWidget->getTimeLine()->getPlayTime() - startDrawTime);
        //qDebug() << startDrawTime;
        //pDrawWidget->drawQImage(0, 0, frame.videoFrame, z);
        pDrawWidget->drawQImageFromTexture(0, 0, frame.videoFrame, textureIndex, z);
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

bool DrawVideoElm::isVidePathValid()
{
    return  videoValid;
}

bool DrawVideoElm::setVideoFile(QString path)
{
    videoValid = false;

    QFile file(path);
    if(file.exists())
    {
        if(decoder.initFF(path) != 0)
            videPath = path;
        else
            return false;
        videoValid = true;

        setPlayTimeUntilFreeze(decoder.getDuration());
    }
    if(lifeTime <= 1000)
        lifeTime = decoder.getDuration();
}

bool DrawVideoElm::load_add(QDataStream &stream, QString projectPATH, float version)
{
    QDir dir(projectPATH);

    stream >> videPath;
    QFileInfo path(videPath);
    if(path.isRelative())
        videPath = dir.absoluteFilePath(videPath);
//    qDebug() << "videoPATH  " << videPath;
    key = videPath;
    setVideoFile(videPath);
}

bool DrawVideoElm::save_add(QDataStream &stream, QString projectPATH)
{
    QDir dir(projectPATH);

    stream << dir.relativeFilePath(videPath);
}


bool DrawVideoElm::setDrawWidget(OGLWidget *value)
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

