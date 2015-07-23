#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include  <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider
    {
    public:
    explicit ImageProvider();
    virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize);
    };

#endif // IMAGEPROVIDER_H
