#include "videodecoder.h"


AVCodecContext *VideoDecoder::getVideoCodecContext() const
{
    void *temp = malloc(sizeof(AVCodecContext));
    memcpy(temp, videoCodecContext, sizeof(AVCodecContext) );
    //qDebug() << "CH" << videoCodecContext->bit_rate;
    return (AVCodecContext*)temp;
}

bool VideoDecoder::seekFrame(int64_t frame)
{

    qDebug("\t avformat_seek_file\n");
    if(avformat_seek_file(videoFormatContext, videoStream, 0, frame, frame, AVSEEK_FLAG_FRAME)<0)
        return false;

    avcodec_flush_buffers(videoFormatContext->streams[videoStream]->codec);

    return true;
}

void VideoDecoder::seekFile(int ms)
{
    qDebug() << "seekFile();";
    // avformat_seek_file(formatContext, audioStream,INT64_MIN, ms, INT64_MAX, 0 );
    if(!init)
        return;

    int64_t desiredFrameNumber = av_rescale(ms, videoFormatContext->streams[videoStream]->time_base.den, videoFormatContext->streams[videoStream]->time_base.num);
    desiredFrameNumber/=1000;

    seekFrame(desiredFrameNumber);
    baseTime = 0;
}


int VideoDecoder::getFrameFinished() const
{
    return frameFinished;
}

QSize VideoDecoder::getSize()
{
    if(init)
        return QSize(videoCodecContext->width, videoCodecContext->height);
    else
        return QSize(640, 480);
}
VideoDecoder::VideoDecoder(QObject *parent, AVFormatContext *formatContext) :QObject(parent)
{
    videoFormatContext = formatContext;
    initVideoDecoder();

}

VideoDecoder::~VideoDecoder()
{
    av_free(videoBuffer);
    av_free(videoFrameRGB);

    // Free the YUV frame
    av_free(videoFrame);

    // Close the codec
    avcodec_close(videoCodecContext);

    // Close the video file
    avformat_close_input(&videoFormatContext);
}

int VideoDecoder::getVideoLengthMs()
{
    int secs = videoFormatContext->duration / AV_TIME_BASE;
    int us = videoFormatContext->duration % AV_TIME_BASE;
    int l = secs*1000 + us/1000;

    //dumpFormat(pFormatCtx,videoStream,"test video",0);
    return l;
}

int VideoDecoder::initVideoDecoder()
{
    // Find the first video stream
    videoStream=-1;
    for(i=0; i<videoFormatContext->nb_streams; i++)
        if(videoFormatContext->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
            videoStream=i;
            break;
        }
    if(videoStream==-1)
    {
        qDebug() << "Didn't find a video stream";
        return -1; // Didn't find a video stream
    }

    // Get a pointer to the codec context for the video stream
    videoCodecContext=videoFormatContext->streams[videoStream]->codec;
    //videoCodecContext->codec->

    //      avcodec_alloc_context3(avcodec_find_decoder_by_name());
    // Find the decoder for the video stream
    //qDebug() << "Codec ID   " << videoCodecContext->codec_id;
    videoCodec=avcodec_find_decoder(videoCodecContext->codec_id);
    if(videoCodec==NULL) {
        qDebug() << "Codec not found";
        return -1; // Codec not found
    }
    else
        //qDebug() << videoCodecContext->codec_name;
        // Open codec
        if(avcodec_open2(videoCodecContext, videoCodec, &optionsDict)<0)
        {
            qDebug() << "Could not open codec";
            return -1; // Could not open codec
        }

    // Allocate video frame
    videoFrame=av_frame_alloc();

    // Allocate an AVFrame structure
    videoFrameRGB=av_frame_alloc();
    if(videoFrameRGB==NULL){
        qDebug() << "Allocate an AVFrame structure";
        return -1;
    }

    // Determine required buffer size and allocate buffer
    numBytes=avpicture_get_size(AV_PIX_FMT_BGR32, videoCodecContext->width,
                                videoCodecContext->height);
    videoBuffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

    sws_ctx = sws_getCachedContext(sws_ctx,videoCodecContext->width, videoCodecContext->height, videoCodecContext->pix_fmt, videoCodecContext->width, videoCodecContext->height, AV_PIX_FMT_BGR32, SWS_BICUBIC, NULL, NULL, NULL);
    /*  sws_getContext
      (
          pCodecCtx->width,
          pCodecCtx->height,
          pCodecCtx->pix_fmt,
          pCodecCtx->width,
          pCodecCtx->height,
          AV_PIX_FMT_BGR32,
          SWS_BILINEAR,
          NULL,
          NULL,
          NULL
      );
*/
    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
    avpicture_fill((AVPicture *)videoFrameRGB, videoBuffer, AV_PIX_FMT_BGR32,
                   videoCodecContext->width, videoCodecContext->height);

    // Read frames and save first five frames to disk
    pts = videoFormatContext->streams[videoStream]->avg_frame_rate.num/100000;
    if(pts < 25)
        pts = 25;
    qDebug() << "INFO:  " << "FPS   " <<pts;
    duration = videoFormatContext->streams[videoStream]->nb_frames/pts;
    qDebug() << "INFO:  " << "DURATION  " << duration;
    baseTime = av_q2d(videoFormatContext->streams[videoStream]->time_base);
    qDebug() << "INFO:  " << "BASE_TIME " << baseTime;
    i=0;
    init = true;

    return pts;

}

