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

    pDrawWidget->drawTexture(x, y, width, height, textureIndex);
}

bool DrawImageElm::load_add(QDataStream &stream)
{

}

bool DrawImageElm::save_add(QDataStream &stream)
{

}

void DrawImageElm::setDrawImage(QImage img)
{
    image = img.convertToFormat(QImage::Format_RGBA8888);
    icon = img;
    textureIndex = pDrawWidget->loadTexture(image);
  //  qDebug() << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWWWWWWWWWWWWWWWWW     " << textureIndex;
}

