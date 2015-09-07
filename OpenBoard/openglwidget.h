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
#include "shadertest.h"
#include <QGLShader>
#include "shaderprogramwrapper.h"
#include <QOpenGLFunctions_3_0>
#include <QMap>
#include <QList>



class ListControll;
struct BrushBeginingIndex;
class DrawTextElm;
class DrawBrushElm;
class DrawElement;
class ShaderProgramWrapper;


/*
#include <QtAV/QtAV>
#include <QtAVWidgets/QtAVWidgets>

using namespace QtAV;
*/

#define STREAM_FRAME_RATE 10
#define STREAM_DURATION 60
#define TEXTURE_INDEX_BRUSH 1
#define MIN_RECT_SIZE 25
struct ColorMarker{
    int startIndex;
    QColor value;
};
enum EditingRectangleBindMode {EDIT_RECTANGLE_UNBINDED =0,EDIT_RECTANGLE_MOVE=1,EDIT_RECTANGLE_RESIZE=2};
class OGLWidget;

struct RectangleEditor {
    QRect rect;
    int leftCornerSize;
    volatile bool isEditingRectangleVisible = true;
    int editingRectangleMode = EDIT_RECTANGLE_UNBINDED;

};
struct AnimationFigure
{
    AnimationFigure( QRect rect, int type, int start, int stop )
    {
        this->rect = rect;
        this->type = type;
        this->start = start;
        this->stop = stop;
    }

    AnimationFigure(){};

    QRect rect;
    double persent = 0;
    bool fill = true;
    int type = 0;
    int start = -1;
    int stop = -1;
};


class Encoder;

struct DrawData{
    QString str;
    int index;
    bool IsPlay;
};

struct FBOWrapper{
    GLuint frameBuffer;
    GLuint bindedTexture;
    int errorStatus= -1;
    int tWidth=0,tHeight=0;
};
class OGLWidget : public QGLWidget, protected QOpenGLFunctions_3_0
{
    Q_OBJECT
   // Q_PROPERTY(QString  drawText READ getDrawText WRITE setDrawText NOTIFY drawTextChanged)
    QPoint mousePressPos;
    ShaderTest shaderWindow;

signals:
    void stopShowLastDrawingSignal();
public:


	enum shaderEnum {ALPHA_SHADER=0,SPIRAL_SHADER=1};
	void processMouse();
	ShaderProgramWrapper* getMainShader();
	void initPBO();
	void initShaderPrograms();
	QVector<ShaderProgramWrapper*> getShaderPrograms();
	bool isShaderSupported();
	void setShaderSupported(bool value);

    BrushManager m_manager;
    bool sucsessLoadTexture;
    void setFrameRate(int frameRate);
    void keyEventSignal(QKeyEvent *event);
    /*
     * |Future gradient
     */


  // bool isMousePlay = false;//play recorded mouse movement
   bool isMousePress = false;
   bool ismouseWasPressedBeforeDrag = false;  
    bool isClearFrameBuffer = false;//clear frame buffer



   DrawBrushElm *drawBrushElm = NULL;//record mouse movement
    GLuint brushTexture;
    GLuint brushTextureCurrentPlayed;

    GLuint backGroundTexture;





//bool isEditingRectangleBindedToCursor = false;
   RectangleEditor editingRectangle;//Draw element layout manager
   bool forseEditBoxDisable = false;

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
    void hideEvent(QHideEvent *);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *event);
    bool event(QEvent *e);
    QSize getTextureSize();



    /*
     * |Canvas control
     */
    void addAudioToList(QByteArray arr);
    void clearAudioList();
    void drawFigure (int x, int y, int width, int height, FigureType type, bool fill = true, QColor col = "#FF0000", float size = 2);


    QPoint drawWrapText( QString str ); // main draw function

    void fillText(QString str, QColor color,QFont textFont, int x, int y, int z = 0, float scale = 1);

    void pause(int ms);

    /*
     * |G/S
     */
    StatusDraw getStatus() const;

    void setDrawText( QString data );
    QString getDrawText();
    void recreate();
    /*
     * |encoder
    */
    bool getBusy() const;
    void setBusy( bool value);

    QImage getBackBuffer() const;
    void setBackBuffer(const QImage &value);



    void drawTexture(int x, int y, int width, int height, int index, int angle=0, float scaleX = 1, float scaleY = 1, int z = 0);
    void drawTexture(int x, int y, int width, int height, GLuint texture, int angle=0, float scaleX = 1, float scaleY = 1, int z = 0);

    int initTexture(GLuint &texture, int width, int height);
    void initFBDepthBuffer(GLuint &fbo_depth);
    void paintBrushInBuffer(FBOWrapper fboWrapper);
    FBOWrapper initFboWrapper(int width, int height, bool visibleOnly=true, bool forceLoad = false);
    QList<DrawElement *> &getList();
    void setList(const QList<DrawElement *> &value);
    bool getIsBrushWindowOpened() const;
    void setIsBrushWindowOpened(bool value);
    int getWax();
    int getWay();

    void paintBufferOnScreen(FBOWrapper buffer,int x , int y , int width, int height, int z = 0);

    void deleteFBO(FBOWrapper wrapper);

    void paintBrushInBuffer(GLuint& texture,Brush& currentBrushOfDrawSystem,FBOWrapper &fboWrapper,QVector<QPoint> coords, QVector<BrushBeginingIndex> brushes,int keyFrame);




    void drawQImage(int x, int y, QImage img, int z = 0);

    void myRenderText(QGLWidget *w, int x, int y, int z, const QString &text, const QColor &col = Qt::white, const QFont &font = QFont(), float scale = 1);


    bool isShowLastDrawing();
    void setShowLastDrawing(bool val);
    bool getShowLastDrawing();
    void stopShowLastDrawing();

    RectangleEditor * getEditingRectangle();
    void setEditingRectangle(const RectangleEditor &value);

    int getCurStatus() const;
    void setCurStatus(const StatusDraw &value);

    FBOWrapper getMouseFBO();
    void bindBuffer(GLuint buffer);

    QImage twiceImageSizeWithouScaling(QImage img);
    QOpenGLFunctions_3_0 *getOglFuncs();
    FBOWrapper getPingPongFBO();
    void useShader(ShaderProgramWrapper *shader);
    ShaderProgramWrapper *getTestShader();
    void disableShader();
    void enableShader();