QImage VideoDecoder::getNextFrame(qint64 time)
{
    //if(init)
    {
        //   //qDebug() << "out" << i << "\n";
        if(av_read_frame(videoFormatContext, &videoPacket)>=0) {
            //  qDebug() << "PTS" << videoPacket.pts;
            //qDebug() << "DTS" << videoPacket.dts;
            QImage res =  getNextFrame(videoPacket, time);
            //av_free_packet(&videoPacket);
            return res;
        }
        else return QImage(10,10,QImage::Format_RGB888);
        //  imggg.save("F:/kaka" + QString::number(i) + ".png");
        //return imggg;
    }
    // else return QImage(800,600,QImage::Format_RGB888);
}

QImage VideoDecoder::getNextFrame(AVPacket &videoPacket, qint64 time)
{
    // Is this a packet from the video stream?
    //    //qDebug() << "SIZE   " << videoPacket.size;
    // qDebug() << "PTS" << videoPacket.pts;
    // qDebug() << "DTS" << videoPacket.dts;
    if(!init)
    {
        //qDebug() << "NO_VIDEO_DECODER";
        return QImage();
    }

    int len;
    int finish = 0;
    frameFinished = false;
    if(videoPacket.stream_index == videoStream) {
        //         //qDebug() << "stream index   " << videoPacket.stream_index;
        // Decode video frame truble
        while (videoPacket.size > 0)
        {
            int len = avcodec_decode_video2(videoCodecContext, videoFrame, &finish, &videoPacket);
            //  qDebug() << "DTS" << videoFrame->best_effort_timestamp;


            // Did we get a video frame?
            if(finish) {
                // Convert the image from its native format to RGB
                sws_scale
                        (
                            sws_ctx,
                            (uint8_t const * const *)videoFrame->data,
                            videoFrame->linesize,
                            0,
                            videoCodecContext->height,
                            videoFrameRGB->data,
                            videoFrameRGB->linesize
                            );

                //baseTime =  videoFrame->best_effort_timestamp;

                //     qDebug() << "TIME   " << time << "  " << (getDTSFromMS(time) - stream->start_time) * av_q2d(stream->time_base)*1000;

            }
            videoPacket.size -= len;
            videoPacket.data += len;
        }

        AVStream *stream = videoFormatContext->streams[videoStream];
        qint64 seconds= (videoPacket.dts - stream->start_time) * av_q2d(stream->time_base)*1000;
        //  qDebug() << "V_SECONDS    " << seconds;
        baseTime = seconds;
        /*if(time <= seconds)
            frameFinished = true;*/
    }


    //timer.
    return QImage((uchar*)videoFrameRGB->data[0],videoCodecContext->width, videoCodecContext->height, QImage::Format_RGBA8888_Premultiplied);

}

qint64 VideoDecoder::getDTSFromMS(int ms)
{
    AVStream *stream = videoFormatContext->streams[videoStream];
    //double seconds = (audioPacket.dts - stream->start_time) * av_q2d(stream->time_base)*1000;
    return (qint64) qCeil((double)(ms/(av_q2d(stream->time_base)*1000)) + stream->start_time);
}
