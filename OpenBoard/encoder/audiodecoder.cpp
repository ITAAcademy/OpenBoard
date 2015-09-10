#include "audiodecoder.h"

static sample_fmt_entry samplefmts[] = { { AV_SAMPLE_FMT_U8, SampleFormat_Unsigned8, "u8" },
    { AV_SAMPLE_FMT_S16, SampleFormat_Signed16, "s16" },
    { AV_SAMPLE_FMT_S32, SampleFormat_Signed32, "s32" },
    { AV_SAMPLE_FMT_FLT, SampleFormat_Float, "float" },
    { AV_SAMPLE_FMT_DBL, SampleFormat_Double, "double" },
    { AV_SAMPLE_FMT_U8P, SampleFormat_Unsigned8Planar, "u8p" },
    { AV_SAMPLE_FMT_S16P, SampleFormat_Signed16Planar, "s16p" },
    { AV_SAMPLE_FMT_S32P, SampleFormat_Signed32Planar, "s32p" },
    { AV_SAMPLE_FMT_FLTP, SampleFormat_FloatPlanar, "floatp" },
    { AV_SAMPLE_FMT_DBLP, SampleFormat_DoublePlanar, "doublep" },
    { AV_SAMPLE_FMT_NONE, SampleFormat_Unknown, "unknown" }
};

void AudioDecoder::setAudioPacket(const AVPacket &value)
{
    audioPacket = value;
}

qint64 AudioDecoder::getDTSFromMS(int ms)
{
    AVStream *stream = formatContext->streams[audioStream];
    //double seconds = (audioPacket.dts - stream->start_time) * av_q2d(stream->time_base)*1000;
    return (qint64) qCeil((double)(ms/(av_q2d(stream->time_base)*1000)) + stream->start_time);
}

void AudioDecoder::seekFile(int ms)
{
    qDebug() << "seekFile();";
    avformat_seek_file(formatContext, audioStream,INT64_MIN, ms, INT64_MAX, 0 );
    baseTime = 0;
    audioBuffer.clear();
}
void AudioDecoder::stateChanged(QAudio::State state)
{
    //qDebug() << "State Change ::: " << state;
}

int AudioDecoder::getFrameFinished() const
{
    return frameFinished;
}

int64_t AudioDecoder::getDuration() const
{
    return duration;
}
AudioDecoder::AudioDecoder(QObject * parent, AVFormatContext *formatContext ): QObject( parent ),  m_pullTimer(new QTimer(this))
{
    this->formatContext = formatContext;
    initAudioDecoder();
    initFormat();
}

void AudioDecoder::initAudioDecoder()
{
    buffSize = 0;
    for( unsigned int i=0; i < formatContext->nb_streams; i++ )
    {
        if( formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO )
        {
            audioStream = i;
            break;
        }
    }
    if( audioStream == -1 )
    {
        qWarning() << "Didnt find audio stream";
        return;
    }

    audioCodecContext = formatContext->streams[audioStream]->codec;

    audioCodec = avcodec_find_decoder(audioCodecContext->codec_id);
    //qDebug() << "codec ID" << audioCodecContext->codec_id;
    avcodec_open2(audioCodecContext, audioCodec, &optionsDict);

    int secs = formatContext->duration / AV_TIME_BASE;
    int us = formatContext->duration % AV_TIME_BASE;
    int l = secs*1000 + us/1000;

    //dumpFormat(pFormatCtx,videoStream,"test video",0);

    duration = l;

    //med_buffer = (unsigned char*)malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE + FF_INPUT_BUFFER_PADDING_SIZE);

   // buffer.open(QBuffer::WriteOnly);
}

AudioDecoder::~AudioDecoder()
{
    delete audio;
    myFile.close();
}

QByteArray AudioDecoder::nextFrame(qint64 time)
{
    if( av_read_frame(formatContext,&audioPacket) >= 0 )
    {
        return nextFrame(audioPacket, time);
    }

}

