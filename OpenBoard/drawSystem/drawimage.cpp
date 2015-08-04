#include "drawImage.h"

DrawImageElm::DrawImageElm(OGLWidget *drawWidget, QObject *parent) : DrawElement(drawWidget, parent)
{
    setType("image");
}

DrawImageElm::~DrawImageElm()
{

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
    if(pDrawWidget != NULL)
        if(textureIndex > 1)
            textureIndex = pDrawWidget->loadTexture(image, textureIndex , true);
        else
            textureIndex = pDrawWidget->loadTexture(image);

}

bool DrawImageElm::setDrawWidget(OGLWidget *value)
{
    if(!DrawElement::setDrawWidget(value))
        return 0;
    if(textureIndex > 1) // 0 is backgraund in default
        textureIndex = pDrawWidget->loadTexture(image, textureIndex , true);
    else
        textureIndex = pDrawWidget->loadTexture(image);
    //// qDebug() << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWWWWWWWWWWWWWWWWW     " << textureIndex;
}

