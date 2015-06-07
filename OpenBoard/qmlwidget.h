#ifndef QMLWIDGET_H
#define QMLWIDGET_H

#include <QObject>
#include <QtCore>
#include <QtQml>
#include <QtQuickWidgets>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QImage>
#include <QPainter>
#include <QMetaObject>
#include <QFontMetrics>
#include <QtMultimedia/QAudioRecorder>
#include <QtMultimedia/QAudioProbe>

#include <Encoder>
#include <ScreenGrabber>
#include <VideoCodecSettings>
#include <AudioCodecSettings>

/*
#include <QtAV/QtAV>
#include <QtAVWidgets/QtAVWidgets>

using namespace QtAV;
*/

#define STREAM_FRAME_RATE 10
#define STREAM_DURATION 60



class Encoder;

struct DrawData{
    QString str;
    int index;
    bool IsPlay;
};


class QmlWidget : public QQuickWidget
{
    Q_OBJECT
    Q_PROPERTY(QString  drawText READ getDrawText WRITE setDrawText NOTIFY drawTextChanged)

public:
    /*
     * Структурка для градіента
     */
    struct GradientSetting{
        QStringList list;
        void addColorStop( float range, int r, int g, int b, int a = 255)
        {
            list.push_back(QString::number(range));
            list.push_back(QString("rgba(%1, %2, %3, %4)").arg(r).arg(g).arg(b).arg(a));
        }
    };
    // status state
    enum StatusDraw{
     PLAY , STOP, PAUSE
    };
    enum FigureType{
        LINE, RECTANGLE
    };

    /*
     * Events
     */
    explicit QmlWidget(QWidget *parent = 0);
    ~QmlWidget();
    void moveEvent(QMoveEvent *event);
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent ( QMouseEvent * event );
    /*
     * Canvas control
     */
    void clearCanvas();
    void drawFigure (int x, int y, int width, int height, FigureType type, bool fill);
    void nextRow();
    Q_INVOKABLE void crossOutLastSymbol();
    void crossOutWithAnimation();
    QPoint drawWrapText( QString str ); // main draw function
    void setFillColor( QColor col);
    void setFillGradient( int x , int y, int width, int height, GradientSetting color);
    void fillText( QString str, int x, int y);
    void fillAnimationText(QString str, int x, int y, float time);
    void isLastRow();
    /*
     * G/S
     */
    StatusDraw getStatus() const;
    QFont getTextFont() const;
    void setTextFont(const QFont &value);
    void setDrawText( QString data );
    QString getDrawText();
    void recreate();
    /*
     * encoder
    */
    VideoCodecSettings videoCodecSettings() const;
    AudioCodecSettings audioCodecSettings() const;
public slots:
    void drawAnimated( bool record );
    void stopAnimated();
    void pauseAnimated();
public:
    bool isRecord() const;
    int getCountDeleteWT() const;
    int getDelay() const;
    void setDelay(int value);
    QColor getMainFillColor() const;
    void setMainFillColor(const QColor &value);

signals:
    void drawTextChanged();
public slots:

private slots:
    void processBuffer(const QAudioBuffer &buffer);
    void displayErrorMessage();
    void fps_control();
private:
    QString drawText;
    Encoder *m_encoder;
    QAudioRecorder *audioRecorder;
    QAudioProbe *probe;
    bool bRecord;
    void generateFrames();
    StatusDraw curStatus; // 0 - stop; 1 - play; -1 - pause
    QObject *canvas;
    /*
     * Сavas property
    */
    int lineHeight;
    int marginLeft;
    int marginTop;
    int maxWidth; //размер поле, где виводится текст
    int pt;
    bool crossWithAnimation = false;
    QString font;
    bool isWord  ;
    int x ,y ;
    int indexW ;
    int indexRow;
    int scroll;
    QColor fillColor;
    QColor mainFillColor;
    QList <QPoint> symbolPositionList;
    QString listWords; // вся стрічка
    QList<int> listStr; // номер з якої починається і-та стрічка
    QFont textFont;
    QFontMetrics *fMetrics;
    int indexInLsit;
    int deleteWT;
    QTimer tickTimer;
    int delay;
    int fps_stabilitron;
    QTimer *fps_timer;

};




#endif // QMLWIDGET_H
