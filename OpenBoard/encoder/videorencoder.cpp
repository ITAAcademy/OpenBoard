#include "videorencoder.h"

AV_REncoder::AV_REncoder(QObject *parent) : QThread(parent)
{
    bRun = false;
    connect(this, SIGNAL(started()), this, SLOT(onStart()));

    initVideo();

    initAudio();
}

AV_REncoder::~AV_REncoder()
{
    if(audioRecorder != NULL)
        delete audioRecorder;
    if(probe != NULL)
        delete probe;
}

QImage AV_REncoder::getFrame() const
{
    return frame;
}

void AV_REncoder::setFrame(const QImage &value)
{
    //// qDebug() << "NEW IMAGE";
    // value.save("we.jpg");
    if(newImage)
    {
        //memcpy(data, value.bits(), value.byteCount());
        frame = value;
        newImage = false;
    }
}

VideoCodecSettings AV_REncoder::videoCodecSettings() const
{
    //x264 loseless fast preset
    VideoCodecSettings settings;
    settings.setCoderType(EncoderGlobal::Vlc);
    settings.setFlags(EncoderGlobal::LoopFilter);
    settings.setMotionEstimationComparison(1);
    settings.setPartitions(EncoderGlobal::I4x4 | EncoderGlobal::P8x8);
    settings.setMotionEstimationMethod(EncoderGlobal::Hex);
    settings.setSubpixelMotionEstimationQuality(3);
    settings.setMotionEstimationRange(16);
    settings.setGopSize(250);
    settings.setMinimumKeyframeInterval(2);
    settings.setSceneChangeThreshold(40);
    settings.setIQuantFactor(0.71f);
    settings.setBFrameStrategy(1);
    settings.setQuantizerCurveCompressionFactor(0.6f);
    settings.setMinimumQuantizer(0);
    settings.setMaximumQuantizer(69);
    settings.setMaximumQuantizerDifference(4);
    settings.setDirectMvPredictionMode(EncoderGlobal::SpatialMode);
    settings.setFlags2(EncoderGlobal::FastPSkip);
    settings.setConstantQuantizerMode(0);
    settings.setPFramePredictionAnalysisMethod(EncoderGlobal::NoWpm);
    settings.setBitrate(2048000);

    return settings;
}

AudioCodecSettings AV_REncoder::audioCodecSettings() const
{
    // audio, possible future adventures
    AudioCodecSettings settings;
    settings.setSampleRate( 44100);
    settings.setChannelCount(2);
    settings.setSampleFormat(EncoderGlobal::Signed16);
    return settings;
}

void AV_REncoder::setFileName(QString path)
{
    m_encoder->setFilePath( path );
    fileName = path;
    // qDebug() << "Set path   " << path;
}

void AV_REncoder::setGrabWidget(QGLWidget *widget)
{
    grabWidget = widget;
    m_encoder->setVideoSize(grabWidget->size());
    frame = QImage(widget->size(), QImage::Format_RGB888);
    data = new unsigned char[3 * widget->size().height() * widget->size().width()];
}

void AV_REncoder::startRecord()
{
    bRun = true;
    bPause = false;
    m_encoder->start();
    audioRecorder->record();
    start();
}

void AV_REncoder::onStart()
{
    // qDebug() << "RUNNNNNN";
}

void AV_REncoder::initAudio()
{
    audioRecorder = new QAudioRecorder(this);
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/pcm");
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioSettings.setChannelCount(2);
    audioSettings.setSampleRate(44100);
    audioSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding );

    //audioRecorder->setOutputLocation(QUrl::fromLocalFile("test"));
    QString container = "audio/x-wav";
    audioRecorder->setEncodingSettings(audioSettings, QVideoEncoderSettings(), container);
    audioRecorder->setAudioInput(audioRecorder->audioInputs().at(0));
    probe = new QAudioProbe;
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
            this, SLOT(processAudioBuffer(QAudioBuffer)));
    connect(audioRecorder, SIGNAL(error(QMediaRecorder::Error)), this,
            SLOT(displayErrorMessage()));
    probe->setSource(audioRecorder);
}

void AV_REncoder::initVideo()
{
    m_encoder = new Encoder(this);
    m_encoder->setVideoCodecSettings(videoCodecSettings());
    m_encoder->setAudioCodecSettings(audioCodecSettings());
    m_encoder->setEncodingMode(Encoder::VideoAudioMode);
   // m_encoder->setEncodingMode(Encoder::VideoMode);
    m_encoder->setVideoCodec(EncoderGlobal::H264);
    m_encoder->setAudioCodec(EncoderGlobal::MP3);
    m_encoder->setOutputPixelFormat(EncoderGlobal::YUV420P);
    m_encoder->setFixedFrameRate(25);
}

void AV_REncoder::pause()
{
    bPause = !bPause;
}

void AV_REncoder::stop()
{
    if(bRun)
    {
        audioRecorder->stop();
        m_encoder->stop();
        bRun = false;
        // qDebug() << "STOPPPP";
    }
 //   exit();
}

void AV_REncoder::encodeAudioData(QByteArray array)
{
    m_encoder->encodeAudioData(array);
}

void AV_REncoder::run()
{
    int i = 0;
    int delta = 0;
    QElapsedTimer timer;
    timer.start();
    while(bRun)
    {
        if(timer.elapsed() >= 40 - delta && !bPause)
        {
      //      // qDebug() << "SHOW";
            if(!newImage)
            {
                m_encoder->encodeVideoFrame(frame);
                newImage = true;
            }
            int k = timer.elapsed() - (40 - delta);
            if(k > 0)
                delta = k;
            timer.restart();


        }
    }
}

void AV_REncoder::processAudioBuffer(const QAudioBuffer& buffer)
{
    if(!bPause)
    {
        m_encoder->encodeAudioData(QByteArray(buffer.constData<char>(), buffer.byteCount()));
      //  // qDebug() << "AUDIO";
    }
   // // qDebug() << "AUDIO";
}

void AV_REncoder::displayErrorMessage()
{
    // qDebug() << (audioRecorder->errorString());
}