public slots:
    void setAbleDrawing(bool value);
   // void clearFrameBuffer();
        void clearFrameBuffer(FBOWrapper fboWrapper);
    void hideBrushManager();
    void slotBlockEdited();
    bool drawAnimated( bool record );
    void stopAnimated();
    void pauseAnimated();
    void brushParamsChanged();
    void updateWindow();
    bool isRecord() const;

    int getDelay() const;
    void setDelay(int value);

    void clear(int x,int y,int width,int height);

    /*
     * | new method reDraw
     *
     */




    //void clearBuffer();
    void testWrap(int kIndexOfRow);
    GLuint loadTexture(QImage img,bool doubleSize=false);
    void deleteTexture(GLuint index); // gl_only delete only from video memory, can reload
    int loadTextureFromFile(QString path); // return index for reload + texture indefication
    /*
     *
     *
    */


    ListControll* getTimeLine();

    void displayText(const QString &text, QColor color,QFont font);
    void testRectangle();
    bool isInit();
    void setFileNameForRecords(QString ) ;


    void drawQImageFromTexture(int x, int y, QImage img, GLuint index, int z);
    void ShowHideShaderWindow();
    void testInit();
signals:
    void windowUpdating(int frameRate);
    void pauseSignal();
    void stopSignal();
    void startSignal();


private slots:
    void imageLoadedPictureSizeSlot(QSize);
    bool crossTextV2();

    void storeMousePos();

private:
    QStack<ShaderProgramWrapper*> currentShaderStack;
    int MOUSE_PROCESS_DELAY_MS=30;
QString fileNameForRecords;
  //  QMap <void* , QList<QByteArray>>  audioList;
    GLuint pixelBufferIDs[2];

    QList<QByteArray>  audioList;
    QOpenGLFunctions_3_0 *oglFuncs;

     QVector<ShaderProgramWrapper*> shaderPrograms;

    bool shaderSupported = false;
    ShaderProgramWrapper *mainShader;//Color,alpha,blur;
    ShaderProgramWrapper *test;//Color,alpha,blur;

         int frameRate = 25;
       bool mayShowRedRectangle = true;
    unsigned int current_millisecs =0;
    unsigned int last_milisecs_update = 0;
    unsigned int last_milisecs_drawn = 0;
    unsigned int last_mouse_process = 0;

    QVector<GLenum> attachment;
    FBOWrapper mouseFBO,pingpongFBO;

     QMessageBox ms_for_debug;
    bool pressedCtrl = false;
    bool pressedShift = false;

    bool showingLastDrawing = false;
    int currentLastDrawingPointIterator = 0;
    //GLuint ShaderProgram;
       bool firstUpdate = true;
     bool isPainting;
    QImage img;
    ListControll *timeLine = NULL;

         Brush currentBrushOfLastDrawing;
   // GLuint    fbo,// The frame buffer object
    //fbo_depth, // The depth buffer for the frame buffer object

    //fbo_texture; // The texture object to write our frame buffer object to
    QString drawText;
    bool bRecord;
    void generateFrames();
    volatile StatusDraw curStatus; // 0 - stop; 1 - play; -1 - pause
    QThread drawThread;
    AV_REncoder *m_encoder = NULL;
    bool able_drawing = false;

    /*
     * |Сavas property
    */





    /*
     * |not use
     */


    /*
     * |not use
    */
    /*QFont textFont;
    QFont mainTextFont;
    QFontMetrics *fMetrics;
    int indexInList;
    int deleteWT;*/

    /*
     * |new property
     */
    QVector<int> wrapShift;
    QVector <QImage> imgList;
    QVector <GLuint> textureList;
    QList<DrawElement *> list_1;
    QList<DrawElement *> list_2;

    int maxDrawElm = 0;
    int delay;

    int maxWidth; //размер поле, где виводится текст
    int realDelay;
    //int mousePlayIndex = 0;//current point of stored points arr



    int widthToClean=0;

    double timer_test;
    QTimer tickTimer;


    bool busy = false;
    bool isClose = false;
    bool curentList = false;
    bool init = false;





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