int AudioDecoder::resample()
{
    if(out == NULL)
    {
        av_free(out);
        out = av_frame_alloc();
        /*av_frame_copy(out, audioFrame);
        //av_frame_make_writable(out);
        av_frame_set_channel_layout(out, AV_CH_LAYOUT_STEREO);
        av_frame_set_pkt_pos(out,0);
        //qDebug() << audioFrame->format;*/

    }

   if(swr != NULL)
    {
/*        if( swr_convert_frame(swr, out, audioFrame) != 0)
        {
            //qDebug() << "ERR cannot convert audio";
        }
        else
            //qDebug() << "OK";
*/
        /*
         * V2
        */

            int ret;
               uint8_t **out_data = NULL;
               uint8_t **in_data = NULL;
               int out_nb_samples = 0, in_nb_samples = 0;

               if (out) {
                   out_data       = out->extended_data;
                   out_nb_samples = out->nb_samples;
                   //qDebug() << "QWE" << out_nb_samples;
               }

               if (audioFrame) {
                   in_data       = audioFrame->extended_data;
                   in_nb_samples = audioFrame->nb_samples;
                   //qDebug() << "QWE" << audioFrame->nb_samples;
               }
               int src_rate = audioCodecContext->sample_rate;
               int dst_nb_samples;
               int max_dst_nb_samples = dst_nb_samples =  av_rescale_rnd(in_nb_samples, audioCodecContext->sample_rate, audioCodecContext->sample_rate, AV_ROUND_UP);
               ////////////////////////////////////
               /*
                *
               */
               int src_ch_layout = audioCodecContext->channel_layout;

               int src_nb_channels = av_get_channel_layout_nb_channels(src_ch_layout);
                  ret = av_samples_alloc_array_and_samples(&in_data, audioFrame->linesize, audioFrame->channels,
                                                           audioFrame->nb_samples, audioCodecContext->sample_fmt, 0);
                  if (ret < 0) {
                      //qDebug() << "Could not allocate source samples\n";
                      return 0;
                  }

                  /* compute the number of converted samples: buffering is avoided
                   * ensuring that the output buffer will contain at least all the
                   * converted input samples */
                  int sampleRate = audioFrame->sample_rate;
                  max_dst_nb_samples = dst_nb_samples =
                      av_rescale_rnd(audioFrame->nb_samples, sampleRate, sampleRate, AV_ROUND_UP);
                  dst_nb_samples = av_rescale_rnd(swr_get_delay(swr, sampleRate) +
                                                  audioFrame->nb_samples, sampleRate, sampleRate, AV_ROUND_UP);
                  /* buffer is going to be directly written to a rawaudio file, no alignment */
                  int dst_nb_channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
                  //qDebug() << "Chanel" << dst_nb_channels;
                  ret = av_samples_alloc_array_and_samples(&out_data, out->linesize, dst_nb_channels,
                                                           dst_nb_samples, AV_SAMPLE_FMT_S16, 0);
                  if (ret < 0) {
                      //qDebug() <<  "Could not allocate destination samples\n";
                      return 0;
                  }

                  //qDebug() << "DST NB SAMPLES   " << dst_nb_samples;
                  if (dst_nb_samples > max_dst_nb_samples) {
                      av_freep(&out_data[0]);
                      ret = av_samples_alloc(out_data, out->linesize, dst_nb_channels,
                                             dst_nb_samples, AV_SAMPLE_FMT_S16, 1);
                  /*    if (ret < 0)
                          break;*/
                      max_dst_nb_samples = dst_nb_samples;
                  }

                  /* convert to destination format */
                  ret = swr_convert(swr, out_data, dst_nb_samples, (const uint8_t **)in_data, audioFrame->nb_samples);
                  if (ret < 0) {
                      //qDebug() << "Error while converting\n";
                      return 0;
                  }
                  out->nb_samples = dst_nb_samples;
                  return dst_nb_samples;
               /*
                *
               */
                 /*
               ret = swr_convert(swr, out_data, out_nb_samples, in_data, in_nb_samples);

               if (ret < 0) {
                   if (out)
                      out->nb_samples = 0;
                  return ret;
              }

              if (out)
                  out->nb_samples = ret;

              return 0;*/

    }
    else
        qDebug() << "ERR cannot convert audio";


/*
    int inRate = 0;
    int outRate = 0;
    char *out;
    char *in;
    int size;
    audio_cntx = av_resample_init( outRate,	// out rate
                inRate,	// in rate
                16,	// filter length
                10,	// phase count
                0,	// linear FIR filter
                1.0 );	// cutoff frequency
    if(audio_cntx )
       //qDebug() << "Failed to create resampling context!";

    int samples_consumed = 0;
    int samples_output = av_resample( audio_cntx,
        (short*)out,
        (short*)in,
        &samples_consumed,
        size / 2,
        sizeof( out ) / 2, // in samples
        0 );
    if(samples_output > 0 )
        //qDebug() << "Error calling av_resample()!";

    av_resample_close( audio_cntx );

    // Play the processed samples.
*/
}

