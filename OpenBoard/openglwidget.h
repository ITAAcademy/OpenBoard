#ifndef OPENGLWIDGET
#define OPENGLWIDGET

#include <QObject>
#include <QtCore>
//#include <QtQml>
//#include <QtQuickWidgets>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QImage>
#include <QPainter>
#include <QMetaObject>
#include <QFontMetrics>
#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

#include "encoder/videorencoder.h"
/*
#include <QtAV/QtAV>
#include <QtAVWidgets/QtAVWidgets>

using namespace QtAV;
*/

#define STREAM_FRAME_RATE 10
#define STREAM_DURATION 60

struct ColorMarker{
    int startIndex;
    QColor value;
};

class Encoder;

struct DrawData{
    QString str;
    int index;
    bool IsPlay;
};


class OGLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(QString  drawText READ getDrawText WRITE setDrawText NOTIFY drawTextChanged)

public:
    /*
     * |Future gradient
     */
   volatile bool isCrossingNow;
    QList<ColorMarker> colors;
    QImage brushBuffer;
    GLuint fbo, render_buf;
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
    explicit OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
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
    void nextRow(int n   = -1, int Row = -1, bool wrap = true);
    Q_INVOKABLE void crossOutLastSymbol(int n = 1);
    void crossOutWithAnimation(int n = 1);
    void clearSymbol(int index);
    QPoint drawWrapText( QString str ); // main draw function
    void setFillColor( QColor col);
    void setFillGradient( int x , int y, int width, int height, GradientSetting color);
    void fillText( QString str,QColor color, int x, int y);
    void fillAnimationText(QString str, int x, int y, float time);
    void isLastRow();
    void pause(int ms);

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
    bool getBusy() const;

    QImage getBackBuffer() const;
    void setBackBuffer(const QImage &value);

    int getCursorIndex() const;
    void setCursorIndex(int value);


    void drawTexture(int x, int y, int width, int height, GLuint texture);
    void update();
public slots:
    void drawAnimated( bool record );
    void stopAnimated();
    void pauseAnimated();

    void updateWindow();
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
    bool crossText();
    bool crossTextV2();
    int getFirstSymbolOfString(int index, bool symbol = false);
    int getCountNullString(int index);
private:
    QImage img;
    QImage GL_formatted_image;
    GLuint texture;
    QString drawText;
    bool bRecord;
    void generateFrames();
    int loadTexture(QImage img, int index = -1, bool modify = false);
    int loadTextureFromFile(QString path, int index = -1); // return index for reload + texture indefication
    bool reloadTexture( int index);
    StatusDraw curStatus; // 0 - stop; 1 - play; -1 - pause
    QObject *canvas;
    QThread drawThread;
    AV_REncoder *m_encoder = NULL;

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
    int realDelay;
    double timer_test;
    double animationSpeed = 0.01;
    bool busy = false;


    /*
     * |new property
     */

    QList<QString> stringList;
    QList<short int> cross;
    int indexRowInList; // first str for draw
    int indexFirstDrawSymbol = 0;
    int maxDrawElm = 0;
    QElapsedTimer framDelayTimer;
    bool isClose = false;
    int cursorIndex;
    QVector <QImage> imgList;
    QVector <GLuint> textureList;

protected:
    void destroy(bool destroyWindow, bool destroySubWindow);
    void initializeGL(); // Метод для инициализирования opengl
       void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
       void paintGL(); // Метод для вывода изображения на экран
        int wax ,way; // Размеры окна нашей программы
};


#endif // OPENGLWIDGET

