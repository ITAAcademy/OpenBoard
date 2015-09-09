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
    gif->setCacheMode(QMovie::CacheAll);
}
DrawImageElm::DrawImageElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("image");
    setTypeId(Element_type::Image);
    if(gif != NULL)
        delete gif;
   /* ShaderEffect alphaEffect(OGLWidget::ALPHA_SHADER);
    ShaderEffect alphaEffect2(OGLWidget::ALPHA_SHADER);
    ShaderEffect spiralEffect(OGLWidget::SPIRAL_SHADER);
    alphaEffect.setEffectTimeHowLong(500);
    alphaEffect.setStartTimeMS(0);
    //alphaEffect.setReverse(true);
    alphaEffect2.setEffectTimeHowLong(500);
    alphaEffect2.setReverse(true);
    alphaEffect2.setStartTimeMS(500);
    alphaEffect2.setAnchorToEnd(true);
    //alphaEffect.setAnchorToEnd(true);
    //alphaEffect2.setReverse(false);
 //   spiralEffect.setEffectTimeHowLong(1000);

    //qDebug() << "alpha effect created";

     effects.push_back(alphaEffect); //ADD DEFAULT EFFECT
     effects.push_back(alphaEffect2); //ADD DEFAULT EFFECT
     //effects.push_back(alphaEffect2); //ADD DEFAULT EFFECT
     //effects.push_back(spiralEffect); //ADD DEFAULT EFFECT
     */

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
        //pDrawWidget->bindBuffer(fboWrapper.frameBuffer);
        if(keyCouter==0)
                {

                   qDebug() << "RESET GIF";
                        gif->stop();
                        gif->start();

    int playTime = pDrawWidget->getTimeLine()->getPlayTime();
             int keyFrame = (playTime-startDrawTime)*gif->frameCount()/lifeTime;
gif->jumpToFrame(keyFrame);
              gif->start();

        }
        if (bPause){
                gif->setPaused(true);
        }
        else    gif->setPaused(false);
        pDrawWidget->drawQImageFromTexture(0, 0, gif->currentImage(),textureIndex,z);
    }
    else
    {
        pDrawWidget->clearFrameBuffer(fboWrapper);
        pDrawWidget->drawTexture(0, 0, pDrawWidget->getWax(), pDrawWidget->getWay(), textureIndex, 0, 1 , 1, z);
    }
     keyCouter++;

}

bool DrawImageElm::load_add(QDataStream &stream)
{
    stream >> bGIF ;
    qDebug() << "DrawImageElm lastPath:" + lastPath;

    if(bGIF)
    {  
        stream >> lastPath;
        gif = new QMovie(lastPath);
        if(!gif->isValid())
            bGIF = false;
    }
    qDebug() << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" + bGIF;
}

bool DrawImageElm::save_add(QDataStream &stream)
{
    stream << bGIF;
    qDebug() << "DrawImageElm lastPath:" + lastPath;

    if(bGIF)
    {   
        stream << lastPath;
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

