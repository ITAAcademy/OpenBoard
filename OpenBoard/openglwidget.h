#ifndef OPENGLWIDGET
#define OPENGLWIDGET
#pragma once
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
#include "../Brush/brushcontroll.h"
class DrawTextElm;
class DrawElement;
/*
#include <QtAV/QtAV>
#include <QtAVWidgets/QtAVWidgets>

using namespace QtAV;
*/

#define STREAM_FRAME_RATE 10
#define STREAM_DURATION 60
#define TEXTURE_INDEX_BRUSH 1
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
   bool isMousePress = false;
   bool ismouseWasPressedBeforeDrag = false;
   volatile bool isCrossingNow;
    QList<ColorMarker> colors;
    QImage brushBuffer;
    struct GradientSetting{
        QStringList list;
        void addColorStop( float range, int r, int g, int b, int a = 255)
        {
            list.push_back(QString::number(range));
            list.push_back(QString("rgba(%1, %2, %3, %4)").arg(r).arg(g).arg(b).arg(a));
        }
    };
    // |status state
    QPoint mousePos;
    QPoint prevMousePos;
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
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    QSize getTextureSize();
    /*
     * |Canvas control
     */
    void clearCanvas(int m_x = 0, int m_y = 0);
    void drawFigure (int x, int y, int width, int height, FigureType type, bool fill, QColor col, float size);
    void drawAnimationFigure (int x, int y, int width, int height, FigureType type, bool fill);
    void nextRow(int n   = -1, int Row = -1, bool wrap = true);
    Q_INVOKABLE void crossOutLastSymbol(int n = 1);
    void crossOutWithAnimation(int n = 1);
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
    void initFrameBufferTexture();
    void initFrameBufferDepthBuffer();
    void renderMouseCursor();
    void initFrameBuffer();
    QList<DrawElement *> &getList();
    void setList(const QList<DrawElement *> &value);

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
    void drawTextBuffer(int m_x, int m_y, int m_width, int m_height);
    void moveCursor(int n = 1, bool withWrapShift = true);
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
    void pauseSignal();
    void stopSignal();
    void startSignal();
private slots:
    bool crossText();
    bool crossTextV2();
    int getFirstSymbolOfString(int index, bool symbol = false);
    int getCountNullString(int index);
private:
    QImage img;

    unsigned int fbo; // The frame buffer object
    unsigned int fbo_depth; // The depth buffer for the frame buffer object
    unsigned int fbo_texture; // The texture object to write our frame buffer object to
    QString drawText;
    bool bRecord;
    void generateFrames();
    int loadTexture(QImage img, int index = -1, bool modify = false);
    int loadTextureFromFile(QString path, int index = -1); // return index for reload + texture indefication
    bool reloadTexture( int index);
    StatusDraw curStatus; // 0 - stop; 1 - play; -1 - pause
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
    QFontMetrics *fMetrics;
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
    QVector<int> wrapShift;
    int indexFirstDrawSymbol = 0;
    int maxDrawElm = 0;
    QElapsedTimer framDelayTimer;
    bool isClose = false;
    int cursorIndex;
    QVector <QImage> imgList;
    QVector <GLuint> textureList;
    QList<DrawElement *> list_1;
    QList<DrawElement *> list_2;
    bool curentList = false;
    BrushManager m_manager;
protected:
    void destroy(bool destroyWindow, bool destroySubWindow);
    void initializeGL(); // Метод для инициализирования opengl
       void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
       void paintGL(); // Метод для вывода изображения на экран
        int wax ,way; // Размеры окна нашей программы
};


#endif // OPENGLWIDGET

