#include "drawImage.h"
#include "../TimeLine/listcontroll.h"

bool DrawImageElm::isBGIF() const
{
    return bGIF;
}

void DrawImageElm::setGIF(bool value)
{
    bGIF = value;
}

QMovie *DrawImageElm::getGif() const
{
    return gif;
}

void DrawImageElm::setGif(QMovie *value)
{
    gif = value;
}
DrawImageElm::DrawImageElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("image");
    setTypeId(Element_type::Image);
    if(gif != NULL)
        delete gif;
}

DrawImageElm::~DrawImageElm()
{
    if(textureIndex != 0)
        pDrawWidget->deleteTexture(textureIndex);
}

void DrawImageElm::draw()
{

    if(bGIF)
    {
        pDrawWidget->clearFrameBuffer(fboWrapper);
        if(keyCouter==0)
        {

           qDebug() << "RESET GIF";
                gif->stop();
                gif->start();
        }
        if (bPause){
                gif->setPaused(true);
        }
        else    gif->setPaused(false);
        pDrawWidget->drawQImage(0, 0, gif->currentImage().scaled(pDrawWidget->getWax(), pDrawWidget->getWay()));
    }
    else
        pDrawWidget->drawTexture(0, 0, pDrawWidget->getWax(), pDrawWidget->getWay(), textureIndex, 0, 1 , 1, z);
     keyCouter++;

}

bool DrawImageElm::load_add(QDataStream &stream)
{
    stream >> bGIF >> lastPath;
qDebug() << "qwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" + lastPath;
    if(bGIF)
    {

        gif = new QMovie(lastPath);
        if(!gif->isValid())
            bGIF = false;
    }
    qDebug() << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" + bGIF;
}

bool DrawImageElm::save_add(QDataStream &stream)
{
    stream << bGIF << lastPath;
    qDebug() << "qwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" + lastPath;
    if(bGIF)
    {
        save_image(stream, lastPath);
    }

}

void DrawImageElm::setDrawImage(QImage img)
{
    image = img;
//    new QMovie()
    icon = img;
    //image.save("12334243534534534.png");
    if(pDrawWidget != NULL && pDrawWidget->isVisible())
         textureIndex = pDrawWidget->loadTexture(image);


}

bool DrawImageElm::setDrawWidget(OGLWidget *value)
{
    if(((!DrawElement::setDrawWidget(value) && textureIndex != 4294967295) || failedLoad < 0) || (!pDrawWidget->isVisible() || !pDrawWidget->isInit()))
    {
        return 0;
    }
    textureIndex = pDrawWidget->loadTexture(image);
    if(textureIndex == 4294967295)
        failedLoad--;
    //qDebug() << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWWWWWWWWWWWWWWWWW     " << textureIndex;
}

