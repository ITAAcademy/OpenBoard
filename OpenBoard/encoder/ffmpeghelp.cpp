#include "ffmpeghelp.h"


DecoderType FFmpegHelp::getType() const
{
    return type;
}

void FFmpegHelp::setType(const DecoderType &value)
{
    type = value;
}
FFmpegHelp::FFmpegHelp(QObject *parent) : QObject(parent)
{
    type = VideoAudioType;
}

FFmpegHelp::~FFmpegHelp()
{
    if(vDecoder != NULL)
        delete vDecoder;

    if(aDecoder != NULL)
        delete aDecoder;

}

int FFmpegHelp::initFF(QString path)
{
   // qDebug() << "start initFF";
    formatContext = (AVFormatContext*)openVideoStream( path );
    //videoThread.start();
    //audioThread.start();
   // qDebug() << "FORMAT "   << formatContext;
    if((type  & VideoType) != 0)
    {
        vDecoder = new VideoDecoder(0, formatContext );
        vDecoder->moveToThread(&videoThread);
    }
    if((type  & AudioType) != 0)
    {
        aDecoder = new AudioDecoder(0, formatContext);
        aDecoder->moveToThread(&audioThread);
    }




  //  audio_decode_example(path.append("fsdfsd").toLatin1().data(), path.toLatin1().data());
    return 1;
}

QSize FFmpegHelp::getSize()
{
    if((type & VideoType) != 0)
        return vDecoder->getSize();
    else
        return QSize(10, 10);
}

FFmpegHelp::Frame FFmpegHelp::getNextFrame(qint64 time)
{
    AVPacket Packet;
    aNext.clear();

    qint64 baseTime;
    if(((type & VideoType) != 0) && vDecoder->init)
        baseTime = vDecoder->baseTime;
    else
        baseTime = aDecoder->baseTime;
    //qDebug() << vDecoder->baseTime - aDecoder->baseTime;


    while( time >= baseTime &&  av_read_frame(formatContext, &Packet) >= 0 )
    {
        if(type  & VideoType != 0)
         vNext = vDecoder->getNextFrame(Packet, time);
        aNext +=  aDecoder->nextFrame(Packet, time);

                //qDebug() << aDecoder->getDTSFromMS(time) << "   " << dts << arr.size();
        av_free_packet(&Packet);

        if((type  & VideoType != 0) && vDecoder->init)
            baseTime = vDecoder->baseTime;
        else
            baseTime = aDecoder->baseTime;

        //qDebug() << "BASE_TIME  " << baseTime;
        //aDecoder->nextFrame(Packet);
    }
    return Frame(vNext, aNext);

}

void FFmpegHelp::restart()
{
    if((type  & VideoType) != 0)
        vDecoder->seekFile(0);
    if((type  & AudioType) != 0)
        aDecoder->seekFile(0);
    getNextFrame(0);
}

long FFmpegHelp::getDuration()
{
    if(((type  & VideoType) != 0) && vDecoder->init)
        return vDecoder->getVideoLengthMs();
    else
        return aDecoder->getDuration();
}

long FFmpegHelp::getPTS()
{
    if((type  & VideoType) != 0)
        return vDecoder->baseTime;
    else
        return 0;
}

AVFormatContext* FFmpegHelp::openVideoStream( QString path)
{
    // Register all formats and codecs
  //  close();
    //AVFormatContext * videoFormatContext = new AVFormatContext();

    path = path + "\0";
    char *str = new char[path.size() + 5];
    strcpy( str, path.toLatin1().data());
  //  strcpy( str, path.toLatin1().data());
    //qDebug() << "Input path:  " << path;
    //qDebug() << "Input path:  " << str;
   // qDebug() << "registaration";
    av_register_all();
   // qDebug() << "registaration  OK";
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
    //qDebug() << "start open ff  " << str;
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
    delete str;
    return formatContext;
}
