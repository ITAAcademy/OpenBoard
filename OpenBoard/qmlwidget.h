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

public:
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
    void nextRow();
    Q_INVOKABLE void crossOutLastSymbol();
    void crossOutWithAnimation();
    void drawWrapText( QString str ); // main draw function
    void setFillColor( QColor col);
    void setFillGradient( int x , int y, int width, int height, GradientSetting color);
    void fillText( QString str, int x, int y);
    void fillAnimationText(QString str, int x, int y, float time);
    void isLastRow();
    /*
     * G/S
     */
    bool IsPlay() const;
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
    void drawAnimated();
    void stopAnimated();
    void pauseAnimated();

signals:
    void drawTextChanged();
public slots:

private:
    QString drawText;
    Encoder *m_encoder;
    void generateFrames();
    bool isPlay;
    QObject *canvas;
    /*
     * Сavas property
    */
    int lineHeight;
    int marginLeft;
    int marginTop;
    int maxWidth; //размер поле, где виводится текст
    int pt;
    QString font;
    bool isWord  ;
    int x ,y ;
    int indexW ;
    int indexRow;
    int scroll;
    QString listWords; // вся стрічка
    QList<int> listStr; // номер з якої починається і-та стрічка
    QFont textFont;
    QFontMetrics *fMetrics;
    int indexInLsit;
    int deleteWT;

};




#endif // QMLWIDGET_H
