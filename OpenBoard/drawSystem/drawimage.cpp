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
    qDebug() << "delete texture begin with index:"<<textureIndex;
    if(textureIndex != -1)
        pDrawWidget->deleteTexture(textureIndex);
    qDebug() << "delete texture end";
    if(gif != NULL)
        delete gif;
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
            int keyFrame = (playTime-startDrawTime)*gif->frameCount()/playTimeUntilFreeze;
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

bool DrawImageElm::load_add(QDataStream &stream, QString projectPATH, float version)
{
    stream >> bGIF ;
    // qDebug() << "DrawImageElm lastPath:" + lastPath;

    if(bGIF)
    {
        stream >> lastPath;
        QDir dir(projectPATH);
        QFileInfo path(lastPath);
        if(path.isRelative())
            lastPath = dir.absoluteFilePath(lastPath);

        gif = new QMovie(lastPath);
        if(!gif->isValid())
            bGIF = false;
    }
    // qDebug() << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" + bGIF;
}

bool DrawImageElm::save_add(QDataStream &stream, QString projectPATH)
{
    stream << bGIF;
    //qDebug() << "DrawImageElm lastPath:" + lastPath;

    if(bGIF)
    {
        QDir dir(projectPATH);

        stream << dir.relativeFilePath(lastPath);
    }

}



void DrawImageElm::setDrawImage(QImage img,bool set_bk)
{
    image = img;
    //image = QImage("E:/картинки/Фото0051.jpg");
    //    new QMovie()
    if ( set_bk)
        img_backup = img;

    icon = image;
    //image.save("12334243534534534.png");
    if(pDrawWidget != NULL && pDrawWidget->isVisible())
        textureIndex = pDrawWidget->loadTexture(image);


}

void DrawImageElm::setBorder(float value)
{
    if (value <= 0.0000001)
    {
        border = 0;
        image = img_backup;
        icon = image;
    }
    border = value;
    if (border > 0.001)
    {
        int img_width = img_backup.width();
        int img_height = img_backup.height();
        float scale_x = (float) this->width/img_width;
        float scale_y = (float) this->height/img_height;
       // qDebug() << "KKKKKKKKKKKKKKKK  "<<scale_x << " " << scale_y;

       /* if (abs(scale_x - scale_y) < 0.0001)
            scale_x = scale_y = 1;
        else
            if (scale_x < scale_y)
            {
                scale_x /= scale_y;
                scale_y = 1;
            }
        else
            {
                scale_y /= scale_x;
                scale_x = 1;
            }*/

        //QPixmap newPixmap = QPixmap::fromImage(image,0);//(img_width - border, img_height - border); // создаём картинку
        /*  QPixmap  px = QPixmap::fromImage(img_backup,0).scaled(QSize(img_width*(1-  border),img_height*(1 - border)),  Qt::KeepAspectRatio);

        QPixmap px_out = QPixmap::fromImage(image,0);
        QPixmap bac(img_width,img_height);
        QPainter painter(&bac);
        painter.drawPixmap(0,0, px_out);
        painter.drawPixmap((img_width -px.width())/2, (img_height - px.height())/2, px);
        painter.end();*/
        QPixmap px_out = QPixmap::fromImage(img_backup,0);

        QPixmap bac(img_width,img_height);
        QPainter painter(&bac);
        float ax = img_width * border/scale_x;
        float ay = img_height* border/scale_y;
        //painter.drawPixmap(0,0,ax, ay,px_out, 0,0, img_width * border,img_height * border   );
        painter.drawPixmap(0,0, px_out);
        painter.drawPixmap(0,0,ax, ay, px_out,
                           0,0, img_width * border,img_height * border   ); //left top ++
        painter.drawPixmap(img_width - ax,0,img_width, ay, px_out,
                           img_width * (1 - border),0, img_width*scale_x ,img_height * border   ); //right top ++

        painter.drawPixmap(0,img_height - ay,ax, img_height, px_out,
                           0,img_height * scale_y, img_width * border,img_height   ); //left bottom

         painter.drawPixmap(img_width - ax ,img_height - ay, img_width , img_height, px_out,
                            0,0, img_width * scale_x,img_height * border   ); //right bottom
       // painter.drawPixmap(0,ay, px_out, 0,0, img_width * border,img_height * border   );
       // painter.drawPixmap(0,img_width - ay ,ax, img_width ,px_out, 0,0, img_width * border,img_height *(1 - border)  );

        painter.end();

        setDrawImage(bac.toImage(),false);
    }
}

void DrawImageElm::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
   // setBorder(0.2);

}

void DrawImageElm::setSize(QSize pos)
{
    setSize(pos.width(),pos.height());
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

