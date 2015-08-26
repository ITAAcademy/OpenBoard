#include "drawImage.h"


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
        if(gif->state() != QMovie::Running)
            gif->start();
        pDrawWidget->drawQImage(x, y, gif->currentImage().scaled(width, height));
    }
    else
        pDrawWidget->drawTexture(x, y, width, height, textureIndex, 0, 1 , 1, z);
}

bool DrawImageElm::load_add(QDataStream &stream)
{

}

bool DrawImageElm::save_add(QDataStream &stream)
{

}

void DrawImageElm::setDrawImage(QImage img)
{
    image = img;
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

