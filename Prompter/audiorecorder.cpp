#include <QAudioProbe>
#include <QAudioRecorder>
#include <QDir>
#include <QFileDialog>
#include <QMediaRecorder>

#include "audiorecorder.h"

AudioRecorder::AudioRecorder(QObject *parent) :
    QObject(parent)
{
    audioRecorder = new QAudioRecorder(this);
    probe = new QAudioProbe;
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
            this, SLOT(processBuffer(QAudioBuffer)));
    probe->setSource(audioRecorder);
    duration = 0;
/*
    //audio devices
    ui->audioDeviceBox->addItem(tr("Default"), QVariant(QString()));
    foreach (const QString &device, audioRecorder->audioInputs()) {
        ui->audioDeviceBox->addItem(device, QVariant(device));
    }

    //audio codecs
    ui->audioCodecBox->addItem(tr("Default"), QVariant(QString()));
    foreach (const QString &codecName, audioRecorder->supportedAudioCodecs()) {
        ui->audioCodecBox->addItem(codecName, QVariant(codecName));
    }

    //containers
    ui->containerBox->addItem(tr("Default"), QVariant(QString()));
    foreach (const QString &containerName, audioRecorder->supportedContainers()) {
        ui->containerBox->addItem(containerName, QVariant(containerName));
    }

    //sample rate
    ui->sampleRateBox->addItem(tr("Default"), QVariant(0));
    foreach (int sampleRate, audioRecorder->supportedAudioSampleRates()) {
        ui->sampleRateBox->addItem(QString::number(sampleRate), QVariant(
                                       sampleRate));
    }

    //channels
    ui->channelsBox->addItem(tr("Default"), QVariant(-1));
    ui->channelsBox->addItem(QStringLiteral("1"), QVariant(1));
    ui->channelsBox->addItem(QStringLiteral("2"), QVariant(2));
    ui->channelsBox->addItem(QStringLiteral("4"), QVariant(4));

    //quality
    ui->qualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));
    ui->qualitySlider->setValue(int(QMultimedia::NormalQuality));

    //bitrates:
    ui->bitrateBox->addItem(tr("Default"), QVariant(0));
    ui->bitrateBox->addItem(QStringLiteral("32000"), QVariant(32000));
    ui->bitrateBox->addItem(QStringLiteral("64000"), QVariant(64000));
    ui->bitrateBox->addItem(QStringLiteral("96000"), QVariant(96000));
    ui->bitrateBox->addItem(QStringLiteral("128000"), QVariant(128000));
*/
    connect(audioRecorder, SIGNAL(durationChanged(qint64)), this,
            SLOT(updateProgress(qint64)));
    connect(audioRecorder, SIGNAL(statusChanged(QMediaRecorder::Status)), this,
            SLOT(updateStatus(QMediaRecorder::Status)));
    connect(audioRecorder, SIGNAL(stateChanged(QMediaRecorder::State)),
            this, SLOT(onStateChanged(QMediaRecorder::State)));
    connect(audioRecorder, SIGNAL(error(QMediaRecorder::Error)), this,
            SLOT(displayErrorMessage()));
}

AudioRecorder::~AudioRecorder()
{
    delete audioRecorder;
    delete probe;
}

void AudioRecorder::updateProgress(qint64 duration)
{
    if (audioRecorder->error() != QMediaRecorder::NoError || duration < 2000)
        return;
    this->duration = duration/1000;
    //ui->statusbar->showMessage(tr("Recorded %1 sec").arg(duration / 1000));
}

void AudioRecorder::updateStatus(QMediaRecorder::Status status)
{
    /*QString statusMessage;

    switch (status) {
    case QMediaRecorder::RecordingStatus:
        statusMessage = tr("Recording to %1").arg(audioRecorder->actualLocation().toString());
        break;
    case QMediaRecorder::PausedStatus:
        clearAudioLevels();
        statusMessage = tr("Paused");
        break;
    case QMediaRecorder::UnloadedStatus:
    case QMediaRecorder::LoadedStatus:
        clearAudioLevels();
        statusMessage = tr("Stopped");
    default:
        break;
    }*/

   /* if (audioRecorder->error() == QMediaRecorder::NoError)
        ui->statusbar->showMessage(statusMessage);*/
}

void AudioRecorder::onStateChanged(QMediaRecorder::State state)
{
    switch (state) {
    case QMediaRecorder::RecordingState:
        currentStatus = REC;
        break;
    case QMediaRecorder::PausedState:
        currentStatus = PAUSE;;
        break;
    case QMediaRecorder::StoppedState:
        currentStatus = STOP;
        break;
    }
}

void AudioRecorder::toggleRecord()
{
    if (audioRecorder->state() == QMediaRecorder::StoppedState && audioRecorder->audioInputs().size() > 0) {
        audioRecorder->setAudioInput(currentDevice);

        QAudioEncoderSettings audioSettings;
        audioSettings.setCodec("audio/raw");
        audioSettings.setQuality(QMultimedia::NormalQuality);
        audioSettings.setChannelCount(2);
        audioSettings.setSampleRate(44100);
        audioSettings.setEncodingMode(QMultimedia::ConstantBitRateEncoding );
        QString container = "audio/x-wav";
        audioRecorder->setEncodingSettings(audioSettings, QVideoEncoderSettings(), container);
        audioRecorder->record();
    }
    else {
        audioRecorder->stop();
    }
}

void AudioRecorder::togglePause()
{
    if (audioRecorder->state() != QMediaRecorder::PausedState)
        audioRecorder->pause();
    else
        audioRecorder->record();
}

void AudioRecorder::setOutputLocation()
{
    QString fileName = QFileDialog::getSaveFileName();
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));
    outputLocationSet = true;
}

QString AudioRecorder::getErrorMessage()
{
    return audioRecorder->errorString();
}

// This function returns the maximum possible sample value for a given audio format

void AudioRecorder::processBuffer(const QAudioBuffer& buffer)
{

}

AudioRecorder::STATUS AudioRecorder::getStatus()
{
    return currentStatus;
}

QStringList AudioRecorder::getAllowDevices()
{
    return audioRecorder->audioInputs();
}
