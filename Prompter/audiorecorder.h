#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QMediaRecorder>
#include <QUrl>
#include <QAudioRecorder>
#include <QAudioProbe>

class AudioRecorder : public QObject
{
    Q_OBJECT

public:
    enum STATUS{
        REC,
        STOP,
        PAUSE
    };

    AudioRecorder(QObject *parent = 0);
    ~AudioRecorder();

public slots:
    void processBuffer(const QAudioBuffer&);
    STATUS getStatus();
    QStringList getAllowDevices();
    void setOutputLocation();

private slots:
    void togglePause();
    void toggleRecord();

    void updateStatus(QMediaRecorder::Status);
    void onStateChanged(QMediaRecorder::State);
    void updateProgress(qint64 pos);
    QString getErrorMessage();

private:
    QAudioRecorder *audioRecorder;
    QAudioProbe *probe;
    bool outputLocationSet;
    double duration;
    STATUS currentStatus;
    QString currentDevice;

};

#endif // AUDIORECORDER_H
