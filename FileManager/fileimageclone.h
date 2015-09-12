#ifndef FILEIMAGECLONE_H
#define FILEIMAGECLONE_H
#include <QQuickImageProvider>
class ImageClone : public QQuickImageProvider
{
    QQuickImageProvider *pro;
public:
    ImageClone(QQuickImageProvider *provider);
    ~ImageClone();
    public slots:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // IMAGECLONE_H
