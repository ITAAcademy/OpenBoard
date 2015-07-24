#include "imageprovider.h"
#include <qDebug>

ImageProvider::ImageProvider(ImageType type, Flags flags) :
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

ImageProvider::~ImageProvider()
{

}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

   // QUrl url("http://lorempixel.com/" + id);
    //QNetworkReply* reply = manager->get(QNetworkRequest(url));
   // QEventLoop eventLoop;
   // QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
   // eventLoop.exec();
 //   if (reply->error() != QNetworkReply::NoError)
 //       return QImage();
    QImage image("F:/prohect/TimeLine/0.png");

    image.save("kaka.png");
            //= QImage::fromData(reply->readAll());
    /*size->setWidth(image.width());
    size->setHeight(image.height());*/
    return image;
}


QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
        int width = 100;
        int height = 50;
        if (size)
            *size = QSize(width, height);
        QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                       requestedSize.height() > 0 ? requestedSize.height() : height);
        pixmap.fill(QColor(id).rgba());

        return pixmap;
    }
