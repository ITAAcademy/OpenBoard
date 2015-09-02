#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include "ffmpeg.h"
#include <QStandardPaths>
#include <QMutexLocker>
#include <QMutex>
#include <QTimer>
#include <QThread>
#include <QImage>
#include <QtCore>

using namespace ffmpeg;

class VideoDecoder : public QObject
{
    Q_OBJECT
    AVFormatContext *videoFormatContext = NULL;
    int             i, videoStream;
    AVCodecContext  *videoCodecContext = NULL;
    AVCodec         *videoCodec = NULL;
    AVFrame         *videoFrame = NULL;
    AVFrame         *videoFrameRGB = NULL;
    AVPacket        videoPacket;
    int             frameFinished;
    int             numBytes;
    uint8_t         *videoBuffer = NULL;

    AVDictionary    *optionsDict = NULL;
    struct SwsContext      *sws_ctx = NULL;

    int pts;



public:
    bool init;
    int64_t duration;
    int64_t baseTime;
public:
    explicit VideoDecoder(QObject * parent, AVFormatContext *formatContext);

    ~VideoDecoder();
    int getVideoLengthMs();
    QImage getNextFrame(qint64 time);
    QImage getNextFrame(AVPacket &videoPacket, qint64 time);
    AVCodecContext *getVideoCodecContext() const;
    void seekFile(int ms);

    int getFrameFinished() const;
    QSize getSize();

public slots:
    qint64 getDTSFromMS(int ms);
private:
    int initVideoDecoder();
};

#endif // VIDEODECODER_H
