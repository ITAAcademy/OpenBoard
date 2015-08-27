#include "ffmpeghelp.h"

FFmpegHelp::FFmpegHelp(QObject *parent) : QObject(parent)
{

}

int FFmpegHelp::initFF(QString path)
{
    qDebug() << "start initFF";
    formatContext = (AVFormatContext*)openVideoStream( path );
    //videoThread.start();
    //audioThread.start();

    vDecoder = new VideoDecoder(0, formatContext );
    aDecoder = new AudioDecoder(0, formatContext);

    vDecoder->moveToThread(&videoThread);
    aDecoder->moveToThread(&audioThread);

  //  audio_decode_example(path.append("fsdfsd").toLatin1().data(), path.toLatin1().data());
    return 1;
}

QImage FFmpegHelp::getNextFrame()
{
    AVPacket Packet;
    QImage next;
    while( av_read_frame(formatContext,&Packet) >= 0 )
    {
        next = QImage(vDecoder->getNextFrame(Packet));
        aDecoder->nextFrame(Packet);
        av_free_packet(&Packet);
        if(vDecoder->getFrameFinished())
            break;
        //aDecoder->nextFrame(Packet);
    }
    if(next.isNull())
        return QImage(800,600, QImage::Format_RGBA8888_Premultiplied);
    return next;

}

void FFmpegHelp::restart()
{
    vDecoder->seekFile(0);
}

long FFmpegHelp::getDuration()
{
    return vDecoder->duration * 1000;
}

long FFmpegHelp::getPTS()
{
    return vDecoder->baseTime;
}

AVFormatContext* FFmpegHelp::openVideoStream( QString path)
{
    // Register all formats and codecs
  //  close();
    //AVFormatContext * videoFormatContext = new AVFormatContext();

    path = path + "\0";
    char *str = new char[path.size() + 5];
    strcpy( str, path.toLatin1().data());
    //qDebug() << "Input path:  " << path;
    //qDebug() << "Input path:  " << str;
    qDebug() << "registaration";
    av_register_all();
    qDebug() << "registaration  OK";
   /* AVCodec * codec = av_codec_next(NULL);

    if(avcodec_find_decoder_by_name("h264_vdpau") != NULL)
        //qDebug() << "===============OK===============";*/
   /* while(codec != NULL)
    {
        //qDebug() << codec->long_name;

        codec = av_codec_next(codec);
    }
    */
    // Open video file
    qDebug() << "start open ff  " << str;
    if(avformat_open_input(&formatContext, str, NULL, NULL)!=0)
    {
      QFile file(str);
      if(file.isOpen())
        qDebug() << "open file\n\t" ;

      return NULL; // Couldn't open file
    }

    // Retrieve stream information
    if(avformat_find_stream_info(formatContext, NULL)<0)
    {
      //qDebug() << "Couldn't find stream information";
      return NULL; // Couldn't find stream information
    }

    // Dump information about file onto standard error
    av_dump_format(formatContext, 0, str, 0);
    return formatContext;
}