int AudioDecoder::resample2()
{
        int out_samples;
        out_samples = av_rescale_rnd(swr_get_delay(swr, audioCodecContext->sample_rate) +
                                             audioFrame->nb_samples, audioCodecContext->sample_rate, audioCodecContext->sample_rate, AV_ROUND_UP);

       // out_samples = фг;
        out = av_frame_clone(audioFrame);
    /*    av_samples_alloc(   out->extended_data,
                             NULL,
                             2,
                             out_samples,
                             AV_SAMPLE_FMT_S16,
                             0);*/
        av_frame_set_channels(out, 2);
        av_frame_set_channel_layout(out, AV_CH_LAYOUT_STEREO);
        av_frame_set_sample_rate(out, 44100);

        int max_dst_nb_samples = av_rescale_rnd(audioFrame->nb_samples, audioCodecContext->sample_rate, audioCodecContext->sample_rate, AV_ROUND_UP);

        int dst_nb_samples = av_rescale_rnd(swr_get_delay(swr, audioCodecContext->sample_rate) +
                                        audioFrame->nb_samples, 44100, audioCodecContext->sample_rate, AV_ROUND_UP);

            av_freep(out->extended_data);
            av_samples_alloc(out->extended_data, out->linesize, 2,
                                   dst_nb_samples, AV_SAMPLE_FMT_S16, 1);
            max_dst_nb_samples = dst_nb_samples;


    out->nb_samples = swr_convert(swr, out->extended_data, dst_nb_samples, (const uint8_t **) audioFrame->extended_data, audioFrame->nb_samples);
}

QByteArray AudioDecoder::nextFrame(AVPacket &audioPacket, qint64 time)
{
    qint64 written=0;
    qint64 data_size;
    qint64 currentDts = getDTSFromMS(time);
    frameFinished = 0;
    QByteArray res;
    if( audioPacket.stream_index == audioStream)
    {
        while(audioPacket.size > 0)
        {
            int len;//, data_size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
            //decode

            len = avcodec_decode_audio4(audioCodecContext, audioFrame, &frameFinished, &audioPacket);

            if(frameFinished)
            {
                if(bSwr_init)
                    resample2();
                if(audioFrame != NULL)
                {
                    data_size = av_samples_get_buffer_size(out->linesize, 2,
                                                                           out->nb_samples,
                                                                           AV_SAMPLE_FMT_S16, 1);
                    /*if(data_size > audio->bytesFree())
                        data_size = audio->bytesFree();*/
                    AudioBuff buff;
                    buff.arr = QByteArray((const char*)out->data[0], data_size);
                    buff.dts = audioPacket.dts;
                    audioBuffer.append(buff);
                    avcodec_free_frame(&out);
                    /*m_output->write((const char*)out->data[0], data_size);
                    res += QByteArray((const char*)out->data[0], data_size);*/
                  //  qDebug() << data_size;
//                    qDebug() << "NEED" << audioPacket.dts - audioFrame->best_effort_timestamp;
                 //   qDebug() << "IS" << data_size;
                    AVStream *stream = formatContext->streams[audioStream];
                    double seconds= (audioPacket.dts - stream->start_time) * av_q2d(stream->time_base)*1000;
                    //qDebug() << "TIME   " << time << "  " << (getDTSFromMS(time) - stream->start_time) * av_q2d(stream->time_base)*1000;
                    //qDebug() << "A_SECONDS    " <<seconds;


                    /*int chunks = audio->bytesFree()/audio->periodSize();
                    for(int i = 0; i < chunks; i++)
                    {
                       if (audio->periodSize()*i < data_size){
                           if((data_size - audio->periodSize()*i) >= audio->periodSize())
                               m_output->write((const char*)out->data[0] + audio->periodSize()*i, audio->periodSize());
                           else {
                               m_output->write((const char*)out->data[0] + audio->periodSize()*i, data_size - audio->periodSize()*i);
                           }
                        }
                    }*/
                    //av_free(audioFrame);

                }
                AVStream *stream = formatContext->streams[audioStream];
                qint64 seconds= (audioPacket.dts - stream->start_time) * av_q2d(stream->time_base)*1000;
                //qDebug() << "V_SECONDS    " << seconds;
                baseTime = seconds;
            }
            audioPacket.size -= len;
            audioPacket.data += len;
        }

        while( audioBuffer.size() > 0 && currentDts >= audioBuffer.first().dts)
        {
         //   qDebug() << "AUDIO  " << currentDts;
            m_output->write(audioBuffer.first().arr.data(), audioBuffer.first().arr.size());
            res += audioBuffer.first().arr;
            audioBuffer.pop_front();

        }

    }

    return res;
}

