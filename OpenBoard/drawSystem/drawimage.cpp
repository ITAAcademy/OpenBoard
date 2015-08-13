#include "drawImage.h"

DrawImageElm::DrawImageElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("image");
    setTypeId(Element_type::Image);
}

DrawImageElm::~DrawImageElm()
{
    if(textureIndex != 0)
        pDrawWidget->deleteTexture(textureIndex);
}

void DrawImageElm::draw()
{

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
    if((!DrawElement::setDrawWidget(value) && textureIndex != -1 || failedLoad == 0) || (!pDrawWidget->isVisible() || !pDrawWidget->isInit()))
    {
        if(pDrawWidget->isVisible() && pDrawWidget->isInit())
            failedLoad--;
        return 0;
    }
    textureIndex = pDrawWidget->loadTexture(image);
    qDebug() << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWWWWWWWWWWWWWWWWW     " << textureIndex;
}

