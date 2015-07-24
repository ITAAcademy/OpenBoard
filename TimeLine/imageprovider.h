#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include  <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider(ImageType type , Flags flags = 0);
    ImageProvider(): QQuickImageProvider(QQuickImageProvider::Image) { }
    ~ImageProvider();
    QImage requestImage(const QString & id, QSize * size, const QSize & requestedSize);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

protected:

};
#endif // IMAGEPROVIDER_H
