#ifndef FFMPEGHELP_H
#define FFMPEGHELP_H

#include <QObject>
#include "videodecoder.h"
#include "audiodecoder.h"

#include <QtCore>
enum DecoderType{
    VideoType = 1 , AudioType = 2, VideoAudioType = 3
};

class FFmpegHelp : public QObject
{
private:
    Q_OBJECT

    QImage vNext;
    QByteArray aNext;

    QThread videoThread;
    QThread audioThread;
    qint64 lastDts = 0;
    DecoderType type;

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
    ~FFmpegHelp();

    Frame getNextFrame(qint64 time);
    void restart(int64_t startTime = 0);
    long int getDuration();
    long int getPTS();

    DecoderType getType() const;
    void setType(const DecoderType &value);

public slots:
    Q_INVOKABLE int initFF(QString path);

private:
    AVFormatContext *openVideoStream(QString path);

signals:

public slots:
    QSize getSize();
};

#endif // FFMPEGHELP_H
