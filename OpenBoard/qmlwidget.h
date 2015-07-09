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
#include <QtConcurrent>

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
     * |Future gradient
     */
    struct GradientSetting{
        QStringList list;
        void addColorStop( float range, int r, int g, int b, int a = 255)
        {
            list.push_back(QString::number(range));
            list.push_back(QString("rgba(%1, %2, %3, %4)").arg(r).arg(g).arg(b).arg(a));
        }
    };
    // |status state
    enum StatusDraw{
     PLAY , STOP, PAUSE
    };
    enum FigureType{
        LINE, RECTANGLE
    };

    /*
     * |Events
     */
    explicit QmlWidget(QWidget *parent = 0);
    ~QmlWidget();
    void moveEvent(QMoveEvent *event);
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    void mousePressEvent ( QMouseEvent * event );
    /*
     * |Canvas control
     */
    void clearCanvas();
    void drawFigure (int x, int y, int width, int height, FigureType type, bool fill, QColor col, float size);
    void drawAnimationFigure (int x, int y, int width, int height, FigureType type, bool fill);
    void nextRow(int n   = -1, int Row = -1);
    Q_INVOKABLE void crossOutLastSymbol();
    void crossOutWithAnimation();
    void clearSymbol(int index);
    QPoint drawWrapText( QString str ); // main draw function
    void setFillColor( QColor col);
    void setFillGradient( int x , int y, int width, int height, GradientSetting color);
    void fillText( QString str, int x, int y);
    void fillAnimationText(QString str, int x, int y, float time);
    void isLastRow();
    void pause(int ms);
    void update();
    /*
     * |G/S
     */
    StatusDraw getStatus() const;
    QFont getTextFont() const;
    void setTextFont(const QFont &value);
    void setDrawText( QString data );
    QString getDrawText();
    void recreate();
    /*
     * |encoder
    */
    VideoCodecSettings videoCodecSettings() const;
    AudioCodecSettings audioCodecSettings() const;
    bool getBusy() const;

public slots:
    void drawAnimated( bool record );
    void stopAnimated();
    void pauseAnimated();
public slots:
    bool isRecord() const;
    int getCountDeleteWT() const;
    int getDelay() const;
    void setDelay(int value);
    QColor getMainFillColor() const;
    void setMainFillColor(const QColor &value);
    void clear(int x,int y,int width,int height);

    /*
     * | new method reDraw
     *
     */
    void insertToBuffer(const QChar ch);
    QPoint convertTextBoxToBufferIndex(int index, bool symbol = false);
    void drawBuffer();
    void moveCursor(int n = 1);
    void clearBuffer();
    void testWrap(int kIndexOfRow);
    void deleteFromBuffer(int n);
    bool crossTextDraw();
    /*
     *
     *
    */

    int getRowFromTextBoxIndex(int index, bool symbol);
signals:
    void drawTextChanged();
private slots:
    void processBuffer(const QAudioBuffer &buffer);
    void displayErrorMessage();
    void fps_control();
    bool crossText();
    bool crossTextV2();
private:
    QString drawText;
    Encoder *m_encoder = NULL;
    QAudioRecorder *audioRecorder = NULL;
    QAudioProbe *probe = NULL;
    bool bRecord;
    void generateFrames();
    StatusDraw curStatus; // 0 - stop; 1 - play; -1 - pause
    QObject *canvas;
    QThread drawThread;
    QThread encoderThread;
    /*
     * |Сavas property
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
    int widthToClean=0;
    QColor fillColor;
    QColor mainFillColor;
    /*
     * |not use
     */
    QList <QPoint> symbolPositionList;
    QString listWords; // вся стрічка
    QString listChars; // останнє введене слово
    QList<int> listStr; // номер з якої починається і-та стрічка
    /*
     * |not use
    */
    QFont textFont;
    QFontMetrics *fMetrics = NULL;
    int indexInList;
    int deleteWT;
    QTimer tickTimer;
    int delay;
    int fps_stabilitron;
    QTimer *fps_timer = NULL;
    QElapsedTimer fps_stabilitiTimer;
    double timer_test;
    double animationSpeed = 0.01;
    bool busy = false;


    /*
     * |new property
     */

    QStringList stringList;
    QList<short int> cross;
    int indexRowInList;
    int cursorIndex;
    bool isClose = false;


};




#endif // QMLWIDGET_H
