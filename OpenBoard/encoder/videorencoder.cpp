#include "videorencoder.h"


bool AV_REncoder::getBPause() const
{
    return bPause;
}

void AV_REncoder::setBPause(bool value)
{
    bPause = value;
}

void AV_REncoder::clearWaitForFrame()
{
    waitForFrame = 0;
}

void AV_REncoder::addWaitForFrame()
{
    waitForFrame++;
}
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

void AV_REncoder::setFrame(QImage value)
{

    // value.save("we.jpg");
    if(!bPause)
    {
        //memcpy(data, value.bits(), value.byteCount());
        frame = value;
        newImage = false;


/*
        if(audioBuffer.size() > 0)
        {
            QList<QByteArray> array;
            QMutableMapIterator it = audioBuffer.first();
            while (it != QMap::end() > 0)
            {
                QByteArray arr;
                while (it.value().size > 0)
                {

//                           m_encoder->encodeAudioData(audioBuffer.first());
                    arr.append(it.value().first());
                    it.value().pop_front();
                }
                array.append(arr);
                it.next();
            }
            QByteArray res;
            for(int i = 0; i < array.length(); i++)
            {
                if(res.size() < array[i].length())
                    res.resize(array[i].length());
                for(int j = 0; j < array[i].length(); j++)
                {
                    res[j] += array[i][j]/array.length();
                }
            }
            m_encoder->encodeAudioData(res);
        }*/

    }
}
/*
void AV_REncoder::addToAudioBuffer( QMap <void* , QList<QByteArray>> array)
{
    audioBuffer;
}
*/
void AV_REncoder::addToAudioBuffer( void* obj, QByteArray array)
{
    audioBuffer[obj] += array;
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
    settings.setPFramePredictionAnalysisMethod(EncoderGlobal::FastBlindMethod);
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
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(path + "test"));
    fileName = path;
    // //qDebug() << "Set path   " << path;
}

void AV_REncoder::setGrabWidget(QGLWidget *widget)
{
    grabWidget = widget;
    m_encoder->setVideoSize(grabWidget->size());
    frame = QImage(widget->size(), QImage::Format_RGB888);
//    data = new unsigned char[3 * widget->size().height() * widget->size().width()];
}

void AV_REncoder::startRecord()
{
    bRun = true;
    bPause = false;
    m_encoder->start();
    audioBuffer.clear();
   // audioRecorder->record();
    start();
}

void AV_REncoder::onStart()
{
    // //qDebug() << "RUNNNNNN";
}

void AV_REncoder::initAudio()
{
    audioRecorder = new QAudioRecorder(this);
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/raw");
    audioSettings.setQuality(QMultimedia::NormalQuality);
    audioSettings.setChannelCount(2);
    audioSettings.setSampleRate(44100);
    audioSettings.setEncodingMode(QMultimedia::ConstantBitRateEncoding );

    audioRecorder->setOutputLocation(QUrl(QDir::currentPath() + "test"));
    QString container = "audio/x-wav";
    audioRecorder->setEncodingSettings(audioSettings, QVideoEncoderSettings(), container);
    qDebug() << "AUDIO INPUT::  " << audioRecorder->audioInputs();
    if(audioRecorder->audioInputs().size() > 0)
        audioRecorder->setAudioInput(audioRecorder->audioInputs()[0]);
    else
        audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
    probe = new QAudioProbe;
    probe->setSource(audioRecorder);

   /* connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
            this, SLOT(processAudioBuffer(QAudioBuffer)));*/
    connect(audioRecorder, SIGNAL(error(QMediaRecorder::Error)), this,
            SLOT(displayErrorMessage()));
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
    newImage = true;
}

void AV_REncoder::stop()
{
    if(bRun)
    {
       // audioRecorder->stop();
        bRun = false;
        m_encoder->stop();

        frame = QImage(grabWidget->size(), QImage::Format_RGB888);
        qDebug() << "STOPPPP";
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
    isRun = true;
    int delta = 0;
    while(bRun || audioBuffer.size() > 0)
    {
            //qDebug() << "SHOW";
            if(!newImage || (!bRun && !audioBuffer.isEmpty()))
            {
                if(bRun)
                    m_encoder->encodeVideoFrame(frame);
                qDebug() << "PERFORM AUDIO " << waitForFrame << "   audioBuffer " << audioBuffer.size();
                if(audioBuffer.size() > 0 && audioBuffer.size() >= waitForFrame)
                {
                    unsigned int minBlock = -1;
                    QMap<void*, QByteArray> ::iterator it = audioBuffer.begin();
                    for(int i = 0; i < audioBuffer.size(); i++)
                    {
                        if(minBlock > it.value().size())
                            minBlock = it.value().size();
                        it++;
                        /*m_encoder->encodeAudioData(audioBuffer.first());
                        audioBuffer.pop_front();*/


                    }

                    QList<void*> itList = audioBuffer.keys();
                    qDebug() << "MIN_AUDIO_BLOCK    " << minBlock;
                    if(minBlock > 0)
                    {
                        QByteArray res;
                        res.resize(minBlock);
                        memset(res.data(), 0, minBlock);
                        for(int i = 0; i < itList.size(); i++)
                        {
                            it = audioBuffer.find(itList[i]);
                            for(int j = 0; j < minBlock; j++)
                            {
                                {
                                    //qDebug() << res[j];
                                    *((short int *)(res.data() + j)) = (*((short int *)(it.value().data() + j)) + *((short int *)(res.data() + j)))/2;
                                    j++;
                                   // qDebug() << res[j];

                                }

                            }

                            it.value().remove(0, minBlock);
                            if(it.value().size() == 0)
                            {
                                audioBuffer.remove(itList[i]);
                            }
                            /*m_encoder->encodeAudioData(audioBuffer.first());
                           audioBuffer.pop_front();*/

                        }
                        m_encoder->encodeAudioData(res);
                    }
                }
                else if(waitForFrame == 0)
                {
                    qDebug() << "PERFORM AUDIO NULL";
                    QByteArray bytes;
                    bytes.resize(5644);
                    bytes.fill(0,5644);
                    m_encoder->encodeAudioData(bytes);
                }
                newImage = true;
            }
       /*     int k = timer.elapsed() - (40 - delta);
            if(k > 0)
                delta = k;
            timer.restart();*/


    }
    isRun = false;
    qDebug() << "STOP_ThREAD";
}

void AV_REncoder::processAudioBuffer(const QAudioBuffer& buffer)
{
/*
    if(!bPause)
    {
        QByteArray arr;
        QByteArray record = QByteArray(buffer.constData<char>(), buffer.byteCount());
        if(audioBuffer.size() > 0)
        {
            qDebug() << "processAudioBuffer();  start" << record.size() << "    " << audioBuffer.first().size();

            if(record.size() == audioBuffer.first().size())
            {
                for(int i = 0; i < record.size(); i++)
                {
                    arr.append(0.5*(record[i] + audioBuffer.first()[i]));
                }
            }
            else
                arr = record;
            audioBuffer.pop_front();
        }

        m_encoder->encodeAudioData(arr);


    }*/
   // // //qDebug() << "AUDIO";
}

void AV_REncoder::displayErrorMessage()
{
    qDebug() << "AUDIO_ERRRRRRRRRRRRRR" << (audioRecorder->errorString());
}

