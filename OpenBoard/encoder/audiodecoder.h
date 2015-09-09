#ifndef AUDIODECODER_H
#define AUDIODECODER_H

#include "ffmpeg.h"
#include <QAudioFormat>
#include <QtCore>
#include <QAudioOutput>
#include <QObject>
#include <QBuffer>
#include <QTimer>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

using namespace std;
using namespace ffmpeg;

#define 	AVCODEC_MAX_AUDIO_FRAME_SIZE   192000
#define AVCODEC_MAX_AUDIO_FRAME_SIZE   192000

enum { kSize = 12, kFloat = 1<<(kSize+1), kUnsigned = 1<<(kSize+2), kPlanar = 1<<(kSize+3), kByteOrder = 1<<(kSize+4) };
/*!
 * \brief The SampleFormat enum
 * s8, u16, u24, s24, u32 are not listed in ffmpeg sample format and have not planar format.
 * pcm_s24le will be decoded as s32-24bit in ffmpeg, it's encoded as 32 bits, but raw sample has 24 bits
 */
enum SampleFormat {
    SampleFormat_Unknown = 0,
    SampleFormat_Input = SampleFormat_Unknown,
    SampleFormat_Unsigned8 = 8 |kUnsigned,
    SampleFormat_Signed8 = 8,
    SampleFormat_Unigned16 = 16 | kUnsigned,
    SampleFormat_Signed16 = 16,
    SampleFormat_Unsigned24 = 24 | kUnsigned,
    SampleFormat_Signed24 = 24,
    SampleFormat_Unsigned32 = 32 | kUnsigned,
    SampleFormat_Signed32 = 32,
    SampleFormat_Float = 4*8 | kFloat,
    SampleFormat_Double = 8*8 | kFloat,
    SampleFormat_Unsigned8Planar = SampleFormat_Unsigned8 | kPlanar,
    SampleFormat_Signed16Planar = SampleFormat_Signed16 | kPlanar,
    SampleFormat_Signed32Planar = SampleFormat_Signed32 | kPlanar,
    SampleFormat_FloatPlanar = SampleFormat_Float | kPlanar,
    SampleFormat_DoublePlanar = SampleFormat_Double | kPlanar
};
const qint64 kHz = 1000000LL;

struct sample_fmt_entry{
    AVSampleFormat avfmt;
    SampleFormat fmt;
    const char* name;
};

class AudioDecoder : public QObject
{
    struct AudioBuff{
        QByteArray arr;
        qint64 dts;
    };

    Q_OBJECT
    AVDictionary    *optionsDict = NULL;
    AVFormatContext *formatContext = NULL;
    int             audioStream = -1;
    AVCodecContext  *audioCodecContext;
    AVCodec         *audioCodec;
    AVPacket        audioPacket;
    AVFrame         *audioFrame = NULL;
    AVFrame         *out  = NULL;
    AVResampleContext *audio_cntx;
    SwrContext *swr;
    bool bSwr_init = true;

    int frameFinished;
    unsigned char *med_buffer;

    QAudioFormat format;
    QAudioOutput *audio;
    QBuffer buffer;

    QTimer *m_pullTimer;
    QIODevice *m_output;
    unsigned int buffSize;
    fstream myFile;
    QList<AudioBuff> audioBuffer;

public:
    int64_t duration = 0;
    int64_t baseTime = 0;

    explicit AudioDecoder(QObject * parent, AVFormatContext *formatContext );
    void initAudioDecoder();
    ~AudioDecoder();
    QByteArray nextFrame(qint64 time);
    QByteArray nextFrame(AVPacket &value, qint64 time);
    void setAudioPacket(const AVPacket &value);
    qint64 getDTSFromMS(int ms);
    int getFrameFinished() const;

    int64_t getDuration() const;

public slots:
    void stateChanged(QAudio::State state);
    void pullTimerExpired();

    void seekFile(int ms);
private:
    void initFormat();
    int getSampleFormatSize(AVSampleFormat frm);
    int resample();
    int resample2();
};

#endif // AUDIODECODER_H
