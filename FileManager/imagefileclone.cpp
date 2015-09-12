#include "fileimageclone.h"

ImageClone::ImageClone(QQuickImageProvider *provider) :QQuickImageProvider(QQuickImageProvider::Image)
{
    pro = provider;
}

QImage ImageClone::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
   // if(pro != NULL)
   return pro->requestImage(id,size,requestedSize);
}

ImageClone::~ImageClone()
{

}

