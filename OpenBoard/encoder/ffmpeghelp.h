#ifndef FFMPEGHELP_H
#define FFMPEGHELP_H

#include <QObject>
#include "videodecoder.h"
#include "audiodecoder.h"

#include <QtCore>

class FFmpegHelp : public QObject
{
    Q_OBJECT

    QThread videoThread;
    QThread audioThread;
    qint64 lastDts = 0;

    VideoDecoder *vDecoder = NULL;
    AudioDecoder *aDecoder = NULL;
    AVFormatContext *formatContext = NULL;
    QVector <AVPacket> bufferPacket;

    QList <QByteArray> audioBuffer;
public:
    struct Frame{
        QImage videoFrame;
        QByteArray audioFrame;
        Frame( QImage img, QByteArray arr)
        {
            videoFrame = img;
            audioFrame = arr;
        }
    };

    explicit FFmpegHelp(QObject *parent = 0);

    Frame getNextFrame(qint64 time);
    void restart();
    long int getDuration();
    long int getPTS();

public slots:
    Q_INVOKABLE int initFF(QString path);

private:
    AVFormatContext *openVideoStream(QString path);

signals:

public slots:
    QSize getSize();
};

#endif // FFMPEGHELP_H