void AudioDecoder::initFormat()
{
    /*
    format.setSampleRate(audioCodecContext->sample_rate);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    //qDebug() << "Audio devises coute: " << QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).size();
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());

    if (!info.isFormatSupported(format)) {
        qWarning()<<"raw audio format not supported by backend, cannot play audio.";
        format = info.nearestFormat(format);
    }
    */
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::BigEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = info.nearestFormat(format);
    }

    audio = 0;
    audio = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format, this);

    //qDebug() << "FORMAT PARAM:";
    //qDebug() << "Sample rate = " << format.sampleRate();
    //qDebug() << "Sample size = " << format.sampleSize();
    //qDebug() << "Codec = " << format.codec();
    //qDebug() << "Chanel count = " << format.channelCount();
    //qDebug() << "Oder = " << format.byteOrder();
    //qDebug() << "Chanel count = " << format.sampleType();

 //   connect(audio,SIGNAL(stateChanged(QAudio::State)),SLOT(stateChanged(QAudio::State)));

    if( !buffer.open(QBuffer::ReadWrite) )
        qWarning() << "Couldnt open Buffer";

   // //qDebug() << "buffer.size()=" << buffer.size();
    audio->setVolume(100);

   // connect(m_pullTimer, SIGNAL(timeout()), SLOT(pullTimerExpired()));
    audioFrame=av_frame_alloc();
   // out=av_frame_alloc();

   // audio->setBufferSize(audioCodecContext->bits_per_raw_sample*2);
    m_output = audio->start();
    //m_output = audio->start();
   // m_pullTimer->start(20);

   // m_pullTimer->setInterval(20);
   // m_pullTimer->start(20);
    //qDebug() << audioCodecContext->sample_rate << "\n";
    //qDebug() << audioCodecContext->sample_fmt << "\n";

    //qDebug() << "start create context";

    swr = swr_alloc_set_opts(NULL,  // we're allocating a new context
                       AV_CH_LAYOUT_STEREO,  // out_ch_layout
                       AV_SAMPLE_FMT_S16,    // out_sample_fmt
                       44100,                // out_sample_rate
                       audioCodecContext->channel_layout, // in_ch_layout
                       audioCodecContext->sample_fmt,   // in_sample_fmt
                       audioCodecContext->sample_rate,                // in_sample_rate
                       0,                    // log_offset
                       NULL);                // log_ctx

    if(swr_init(swr) < 0)
    {
        bSwr_init = false;
        //qDebug() << "ERR create context" << swr_is_initialized(swr);
    }
    else
        qDebug() << "create context" << swr_is_initialized(swr);


    //////////////////////////////

    //audio_cntx = av_audio_resample_init(2, audioCodecContext->channels, audioCodecContext->sample_rate, audioCodecContext->sample_rate, AV_SAMPLE_FMT_S16, audioCodecContext->sample_fmt, 1024, 20, 1, 0);
}

int AudioDecoder::getSampleFormatSize(AVSampleFormat frm)
{
    /*
    //qDebug() << "convert samle format       __::";
    switch (frm) {
    case AV_SAMPLE_FMT_U8:
        //qDebug() << "Set U8";
        return sizeof(unsigned char);
        break;
    case AV_SAMPLE_FMT_S16:
        //qDebug() << "Set S16";
        return 16;
        break;
    case AV_SAMPLE_FMT_FLT:
        //qDebug() << "Set FLT";
        return sizeof(float);
        break;
    case AV_SAMPLE_FMT_DBL:
        //qDebug() << "Set DBL";
        return sizeof(double);
        break;
    case AV_SAMPLE_FMT_S32:
        //qDebug() << "Set S32";
        return sizeof(int);
        break;
    default:
        //qDebug() << "Set def";
        return av_get_bytes_per_sample(frm);
        break;
    }
    */
    for (int i = 0; samplefmts[i].fmt != SampleFormat_Unknown; ++i) {
        if ((int)samplefmts[i].avfmt == frm)
        {
            //qDebug() << samplefmts[i].name;
            return samplefmts[i].fmt;
        }
    }
    return SampleFormat_Unknown;
}


void AudioDecoder::pullTimerExpired()
{
    if (audio && audio->state() != QAudio::StoppedState) {
        //qDebug() << "AUDIO OK";
        int chunks = audio->bytesFree()/audio->periodSize();
        //while (chunks)
        {
               m_output->write((const char*)buffer.data());
           --chunks;
        }
    }
  //  //qDebug() << "AUDIO BAD";
}

