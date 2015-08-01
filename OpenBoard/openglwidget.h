#ifndef OPENGLWIDGET
#define OPENGLWIDGET
#pragma once
#include <QObject>
#include <QtCore>
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
#include <QRect>
#include "encoder/videorencoder.h"
#include "../Brush/brushcontroll.h"

class ListControll;
struct BrushBeginingIndex;
class DrawTextElm;
class DrawBrushElm;
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
enum EditingRectangleBindMode {EDIT_RECTANGLE_UNBINDED =0,EDIT_RECTANGLE_MOVE=1,EDIT_RECTANGLE_RESIZE=2};
struct RectangleEditor {
    QRect rect;
    int leftCornerSize;
    bool isEditingRectangleVisible = true;
    int editingRectangleMode = EDIT_RECTANGLE_UNBINDED;

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
        QPoint mousePressPos;
public:
    BrushManager m_manager;
    /*
     * |Future gradient
     */

   bool isMousePlay = false;//play recorded mouse movement
   bool isMousePress = false;
   bool ismouseWasPressedBeforeDrag = false;  
    bool isClearFrameBuffer = false;//clear frame buffer
   volatile bool isCrossingNow;

   DrawBrushElm *drawBrushElm;//record mouse movement




//bool isEditingRectangleBindedToCursor = false;
   RectangleEditor editingRectangle;//Draw element layout manager

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
    void fillText(QString str, QColor color, int x, int y, int z = 0);
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

    void drawTexture(int x, int y, int width, int height, int index, int angle=0, float scaleX = 1, float scaleY = 1, int z = 0);
    void drawTexture(int x, int y, int width, int height, GLuint texture, int angle=0, float scaleX = 1, float scaleY = 1, int z = 0);
    void update();
    void initFrameBufferTexture();
    void initFrameBufferDepthBuffer();
    void paintBrushInBuffer();
    void initFrameBuffer();
    QList<DrawElement *> &getList();
    void setList(const QList<DrawElement *> &value);
    bool getIsBrushWindowOpened() const;
    void setIsBrushWindowOpened(bool value);

    void paintBufferOnScreen(int x , int y , int width, int height, int z = 0);
    void clearFrameBuffer();


    void paintBrushInBuffer(QVector<QPoint> coords, QVector<BrushBeginingIndex> brushes,int keyFrame);
public slots:
    void drawAnimated( bool record );
    void stopAnimated();
    void pauseAnimated();
    void brushParamsChanged();
    void updateWindow();
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
    void drawTextBuffer(int m_x, int m_y, int m_width, int m_height, int z = 0);
    void moveCursor(int n = 1, bool withWrapShift = true);
    void clearBuffer();
    void testWrap(int kIndexOfRow);
    void deleteFromBuffer(int n);
    bool crossTextDraw();
    int loadTexture(QImage img, int index = -1, bool modify = false);
    int loadTextureFromFile(QString path, int index = -1); // return index for reload + texture indefication
    bool reloadTexture( int index);
    /*
     *
     *
    */

    int getRowFromTextBoxIndex(int index, bool symbol);
    ListControll* getTimeLine();

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
    void storeMousePos();

private:
    QImage img;
    ListControll *timeLine = NULL;

    GLuint    fbo,// The frame buffer object
	fbo_depth, // The depth buffer for the frame buffer object

	fbo_texture; // The texture object to write our frame buffer object to
    QString drawText;
    bool bRecord;
    void generateFrames();
    StatusDraw curStatus; // 0 - stop; 1 - play; -1 - pause
    QThread drawThread;
    AV_REncoder *m_encoder = NULL;

    /*
     * |Сavas property
    */

    bool crossWithAnimation = false;
    QString font;
    bool isWord  ;

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

    /*
     * |new property
     */
    QVector<int> wrapShift;
    QVector <QImage> imgList;
    QVector <GLuint> textureList;
    QList<QString> stringList;
    QList<short int> cross;
    QList<DrawElement *> list_1;
    QList<DrawElement *> list_2;
    int indexRowInList; // first str for draw
    int cursorIndex;
    int indexFirstDrawSymbol = 0;
    int maxDrawElm = 0;
    int delay;
    int lineHeight;
    int marginLeft;
    int marginTop;
    int maxWidth; //размер поле, где виводится текст
    int pt;
    int realDelay;
    int mousePlayIndex = 0;//current point of stored points arr
    int x ,y ;
    int indexW ;
    int indexRow;
    int scroll;
    int widthToClean=0;

    double timer_test;
    double animationSpeed = 0.01;
    QTimer tickTimer;
    QTimer mouseTimer;

    bool busy = false;
    bool isClose = false;
    bool curentList = false;




    bool isBrushWindowOpened = false;//set in true state when brush window opened
protected:
    void destroy(bool destroyWindow, bool destroySubWindow);
    void initializeGL(); // Метод для инициализирования opengl
       void resizeGL(int nWidth, int nHeight);
       void paintGL(); // Output generated Image to screen
        int wax ,way; // Window size

        QPoint selElm;
};


#endif // OPENGLWIDGET

