
#include "openglwidget.h"
#include <qglfunctions.h>
#include "drawSystem/drawsystem.h"
#include "../TimeLine/listcontroll.h"
#define GLWIDGET_SIZE       640,480
/*
 *scroll
 *
int k = canvas->property("scroll").toInt() - 10;
canvas->setProperty("scroll", k);
*/

GLuint OGLWidget::loadTexture(QImage img){

    if(img.isNull()) // QCoreApplication::applicationDirPath()+"/star.png"
    {
        //loads correctly
        qWarning() << "ERROR LOADING IMAGE";// + QCoreApplication::applicationDirPath()+"/star.png";
        return -1;
    }

    ////qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();

    ////qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();
    // //qDebug() << "image converted to GL format";

    QImage GL_formatted_image = convertToGLFormat(img);


    if(GL_formatted_image.isNull())
        qWarning() << "IMAGE IS NULL";
    else
    {
        qWarning() << "IMAGE NOT NULL";
    }
    //generate the texture name
    //glEnable(GL_TEXTURE_2D); // Enable texturing
    GLuint texture;

       glGenTextures(1, &texture); // Obtain an id for the texture

       glBindTexture(GL_TEXTURE_2D, texture); // Set as the current texture
 //qDebug(" after  glBindTexture(GL_TEXTURE_2D, texture);");
       //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


       glTexImage2D(GL_TEXTURE_2D, 0, 4, GL_formatted_image.width(), GL_formatted_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits());

       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

     //  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

       glBindTexture(GL_TEXTURE_2D, 0);
       glDisable(GL_TEXTURE_2D);

//qDebug("before int realIndex = index; ");
       /*GLenum error = glGetError();
       if(error != 0)
           sucsessLoadTexture = true;
        else
           sucsessLoadTexture = false;
*/
       //if(glGetError())
          // return -1;

       return texture;
       //bind the texture ID
}

void OGLWidget::deleteTexture(GLuint index)
{
      glDeleteTextures(1, &index);
}

int OGLWidget::loadTextureFromFile(QString path)
{
    QImage img(path);
    if(img.isNull()) // QCoreApplication::applicationDirPath()+"/star.png"
    {
        //loads correctly
        qWarning() << "ERROR LOADING IMAGE  " + path;
        return 0;
    }
    return loadTexture(img);

}

void OGLWidget::drawTexture(int x, int y, int width, int height, GLuint texture,int angle,float scaleX,float scaleY, int z){
//loadTextures();
  // glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    qglColor(Qt::white);
    glBindTexture(GL_TEXTURE_2D, texture);

    int cx=x+width/2,cy=y+height/2;

    glPushMatrix();

    glTranslatef(cx, cy, 0);
        glScalef(scaleX, scaleY, 1.f);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-cx, -cy, 0);

    glBegin(GL_QUADS);
            //Draw Picture
    glTexCoord2i(0,0); glVertex3i(x, y+height, z);
    glTexCoord2i(0,1); glVertex3i(x,y, z);
    glTexCoord2i(1,1); glVertex3i(x+width,y,z);
    glTexCoord2i(1,0); glVertex3i(x+width, y+height, z);
    glEnd();
     glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
void OGLWidget::drawTexture(int x, int y, int width, int height, int index, int angle, float scaleX, float scaleY, int z)
{
    drawTexture(x, y, width, height, index, angle, scaleX, scaleY, z);
    //// //qDebug() << "void OGLWidget::drawTexture(int x, int y, int width, int height, int index)";
}


QList<DrawElement *> &OGLWidget::getList()
{
    //qDebug () << "get list";
    if(!curentList)
        return list_1;
    else
        return list_2;
}

void OGLWidget::setList(const QList<DrawElement *> &value)
{
   for( DrawElement* elm : value)
    {
        if(elm != NULL && !timeLine->isBlocked)//&& timeLine->getMaxTrackTime() > 0)
        {
            elm->setDrawWidget(this);   //12345

        }
        else
            break;
    }
    if(curentList)
    {
        list_1 = value;
    }
    else
    {
        list_2 = value;
    }
    curentList = !curentList;    
}
void OGLWidget::paintBrushInBuffer(GLuint& texture,Brush& currentBrushOfDrawSystem,FBOWrapper& fboWrapper,QVector<QPoint> coords,QVector<BrushBeginingIndex> brushes,int keyFrame){
    if (fboWrapper.errorStatus==-1)qDebug() << "BAD BUFFER";
   // qDebug()<<"binded buffer in paint brush:"<< fboWrapper.frameBuffer;
   // glBindFramebuffer(GL_FRAMEBUFFER , fboWrapper.frameBuffer); // Bind our frame buffer for rendering
int recordedBrushN = 0;

////qDebug() << "keyFrame:"<<keyFrame;

//bool isBrushUsed = false;
//TEST
glBegin(GL_TRIANGLES);

    glVertex2f(-1.0f, -0.5f);    // lower left vertex
    glVertex2f( 1.0f, -0.5f);    // lower right vertex
    glVertex2f( 0.0f,  0.5f);    // upper vertex

    glEnd();

    for (; recordedBrushN < brushes.length(); )
    {
        ////qDebug() << "brushes["<<recordedBrushN<<"].pointIndex"<<brushes[recordedBrushN].pointIndex;
    if (brushes[recordedBrushN].pointIndex==keyFrame){
       //qDebug() << "KEY_FRAME:"<<keyFrame;
       // //qDebug() << "mouse play index:"<<keyFrame;

        currentBrushOfDrawSystem = brushes[recordedBrushN].brush;

        texture = loadTexture(currentBrushOfDrawSystem.color_img);
        qDebug() << "recordedBrushN:"<<recordedBrushN;

       // isBrushUsed=true;
     ////qDebug() << "recordedBrushN:"<<recordedBrushN;
     break;
    }
    recordedBrushN++;
    }

    //glUseProgram(ShaderProgram);
    glBindTexture(GL_TEXTURE_2D,texture);
   // if (isBrushUsed) {
     //   //qDebug() << "recordedBrushN:" << recordedBrushN;
      //  currentBrushOfDrawSystem = brushes[recordedBrushN].brush;
    //}

     ////qDebug() << "recordedBrushN:"<<recordedBrushN;
    //if (recordedBrushN>=brushes.length())recordedBrushN=brushes.length()-1;
   // //qDebug() << "recordedBrushN:"<<recordedBrushN;


    QSize brushTextureSize = getTextureSize();
    int BRUSH_SIZE=currentBrushOfDrawSystem.size + currentBrushOfDrawSystem.size_delta/2 - rand()%(int)(currentBrushOfDrawSystem.size_delta + 1);
    ////qDebug() << "LOADED BRUSH SIZE DRAW:"<<BRUSH_SIZE;
    float scaleX=1,scaleY=1;
    float randScalePtX = 0;
    float randScalePtY = 0;
    if(currentBrushOfDrawSystem.afinn != 0)
    {

        randScalePtX = (int)currentBrushOfDrawSystem.afinn/2 - rand() % (1 + (int)currentBrushOfDrawSystem.afinn);
        randScalePtY = (int)currentBrushOfDrawSystem.afinn/2 - rand() % (1 + (int)currentBrushOfDrawSystem.afinn);
    }
   // qDebug() << "randScalePtX_" << m_manager.getAffine() << "__AFTER" << randScalePtX << " " << randScalePtY;

    float MAX_SCALE = 2;
    //100 - 2 (MAX_SCALE)
    //1 - x
    //x = 2/100=0.02
    if(randScalePtX!=0)
        scaleX=MAX_SCALE/randScalePtX;
    if(randScalePtY!=0)
        scaleY=MAX_SCALE/randScalePtY;
    double koff = 1;
    if(brushTextureSize.height() != 0)
     koff = brushTextureSize.width()/brushTextureSize.height();
     int maxAngle = currentBrushOfDrawSystem.angle_delta;

     int angle = 0;
     if (maxAngle > 0){
     angle=maxAngle/2 - rand() % (maxAngle);
    }
        int maxDispers = (int)currentBrushOfDrawSystem.dispers;
        int i=1;
        if (maxDispers>0 && currentBrushOfDrawSystem.count>0) i=currentBrushOfDrawSystem.count;
        int imgUniform = glGetUniformLocation(ShaderProgram,"vUV");
          glUniform2i(imgUniform,0,0);
         // int bloorStepUnifrom = glGetUniformLocation(ShaderProgram,"bloorStep");
           // glUniform1i(bloorStepUnifrom,currentBrushOfDrawSystem.blur);

          int colorUniform = glGetUniformLocation(ShaderProgram,"toColor");
          QColor color = currentBrushOfDrawSystem.color_main;
          float r = (float)color.red()/255;
          float g = (float)color.green()/255;
          float b = (float)color.blue()/255;
          float a = (float)currentBrushOfDrawSystem.opacity/100;
         // //qDebug() << r << g << b << a;
            glUniform4f(colorUniform,r,g,b,a);

        for (;i>0;i--)
        {
             int dispersX = 0;
             int dispersY = 0;
             if ((int)currentBrushOfDrawSystem.dispers>0){
                 dispersX = maxDispers/2 - rand() % (maxDispers);
                 dispersY = maxDispers/2 - rand() % (maxDispers);
        }
             int xPos = 0;
             int yPos = 0;
                // //qDebug()<<"mouseRecorder.getBrushBeginings().length():"<<brushes.length();
                 // //qDebug() << "xPos:"<<xPos;
                 // //qDebug() << "yPos:"<<yPos;
                 xPos=coords[keyFrame].x();
                 yPos=coords[keyFrame].y();
                 // //qDebug() << "AFTER123";
               // //qDebug() << "x:"<<xPos;
               // //qDebug() << "y:"<<yPos;
                ////qDebug() << "keyFrame:"<<keyFrame;
                    // if (mousePlayIndex >= coords.length()-1)
                   //  {
                    // isMousePlay=false;
                    //     stopShowLastDrawing();
                   //  mousePlayIndex=0;
                   //  }
                     //else
                     // mousePlayIndex++;


        drawTexture(xPos-BRUSH_SIZE/2 + dispersX ,yPos-BRUSH_SIZE/koff/2 + dispersY,BRUSH_SIZE,BRUSH_SIZE/koff,
                texture,angle,scaleX,scaleY);
        }
// glUseProgram(NULL);


glBindTexture(GL_TEXTURE_2D,0);
//glBindFramebuffer(GL_FRAMEBUFFER , 0); // Unbind our texture
}
bool OGLWidget::isShowLastDrawing(){
    return showingLastDrawing;
}
void OGLWidget::setShowLastDrawing(bool val){
     showingLastDrawing=val;
}
void OGLWidget::stopShowLastDrawing(){
    showingLastDrawing=false;
    currentLastDrawingPointIterator=0;
    emit stopShowLastDrawingSignal();
}

bool OGLWidget::getShowLastDrawing(){
    return showingLastDrawing;
}

void OGLWidget::slotBlockEdited()
{
    //qDebug() << "1234566666666666666";
 // ms_for_debug.show();
 /*QPoint t = timeLine->getSelectedBlockPoint();
editingRectangle.rect = timeLine->getDrawRect(t.x(), t.y());
*/
selElm = QPoint(-1,-1);
}


RectangleEditor* OGLWidget::getEditingRectangle()
{
    return &editingRectangle;
}

void OGLWidget::setEditingRectangle(const RectangleEditor &value)
{
    editingRectangle = value;
}

void OGLWidget::setFrameRate(int fps)
{
frameRate=fps;
}

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    setFixedSize(GLWIDGET_SIZE);
     wax=width(); way=height(); // начальный размер окна
    init = false;
    timeLine = new ListControll();
    connect(timeLine,SIGNAL(stopSignal()),this,SIGNAL(stopSignal()));
    connect(timeLine,SIGNAL(playSignal()),this,SIGNAL(startSignal()));
    connect(timeLine,SIGNAL(pauseSignal()),this,SIGNAL(pauseSignal()));

    connect(this,SIGNAL(windowUpdating(int)),timeLine,SLOT(addMsToTimerValue(int)));


    connect(timeLine,SIGNAL(blockEditedSignal()),this,SLOT(slotBlockEdited()));

  connect(timeLine,SIGNAL(focusFoundSignal()),this,SLOT(hideBrushManager()));

    isPainting = false;
    selElm = QPoint(-1,-1); //because it undefined

    //qRegisterMetaType<DrawData>("DrawData");
    // engine()->rootContext()->setContextProperty(QLatin1String("forma"), this);
    m_encoder = new AV_REncoder(this);
    editingRectangle.rect.setWidth(100);
    editingRectangle.rect.setHeight(100);
    editingRectangle.rect.setX(50);
    editingRectangle.rect.setY(50);
    editingRectangle.leftCornerSize=10;
    bRecord = false;
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    //this->setResizeMode(QQuickWidget::SizeRootObjectToView ); //TODO
    /*
     * init
    */

    //
    ColorMarker startMarker;
    startMarker.startIndex=0;
    //startMarker.value=getMainFillColor();



    maxWidth; //размер поле, где выводится текст




    delay = 1000/3;
    //listStr[0] = 0;

    curStatus = STOP;
    //tickTimer.setSingleShot(false);
   // tickTimer.setInterval(1000/25);
    mouseTimer.setInterval(drawBrushElm->SPEED_OF_RECORDING_MS);
    mouseTimer.setSingleShot(false);
    realDelay = 0;

   // maxWidth = width() - marginLeft;

    //stringList.reserve(600000);




    //OPENGL
   //setFormat(QGLFormat(QGL::SampleBuffers | QGL::DoubleBuffer | QGL::DepthBuffer)); // Двойная буферизация
     QGLFormat format;
     format.setProfile(QGLFormat::CompatibilityProfile);
     format.setVersion(3,0);
     format.setDoubleBuffer(true);
     setFormat(format);
   glDepthFunc(GL_LEQUAL); // Буфер глубины
   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
   timer->start(0);
   connect(&mouseTimer, SIGNAL(timeout()), this, SLOT(storeMousePos()));
   mouseTimer.start();



   //for loading current text in to fist init block
   /*DrawTextElm drawTTElements(this);
   QList <Unit*>mUnitList;

   Unit unit;
   mUnitList.append(&unit);
   drawTTElements.setUnitList(mUnitList);
   drawTTElements.setUnParsestring("", "");
   drawTTElements.save("curent");
 // timeLine->loadCurrentTextInTheFirstBlockWhenInit();
*/
   getTimeLine()->setIsProjectChanged(false);
}
void OGLWidget::bindBuffer(GLuint buffer){
    glBindFramebuffer(GL_FRAMEBUFFER,buffer);
}

OGLWidget::~OGLWidget()
{

    this->stopAnimated();
        qApp->processEvents();
    if(timeLine != NULL)
        delete timeLine;

    if(m_encoder != NULL);
        delete m_encoder;

    if (drawBrushElm !=NULL)
        delete drawBrushElm;
}



void OGLWidget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    wax=nWidth;
    way=nHeight;
    // //qDebug() << "CALL RESIZE";
}
void OGLWidget::paintBufferOnScreen( FBOWrapper buffer,int x, int y, int width, int height, int z){
     if (buffer.errorStatus==-1)qDebug() << "BAD BUFFER";
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,buffer.bindedTexture);
   // qglColor(Qt::green);//TO SEE TEXTURE
    glBegin(GL_QUADS);
            //Draw Picture
    glTexCoord2i(0,0); glVertex3i(x, y+height, z);
    glTexCoord2i(0,1); glVertex3i(x,y, z);
    glTexCoord2i(1,1); glVertex3i(x+width,y,z);
    glTexCoord2i(1,0); glVertex3i(x+width, y+height, z);

   /*
    glTexCoord2i(0,0); glVertex2i(0,0);
    glTexCoord2i(0,1); glVertex2i(0,way);
    glTexCoord2i(1,1); glVertex2i(wax,way);
    glTexCoord2i(1,0); glVertex2i(wax,0);*/

    glEnd();
   // glDeleteTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void OGLWidget::paintBrushInBuffer(FBOWrapper fboWrapper) {
glBindFramebuffer(GL_FRAMEBUFFER , fboWrapper.frameBuffer); // Bind our frame buffer for rendering
//glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT); // Push our glEnable and glViewport states
//glViewport(0, 0, window_width, window_height); // Set the size of the frame buffer view port

//glClearColor (0.0f, 0.0f, 1.0f, 1.0f); // Set the clear colour
//glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the depth and colour buffers
//glLoadIdentity();  // Reset the modelview matrix

//fillText("DEBUG TEXT TO BUFER",QColor(Qt::white),40,40);
   // int PointSize = 10;

       // glPointSize(PointSize);
    //glLineWidth(PointSize);
   // glEnable(GL_TEXTURE_2D);
        //// //qDebug() << "before index";
//// //qDebug() << "paint brush in buffer";
    GLuint texture = brushTexture;
    //// //qDebug()<<"texture:"<<texture;
  // if (!ismouseWasPressedBeforeDrag)

       /* glBegin (GL_POINTS);
        glColor3f (1.0, 0.4, 0.4);
        glVertex3f (mousePos.x(), mousePos.y(),0.0);
        // //qDebug() << mousePos.x();
        glEnd();*/
    //qglColor(m_manager.getColor());
//glUseProgram(ShaderProgram);

         glBindTexture(GL_TEXTURE_2D,texture);
        QSize brushTextureSize = getTextureSize();
        int BRUSH_SIZE=m_manager.getSize() + m_manager.getSizeDelta()/2 - rand()%(int)(m_manager.getSizeDelta() + 1);
        float scaleX=1,scaleY=1;
        float randScalePtX = 0;
        float randScalePtY = 0;
        if(m_manager.getAffine() != 0)
        {
            randScalePtX = m_manager.getAffine()/2 - rand() % (1 + (m_manager.getAffine()));
            randScalePtY = m_manager.getAffine()/2 - rand() % (1 + (m_manager.getAffine()));
        }
       // qDebug() << "randScalePtX_" << m_manager.getAffine() << "__AFTER" << randScalePtX << " " << randScalePtY;

        float MAX_SCALE = 2;
        //100 - 2 (MAX_SCALE)
        //1 - x
        //x = 2/100=0.02
        if(randScalePtX!=0)
            scaleX=MAX_SCALE/randScalePtX;
        if(randScalePtY!=0)
            scaleY=MAX_SCALE/randScalePtY;
        qDebug() << "scale x:"<<scaleX;
                    qDebug () << "scale y:"<<scaleY;
       // // //qDebug() <<"scaleX:"<<scaleX;
       // // //qDebug() <<"scaleY:"<<scaleY;
        //// //qDebug() << "brushSize.width():"<<brushTextureSize.width();
        //// //qDebug() << "brushSize.height():"<<brushTextureSize.height();

        double koff = 1;
        if (brushTextureSize.height()>0)koff=brushTextureSize.width()/brushTextureSize.height();
         int maxAngle = m_manager.getAngleDelta();

         int angle = 0;
         if (maxAngle > 0){
         angle=maxAngle/2 - rand() % (maxAngle);
        }
            int maxDispers = (int)m_manager.getDisepers();
            int i=1;
            if (maxDispers>0 && m_manager.getCount()>0) i=m_manager.getCount();

            int imgUniform = glGetUniformLocation(ShaderProgram,"vUV");
              glUniform2i(imgUniform,0,0);

              //int bloorStepUnifrom = glGetUniformLocation(ShaderProgram,"bloorStep");
              // glUniform1i(bloorStepUnifrom,m_manager.getCreatedBrush().blur);




              int colorUniform = glGetUniformLocation(ShaderProgram,"toColor");
              QColor color = m_manager.getColor();
              float r = (float)color.red()/255;
              float g = (float)color.green()/255;
              float b = (float)color.blue()/255;
              float a = (float)m_manager.getOpacity()/100;
             // //qDebug() << r << g << b << a;
                glUniform4f(colorUniform,r,g,b,a);
            for (;i>0;i--)
            {
                 int dispersX = 0;
                 int dispersY = 0;
                 if ((int)m_manager.getDisepers()>0){
                     dispersX = maxDispers/2 - rand() % (maxDispers);
                     dispersY = maxDispers/2 - rand() % (maxDispers);
            }
                 int xPos = 0;
                 int yPos = 0;
                  xPos = mousePos.x();
                  yPos = mousePos.y();

////qDebug() <<"mousePos.x() = " << mousePos.x() << " mousePos.y() = " << mousePos.y();

            drawTexture(xPos-BRUSH_SIZE/2 + dispersX ,yPos-BRUSH_SIZE/koff/2 + dispersY,BRUSH_SIZE,BRUSH_SIZE/koff,
                    texture,angle,scaleX,scaleY, 1000);
            }
              //glUseProgram(NULL);
        /*
    else{
      glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D,texture);
      QSize brushTextureSize = getTextureSize();
      int BRUSH_SIZE=30;
      // //qDebug() << "brushSize.width():"<<brushTextureSize.width();
      // //qDebug() << "brushSize.height():"<<brushTextureSize.height();
      double koff = brushTextureSize.width()/brushTextureSize.height();

      QPainterPath path;
          path.moveTo(prevMousePos);
          path.lineTo(mousePos);
          QPointF from = prevMousePos;
      for (int i=0;i<100;i+=20 )
      {
        QPointF to = path.pointAtPercent(i);
      drawTexture(from.x()-BRUSH_SIZE/2 ,from.y()-BRUSH_SIZE/koff/2,BRUSH_SIZE,BRUSH_SIZE/koff,texture);
      drawTexture(to.x()-BRUSH_SIZE/2 ,to.y()-BRUSH_SIZE/koff/2,BRUSH_SIZE,BRUSH_SIZE/koff,texture);
      from=to;
      }
      glDisable(GL_TEXTURE_2D);
       prevMousePos.setX(mousePos.x());
       prevMousePos.setY(mousePos.y());
    }*/
    // glDisable(GL_TEXTURE_2D);



glBindTexture(GL_TEXTURE_2D,0);
glBindFramebuffer(GL_FRAMEBUFFER , 0); // Unbind our texture
   //FRAMEBUFFER PART


//saveFrameBufferToTexture();





//glPopAttrib(); // Restore our glEnable and glViewport states


}

void OGLWidget::initShader(){
    QString fragmentShaderCode;
    QString vertexShaderCode;
    QString shaderDir = QDir::currentPath();
     QFile fragmentShadeFile(":/openGL/shaders/fragmentShader.glsl");
     if(fragmentShadeFile.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QTextStream in(&fragmentShadeFile);
         fragmentShaderCode = in.readAll();
         //qDebug() << "fragmentShaderCode:"<<fragmentShaderCode;
     }
    else
         qDebug() << "error on fragmentShader.glsl open path: "<<shaderDir+"/shaders/fragmentShader.glsl";

     QFile vertexShaderFile(":/openGL/shaders/vertexShader.glsl");
     if(vertexShaderFile.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QTextStream in(&vertexShaderFile);
         vertexShaderCode = in.readAll();
     }
     else
           //qDebug() << "error on vertexShader.glsl open path: "<<shaderDir+"/shaders/vertexShader.glsl";

      ShaderProgram = glCreateProgram();
      GLuint vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
      GLuint fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);

      const GLchar* p[1];
      p[0] = vertexShaderCode.toLatin1().constData();
      GLint Lengths[1];
      Lengths[0]= vertexShaderCode.length();
      glShaderSource(vertexShaderObj, 1, p, Lengths);

      const GLchar* p2[1];
      p2[0] = fragmentShaderCode.toLatin1().constData();
      GLint Lengths2[1];
      Lengths2[0]= fragmentShaderCode.length();
      glShaderSource(fragmentShaderObj, 1, p2, Lengths2);

      glCompileShader(vertexShaderObj);
      glCompileShader(fragmentShaderObj);

      //Get compile status and errors detected by compiler
      GLint success;
      glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &success);
      if (!success) {
          GLchar infoLog[1024];
          glGetShaderInfoLog(vertexShaderObj, sizeof(infoLog), NULL, infoLog);
            //qDebug() <<"Error compiling shader type:" << "GL_VERTEX_SHADER" << infoLog;
      }
      glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &success);
      if (!success) {
          GLchar infoLog[1024];
          glGetShaderInfoLog(fragmentShaderObj, sizeof(infoLog), NULL,infoLog);
          //qDebug() <<"Error compiling shader type:" << "GL_FRAGMENT_SHADER" << infoLog;
      }

  glAttachShader(ShaderProgram,vertexShaderObj);
  glAttachShader(ShaderProgram,fragmentShaderObj);
glLinkProgram(ShaderProgram);
glDeleteShader(vertexShaderObj);
glDeleteShader(fragmentShaderObj);
glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
GLchar errorLog[1024];
if (success == 0) {
    glGetProgramInfoLog(ShaderProgram, sizeof(errorLog), NULL, errorLog);
    //qDebug() << "Error linking shader program:" << errorLog;
}
else
    //qDebug() << "Linking shader program success";
glValidateProgram(ShaderProgram);

    //glLinkProgram(program);
    //glUseProgram(program);
}





void OGLWidget::initFBDepthBuffer(GLuint &fbo_depth) {
glGenRenderbuffers(1, &fbo_depth); // Generate one render buffer and store the ID in fbo_depth
glBindRenderbuffer(GL_RENDERBUFFER , fbo_depth); // Bind the fbo_depth render buffer
GLenum error = glGetError();

qDebug() << "GL_ERROR_STATUS glBindRenderbuffer:"<<error;
//glRenderbufferStorage(GL_RENDERBUFFER , GL_DEPTH_COMPONENT, wax, way); // Set the render buffer storage to be a depth component, with a width and height of the window

error = glGetError();
qDebug() << "GL_ERROR_STATUS glRenderbufferStorage:"<<error;

//glFramebufferRenderbuffer(GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_RENDERBUFFER ,fbo_depth); // Set the render buffer of this buffer to the depth buffer
 //error = glGetError();
////qDebug() << "GL_ERROR_STATUS glFramebufferRenderbuffer:"<<error;
glBindRenderbuffer(GL_RENDERBUFFER , 0); // Unbind the render buffer
 error = glGetError();
//qDebug() << "GL_ERROR_STATUS glBindRenderbuffer:"<<error;
}

int OGLWidget::initTexture(GLuint &texture) {
    makeCurrent();
    glEnable(GL_TEXTURE_2D);
    //glDeleteTextures(1,&fbo_texture);
glGenTextures(1, &texture); // Generate one texture

glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture fbo_texture

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wax, way, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); // Create a standard texture with the width and height of our window

// Setup the basic texture parameters
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// Unbind the texture
glBindTexture(GL_TEXTURE_2D, 0);
glDisable(GL_TEXTURE_2D);
return glGetError();
}


FBOWrapper OGLWidget::initFboWrapper(bool visibleOnly) {
    glGetError();

    makeCurrent();
    qDebug () << "                                                                  INIT FBO";

    FBOWrapper fboWrapper;
    fboWrapper.errorStatus=0;
    GLuint fbo=0;
    GLuint depth_buffer=0;
    GLuint fbo_texture=0;
    qDebug() << "fbo:"<<fbo;
    qDebug()<< "depth_buffer:"<<depth_buffer;
    qDebug() << "fbo_texture:"<<fbo_texture;
    GLenum error = glGetError();

    //qDebug() << "GL_ERROR_STATUS initFrameBuffer:"<<error;
  //  glEnable(GL_DEPTH_TEST);

    qDebug() << "GL_ERROR_STATUS initFrameBuffer:"<<error;
    if(error != 0)
    {
        fboWrapper.errorStatus = error;
        return fboWrapper;
    }
    qDebug() << 1;
    if(visibleOnly)
    if(!isVisible() || !isInit())
    {
        fboWrapper.errorStatus = -1;
        return fboWrapper;
    }

    glGenFramebuffers(1, &fbo); // Generate one frame buffer and store the ID in fbo

qDebug() << 2;

qDebug() << 3;
     error = glGetError();
     if(error != NULL)
     {
         fboWrapper.errorStatus = error;
         return fboWrapper;
     }
//initFBDepthBuffer(depth_buffer); // Initialize our frame buffer depth buffer
 error = initTexture(fbo_texture); // Initialize our frame buffer texture
 if(error != NULL)
 {
     fboWrapper.errorStatus = error;
     return fboWrapper;
 }
glBindFramebuffer(GL_FRAMEBUFFER , fbo); // Bind our frame buffer
qDebug () << "texture inited id:"<<fbo_texture;

error = glGetError();
if(error != NULL)
{
    fboWrapper.errorStatus = error;
    return fboWrapper;
}
qDebug() << "GL_ERROR_STATUS initFrameBufferTexture:"<<error;
qDebug() << "attachment.count():"<<attachment.count();
//attachment.append(GL_COLOR_ATTACHMENT0+attachment.count());
attachment.append(GL_COLOR_ATTACHMENT0);
glFramebufferTexture2D(GL_FRAMEBUFFER , attachment.last() , GL_TEXTURE_2D, fbo_texture, 0); // Attach the texture fbo_texture to the color buffer in our frame buffer
//glDrawBuffer(GL_COLOR_ATTACHMENT1);

//glFramebufferRenderbuffer(GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_RENDERBUFFER , depth_buffer); // Attach the depth buffer fbo_depth to our frame buffer
error = glGetError();
if(error != NULL)
{
    fboWrapper.errorStatus = error;
    return fboWrapper;
}
//qDebug() << "GL_ERROR_STATUS:"<<error;
GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER ); // Check that status of our generated frame buffer

if (status != GL_FRAMEBUFFER_COMPLETE ) // If the frame buffer does not report back as complete
{

 qDebug() << "Couldn't create frame buffer\n" ; // Output an error to the console
//exit(0); // Exit the application
 fboWrapper.errorStatus=-1;

}


glBindFramebuffer(GL_FRAMEBUFFER , 0); // Unbind our frame buffer

fboWrapper.bindedTexture=fbo_texture;
fboWrapper.frameBuffer=fbo;
GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (err != GL_FRAMEBUFFER_COMPLETE) {
        qWarning() << "Can't create framebuffer:" << err;
         fboWrapper.errorStatus=-1;
    }



return fboWrapper;
}

void OGLWidget::initializeGL()
{
     qDebug() << "initializeGL";

    initializeGLFunctions();
    makeCurrent();
glEnable(GL_DEPTH_TEST);
    qglClearColor(Qt::black); // Черный цвет фона
    qDebug() << "initializeGLFunctions";
     //glEnable(GL_TEXTURE_2D);
    backGroundTexture = loadTextureFromFile(":/ThirdPart/images/start.png");
    m_manager.getCreatedBrush().color_img=BrushPainter::getInstance()->applyColor(m_manager.getCreatedBrush());
    brushTexture = loadTexture(m_manager.getCreatedBrush().color_img);
    //loadTextureFromFile(":/ThirdPart/images/brush.png");
    //initFrameBuffer(); // Create our frame buffer object
    mainFBO=initFboWrapper(false);
     //initShader();
    setAutoBufferSwap(false);
    qApp->processEvents(QEventLoop::AllEvents, 1000);
    qDebug() << "A";
    drawBrushElm = new DrawBrushElm(this,this);//record mouse movement
    qDebug() << "B";
   /* list_1.append(GenerationDrawElement("kaka.text", this, 0));
    list_1.append(GenerationDrawElement("brush.png", this, 0));*/

   connect(&m_manager,SIGNAL(currentBrushChanged()),this,SLOT(brushParamsChanged()));

}

void OGLWidget::moveEvent(QMoveEvent *event)
{
    /*if(isVisible())
    {
        QPoint curentPos = this->pos();
        curentPos.setY(curentPos.y() + this->height());
        timeLine->setViewPosition(curentPos);
    }*/
}


void OGLWidget::destroy(bool destroyWindow, bool destroySubWindow){
    glDeleteFramebuffers(1,&mainFBO.frameBuffer);
    glDeleteTextures(1,&mainFBO.bindedTexture);
    //glDeleteRenderbuffers(1,&render_buf);

}
FBOWrapper OGLWidget::getMainFBO(){
    return mainFBO;
}

void OGLWidget::clearFrameBuffer(FBOWrapper fboWrapper){

    makeCurrent();
  //  glBindFramebuffer(GL_FRAMEBUFFER , fboWrapper.frameBuffer); // Bind our frame buffer for rendering
   // glClearColor(0.1f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет
   std::vector<GLubyte> emptyData(wax * way * 4, 0);
   glBindTexture(GL_TEXTURE_2D, fboWrapper.bindedTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, wax, way, GL_RGBA, GL_UNSIGNED_BYTE, &emptyData[0]);
     // glBindTexture(GL_TEXTURE_2D,0);
  glBindTexture(GL_TEXTURE_2D, 0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        isClearFrameBuffer=false;
     // glBindFramebuffer(GL_FRAMEBUFFER , 0);
      // qDebug()<<"clearFrameBuffer";


}

void OGLWidget::deleteFBO(FBOWrapper wrapper)
{
    makeCurrent();
    glDeleteTextures(1,&wrapper.bindedTexture);
    glDeleteFramebuffers(1,&wrapper.frameBuffer);

}

void OGLWidget::paintGL()
{
    //glDrawBuffer(GL_COLOR_ATTACHMENT1);
     glBindFramebuffer(GL_FRAMEBUFFER , 0);

    //// qDebug() << "isClearFrameBuffer:"<<isClearFrameBuffer;
    if(isClearFrameBuffer)
        clearFrameBuffer(mainFBO);
//glDrawBuffer(GL_COLOR_ATTACHMENT0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glClearColor(0.0,0.0,0.0,0.0);
    //glClearStencil(0);
    timeLine->update();

    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
     //  glShadeModel(GL_SMOOTH);
       // Сглаживание точек
      // glEnable(GL_POINT_SMOOTH);
      // glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
       // Сглаживание линий
       //glEnable(GL_LINE_SMOOTH);
       //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

      // glEnable(GL_POLYGON_SMOOTH);
      // glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
      // glEnable(GL_MULTISAMPLE);

       glLoadIdentity(); // загружаем матрицу
       glOrtho(0,wax,way,0, -1000000, 200000); // подготавливаем плоскости для матрицы
       glEnable(GL_BLEND);
       glEnable(GL_ALPHA_TEST);

      // glDepthMask(false);
       glDepthFunc(GL_LEQUAL); // this maybe problem
       glAlphaFunc(GL_GREATER,0);
       glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
       //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
       //glBlendEquation ( GL_FUNC_ADD ) ;
     // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



//WRITE TO FRAME BUFER FROM HERE
   // glBindFramebuffer(GL_FRAMEBUFFER,0);
    qglColor(Qt::white);
    drawTexture(0, 0, wax, way, backGroundTexture, 0, 1, 1, -100000);
//WRITE TO SCREEN FROM HERE
//drawTextBuffer(10,10,400,400);



    GLint x1 = editingRectangle.rect.x();
      GLint y1 = editingRectangle.rect.y();
        GLint x2 = editingRectangle.rect.x()+editingRectangle.rect.width();
        GLint y2 = editingRectangle.rect.y()+editingRectangle.rect.height();
        bool canDrawByMouse = true;

        int leftCornerX1=x1-editingRectangle.leftCornerSize/2;
         int leftCornerY1=y1-editingRectangle.leftCornerSize/2;
                 int leftCornerX2=x1 + editingRectangle.leftCornerSize/2;
                  int leftCornerY2=y1 + editingRectangle.leftCornerSize/2;



//if (isMousePlay)paintBrushInBuffer(true);

 ////qDebug() << "PREDRAW";

for(int i = 0; !timeLine->isBlocked && i < getList().size(); i++)
{
    ////qDebug() << "draw   " << i;
    if( getList()[i] != NULL && timeLine->getMaxTrackTime() > 0)
        getList()[i]->paint();
}

if (editingRectangle.isEditingRectangleVisible && !forseEditBoxDisable && !isPainting && getStatus()!= PLAY)
{
   // paintBufferOnScreen(0, 0, wax, way);
    //rectangle
    glLineWidth(3);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3i(x1,y1, 100);
    glVertex3i(x2,y1, 100);

    glVertex3i(x2,y1, 100);
    glVertex3i(x2,y2, 100);

    glVertex3i(x2,y2, 100);
    glVertex3i(x1,y2, 100);

    glVertex3i(x1,y2, 100);
    glVertex3i(x1,y1, 100);
    glEnd();

    //left corner
     glColor3f(0.0f, 1.0f, 0.0f);
     glLineWidth(3);
     glBegin(GL_QUADS);   //We want to draw a quad, i.e. shape with four sides
          // glColor3i(1, 0, 0); //Set the colour to red
       glVertex3i(leftCornerX1, leftCornerY1, 100);            //Draw the four corners of the rectangle
       glVertex3i(leftCornerX2, leftCornerY1, 100);
       glVertex3i(leftCornerX2, leftCornerY2, 100);
       glVertex3i(leftCornerX1, leftCornerY2, 100);
     glEnd();
}
//glDisable(GL_DEPTH_TEST);
if(isMousePress) {
    //editingRectangle.setX(0);
   // editingRectangle.setY(0);

        if (editingRectangle.editingRectangleMode==EDIT_RECTANGLE_UNBINDED && editingRectangle.isEditingRectangleVisible && !forseEditBoxDisable && !isPainting)
 if ((mousePos.x() >= leftCornerX1 && mousePos.x() <= leftCornerX2) && (mousePos.y() >= leftCornerY1 && mousePos.y() <= leftCornerY2))
 {
     editingRectangle.editingRectangleMode=EDIT_RECTANGLE_RESIZE;
 }
 else if ((mousePos.x() >= x1) && (mousePos.x() <= x2) &&
          (mousePos.y() >= y1) && (mousePos.y() <= y2))
 {
     editingRectangle.editingRectangleMode=EDIT_RECTANGLE_MOVE;
 }


 switch(editingRectangle.editingRectangleMode){
case EDIT_RECTANGLE_MOVE:
     canDrawByMouse=false;
    // // //qDebug()<<"EDIT_RECTANGLE_MOVE width"<<editingRectangle.rect.width();
     //if (isPainting)
     {
     editingRectangle.rect.moveTo(mousePos.x() - mousePressPos.x(), //-editingRectangle.rect.width()/2
                            mousePos.y() - mousePressPos.y() ); //-editingRectangle.rect.height()/2
     }

     //editingRectangle.setX(mousePos.x()-editingRectangle.width()/2);
     //editingRectangle.setY(mousePos.y()-editingRectangle.height()/2);
    // // //qDebug()<< "leftCornerX1:"<<leftCornerX1;
     //// //qDebug()<< "leftCornerY1:"<<leftCornerY1;
     // // //qDebug()<< "leftCornerX2:"<<leftCornerX2;
     // // //qDebug()<< "leftCornerY2:"<<leftCornerY2;
 break;
 case EDIT_RECTANGLE_RESIZE:
     canDrawByMouse=false;
     // //qDebug()<<"EDIT_RECTANGLE_RESIZE";
    //  if (isPainting)
     {
         editingRectangle.rect.setX(mousePos.x());
         editingRectangle.rect.setY(mousePos.y());
     }

    break;
 }
 testRectangle();
    if (canDrawByMouse && m_manager.isAbleToDraw()) paintBrushInBuffer(mainFBO);
}
if (showingLastDrawing )
{
    if (drawBrushElm->getBrushes().length()<=0)
    {
        stopShowLastDrawing();
        return;
    }
 int recordedBrushN = 0;
    for (; recordedBrushN < drawBrushElm->getBrushes().length(); )
    {
        ////qDebug() << "brushes["<<recordedBrushN<<"].pointIndex"<<brushes[recordedBrushN].pointIndex;
     if (drawBrushElm->getBrushes()[recordedBrushN].pointIndex==currentLastDrawingPointIterator){
      // //qDebug() << "KEY_FRAME:"<<keyFrame;
       // //qDebug() << "mouse play index:"<<keyFrame;

       currentBrushOfLastDrawing =drawBrushElm->getBrushes()[recordedBrushN].brush;
        brushTexture = loadTexture(drawBrushElm->getBrushes()[recordedBrushN].brush.color_img);
     break;
    }
    recordedBrushN++;
    }
glBindFramebuffer(GL_FRAMEBUFFER , mainFBO.frameBuffer);
    paintBrushInBuffer(brushTextureCurrentPlayed,currentBrushOfLastDrawing,mainFBO,drawBrushElm->getCoords(),drawBrushElm->getBrushes(),currentLastDrawingPointIterator);
    glBindFramebuffer(GL_FRAMEBUFFER ,0);
    currentLastDrawingPointIterator++;
    if (currentLastDrawingPointIterator>=drawBrushElm->getCoords().length())
    {
       stopShowLastDrawing();     
    }
   // currentLastDrawingPointIterator++;

}

if(curStatus == STOP)
    paintBufferOnScreen(mainFBO,0, 0, wax, way,-100);

glDisable(GL_BLEND);
GLuint error = glGetError();

glFinish();
//////////////////////////////
swapBuffers();
glFlush();

if(bRecord)
    m_encoder->setFrame(grabFrameBuffer());


init = true;


}

void OGLWidget::paintEvent(QPaintEvent *event)
{

}

void OGLWidget::resizeEvent(QResizeEvent *envent)
{
    resizeGL(envent->size().width(), envent->size().height());
    //maxWidth = width() - marginLeft;
}

void OGLWidget::closeEvent(QCloseEvent *event)
{
    stopAnimated();

    pause(500);
    isClose = true;
    m_manager.close();
}

void OGLWidget::hideBrushManager()
{
m_manager.hide();
setIsBrushWindowOpened(false);
}



void OGLWidget::mousePressEvent(QMouseEvent *event)
{
getTimeLine()->emitFocusLostSignal();
    if(event->button() == Qt::RightButton)
    {
        if (getIsBrushWindowOpened()){
            m_manager.hide();
            setIsBrushWindowOpened(false);
        }
        else
        {
        m_manager.setPosition(QCursor::pos());

        m_manager.show();
        setIsBrushWindowOpened(true);
        }
    }
    if(event->button() == Qt::LeftButton)
    {
        //isMousePlay = false;
        isPainting = true;
       stopShowLastDrawing();
        if (getIsBrushWindowOpened())
        {
        m_manager.hide();
        setIsBrushWindowOpened(false);
        }
        else{
            mousePos.setX(event->x());
           mousePos.setY(event->y());
           prevMousePos.setX(mousePos.x());
           prevMousePos.setY(mousePos.y());
        isMousePress=true;

       ismouseWasPressedBeforeDrag=false;

       mousePressPos = QPoint(mousePos.x() - editingRectangle.rect.x(),
                              mousePos.y() - editingRectangle.rect.y());

       QRect temp = editingRectangle.rect;
       if (temp.x() <= mousePos.x() && temp.x() + temp.width() >= mousePos.x()
             && temp.y() <= mousePos.y() && temp.y() + temp.height() >= mousePos.y()  )
           isPainting = false;

       //for rectangle resize
       GLint x1 = editingRectangle.rect.x();
         GLint y1 = editingRectangle.rect.y();

       int leftCornerX1=x1-editingRectangle.leftCornerSize/2;
               int leftCornerY1=y1-editingRectangle.leftCornerSize/2;
                       int leftCornerX2=x1 + editingRectangle.leftCornerSize/2;
                        int leftCornerY2=y1 + editingRectangle.leftCornerSize/2;

     if ((mousePos.x() >= leftCornerX1 && mousePos.x() <= leftCornerX2)
      && (mousePos.y() >= leftCornerY1 && mousePos.y() <= leftCornerY2))
           isPainting = false;
        }
    }

    //int x = event->x();
    //int y = event->y();
    //drawImage();



}

void OGLWidget::testRectangle()
{

    if(editingRectangle.rect.x() > this->width() - editingRectangle.rect.width())
        editingRectangle.rect.moveTo(this->width() - editingRectangle.rect.width(), editingRectangle.rect.y());
    if(editingRectangle.rect.y() > this->height() - editingRectangle.rect.height())
        editingRectangle.rect.moveTo(editingRectangle.rect.x(), this->height()  - editingRectangle.rect.height());

    if(editingRectangle.rect.x() < 0)
        editingRectangle.rect.moveTo(0, editingRectangle.rect.y());
    if(editingRectangle.rect.y() < 0)
        editingRectangle.rect.moveTo(editingRectangle.rect.x(), 0);

    if(editingRectangle.rect.width() > this->width())
        editingRectangle.rect.setWidth(this->width());
    if(editingRectangle.rect.height() > this->height())
        editingRectangle.rect.setHeight(this->height());

}

bool OGLWidget::isInit()
{
    return init;
}

void OGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //int x = event->x();
    //int y = event->y();
    //drawImage();
    isMousePress=false;
    if (editingRectangle.editingRectangleMode==EDIT_RECTANGLE_RESIZE)
        editingRectangle.rect=editingRectangle.rect.normalized();
    editingRectangle.editingRectangleMode=EDIT_RECTANGLE_UNBINDED;

    /*
     * MIN_SIZE
     */

    if(editingRectangle.rect.width() < MIN_RECT_SIZE)
           editingRectangle.rect.setWidth(MIN_RECT_SIZE);
    if(editingRectangle.rect.height() < MIN_RECT_SIZE)
           editingRectangle.rect.setHeight(MIN_RECT_SIZE);

    testRectangle();

   /* if(editingRectangle.rect.width() > this->width())
        editingRectangle.rect.setWidth(this->width());
    if(editingRectangle.rect.height() > this->height())
        editingRectangle.rect.setHeight(this->height());
    */

    isPainting = false;
}

void OGLWidget::mouseMoveEvent ( QMouseEvent * event ){

    //mouseDrag
if (event->buttons() & Qt::LeftButton) {
    mousePos.setX(event->x());
   mousePos.setY(event->y());

   ismouseWasPressedBeforeDrag=true;
   //// //qDebug()<<"mouseRecorderTimer.elapsed():"<<mouseRecorderTimer.elapsed();

}
}

void OGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key () == Qt::Key_Control  )
     pressedCtrl = false;
    else
        if (event->key () == Qt::Key_Shift )
            pressedShift = false;
}

bool OGLWidget::event(QEvent *e)
{
    switch(e->type())
    {
        // ...

        case QEvent::WindowActivate :
         timeLine->setFocus();
            break ;

        case QEvent::WindowDeactivate :
            break ;
        // ...

    } ;

    return QGLWidget::event(e) ;
}

void OGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key () == Qt::Key_Control  )
     pressedCtrl = true;
    else
        if (event->key () == Qt::Key_Shift )
         pressedShift = true;
    else
    {
     if (pressedCtrl)
     {
     if ( pressedShift ) //keySequence[0] == Qt::Key_Control && keySequence[1] == Qt::Key_Shift  )
     {
         switch(event->key ())
         {
         case Qt::Key_S : case 1067 :
             timeLine->emitSaveProject();
             break;
         case Qt::Key_O : case 1065 :
             timeLine->emitOpenProject();
             break;
         case Qt::Key_N : case 1058 :
             timeLine->emitNewProject();
             break;
         }
     }
     else
         switch(event->key ())
         {
         case 43 :
             timeLine->zoomPlus();
             break;
         case 45 :
              emit timeLine->zoomMinus();
             break;
         }
     }
    }
}

QSize OGLWidget::getTextureSize()
{
    glEnable(GL_TEXTURE_2D);
    QSize textureSize;
    GLint width;
    GLint height;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
   textureSize.setWidth(width);
    textureSize.setHeight(height);
    return textureSize;
}

QString OGLWidget::getDrawText()
{
    return drawText;
}

void OGLWidget::setDrawText(QString data)
{
    drawText = data;
}



bool OGLWidget::drawAnimated(bool record)
{

    if(curStatus == this->PAUSE)
    {
        //m_recorder->resume();
        curStatus = PLAY;
        if(bRecord)
            timeLine->hide();
        pause(300);
        m_encoder->pause();

        return true;
    }

    curStatus = PLAY;
    if(record)
    {
        editingRectangle.isEditingRectangleVisible = false;
        //QString fileName = QFileDialog::getSaveFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Videos (*.avi *.mp4)"), 0, QFileDialog::DontUseNativeDialog);

        QString suf;
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                        tr("Videos (*.avi *.mp4)"), &suf, QFileDialog::DontUseNativeDialog | QFileDialog::DontConfirmOverwrite);
        fileName =  mSuffixFromFilter(suf, fileName);

        if(fileName.size() == 0)
            return false;
        //qDebug() << "OKKKKKKKKKKKKKKKKKKKKKKK";
      //  //qDebug() << "SHOW_FILE_NAME " << fileName;
        m_encoder->setFileName(fileName);
        m_encoder->setGrabWidget(this);

         m_encoder->startRecord();
        // QTimer::singleShot(1,m_encoder, SLOT(startRecord() ) );
        // //qDebug() << "Start record into file";
         timeLine->hide();
    }

    bRecord = record;
    //tickTimer.start();
    // //qDebug() << "Start play";
    emit startSignal();
    return true;
}

void OGLWidget::stopAnimated()
{
    //pause(100);
    if(init)
    {
        if(bRecord)
        {
            if(m_encoder->getBPause())
               m_encoder->pause();
            m_encoder->stop();
            timeLine->show();
        }

        curStatus = STOP;
        //tickTimer.stop();

        //m_encoder->stop();
        clearFrameBuffer(mainFBO);


       // double t_animationPersentOfCross = animationPersentOfCross;

    }

/*    int t_delay = delay;

    animationPersentOfCross = 1;
    delay = 1;
    while(busy)
    {
         qApp->processEvents();
    }
    animationPersentOfCross = t_animationPersentOfCross;
    delay = t_delay;
*/
    bRecord = false;

 //   pause(200);
     //qDebug() << "Stop play" << timeLine->getPlayTime();
    emit stopSignal();

}

void OGLWidget::pauseAnimated()
{
    m_encoder->pause();

    curStatus = PAUSE;



    // //qDebug() << "Pause play";
    emit pauseSignal();
    if(bRecord)
        timeLine->show();
    //m_recorder->pause();
}

void OGLWidget::brushParamsChanged()
{
    if (!m_manager.isAbleToDraw())return;
    m_manager.getCreatedBrush().color_img=BrushPainter::getInstance()->applyColor(m_manager.getCreatedBrush());
    brushTexture = loadTexture(m_manager.getCreatedBrush().color_img);
    while (!isInit())
        qDebug() << "waiting for init";
    drawBrushElm->addBrush(m_manager.getCreatedBrush());
    //qDebug() << "brushParamsChanged";

}
bool OGLWidget::isRecord() const
{
    return bRecord;
}





void OGLWidget::drawFigure(int x, int y, int x2, int y2, /*OGLWidget::*/FigureType type, bool fill , QColor col , float size )
{
    //// //qDebug()<<"void OGLWidget::drawFigure";
    glDisable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
    qglColor(QColor(Qt::red));
    glBegin(GL_LINES);
     glLineWidth(3.0f);
       glVertex2i( x,y);
       glVertex2i( x2,y);
       // //qDebug()<<"x:"<<x;
        // //qDebug()<<"y:"<<y;
         // //qDebug()<<"x2:"<<x2;
     //glVertex3f( 0,0,0);
    // glVertex3f( 100,100,0);
       glEnd();
    glDisable(GL_LINE_SMOOTH);
      glEnable(GL_BLEND);

    /*QString sColor = QString("rgba(%1, %2, %3, %4)").arg(col.red()).arg(col.green()).arg(col.blue()).arg(col.alpha());
    QMetaObject::invokeMethod(canvas, "drawFigure",
            Q_ARG(QVariant, QVariant(x)),
            Q_ARG(QVariant, QVariant(y)),
            Q_ARG(QVariant, QVariant(width)),
            Q_ARG(QVariant, QVariant(height)),
            Q_ARG(QVariant, QVariant(type)),
            Q_ARG(QVariant, QVariant(fill)),
                              Q_ARG(QVariant, QVariant(size)),
                              Q_ARG(QVariant, QVariant(sColor)));*/
    /*switch (type){
    case LINE:


        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);

        glBegin(GL_LINES);
           glVertex3f( x,y,0);
           glVertex3f( x+width,y+height,0);
         //glVertex3f( 0,0,0);
        // glVertex3f( 100,100,0);
           glEnd();
        glDisable(GL_LINE_SMOOTH);
        break;
    }*/

}






void OGLWidget::generateFrames()
{

}
 int OGLWidget::getCurStatus() const
{
    return (int) curStatus;
}

void OGLWidget::setCurStatus(const StatusDraw &value)
{
    curStatus = value;
}




bool OGLWidget::getIsBrushWindowOpened() const
{
    return isBrushWindowOpened;
}

void OGLWidget::setIsBrushWindowOpened(bool value)
{
    isBrushWindowOpened = value;
}

int OGLWidget::getWax()
{
    return wax;
}

int OGLWidget::getWay()
{
    return way;
}






bool OGLWidget::getBusy() const
{
    return busy;
}

 void OGLWidget::setBusy( bool value)
 {
     busy = value;
 }

void OGLWidget::pause(int ms)
{
    if( ms < 1)
        return;
    QTimer tickTimer;
    tickTimer.setSingleShot(true);
    tickTimer.start(ms);
    while (tickTimer.isActive()) {
      qApp->processEvents(QEventLoop::EventLoopExec);
      if(curStatus == STOP)
        break;
    }
}


void  OGLWidget::updateWindow(){
    //isCrossingNow=true;
    //if (timeLine->getPointedBlocks().size())
   /// if(!timeLine->isBlocked)
   ///

     current_millisecs = QDateTime::currentMSecsSinceEpoch();
   if ((current_millisecs - last_milisecs_drawn) >= 1000/frameRate)
   {
       emit windowUpdating(1000/frameRate);
   last_milisecs_drawn = QDateTime::currentMSecsSinceEpoch();

   setList(timeLine->getPointedBlocksDE());

   QPoint t = timeLine->getSelectedBlockPoint();

   if(curStatus != PLAY && t.x() >= 0)
   {
       if (mayShowRedRectangle)
           editingRectangle.isEditingRectangleVisible = true;

       if(t != selElm )
       {
           //clearBuffer();
           selElm = t;
           editingRectangle.rect = timeLine->getDrawRect(t.x(), t.y());
       }
       else
       {

          // if (!timeLine->getIsEditBlockShow())
           {
           QRect t2 = editingRectangle.rect;
           timeLine->setDrawX(selElm.x(), selElm.y(), t2.x());
           timeLine->setDrawY(selElm.x(), selElm.y(), t2.y());
           timeLine->setDrawSize(selElm.x(), selElm.y(), t2.width(), t2.height());
           }



       }
   }
   else
   {
      // //qDebug() << "SBLOCK " << t;
       selElm = t;
       editingRectangle.isEditingRectangleVisible = false;

   }

    updateGL();
   }
}



int OGLWidget::getDelay() const
{
    return delay;
}

void OGLWidget::setDelay(int value)
{
    delay = value;
    //animationPersentOfCross = (double)1/(value*0.6);
    // //qDebug() << animationPersentOfCross;
}







OGLWidget::StatusDraw OGLWidget::getStatus() const
{
    return curStatus;
}

void OGLWidget::recreate()
{
    this->create();
}
void OGLWidget::clear(int x,int y,int width,int height){

}
void OGLWidget::myRenderText( QGLWidget* w, int x, int y,int z, const QString& text, const QColor& col , const QFont& font , float scale )
{
         qDebug() << scale;
    if (text.isEmpty()) return;

   // //qDebug() <<"myRenderText begin";
    /*glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0, w->width(), w->height(), 0, 1000000, -2000000 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    //glLoadIdentity();*/
    glPushMatrix();

    QFontMetrics fm(font);



    QRect rect = fm.boundingRect( text);
    if (rect.width()>wax)rect.setWidth(wax);
    if (rect.height()>way)rect.setHeight(way);

    QPixmap pixmap( rect.size() );
    pixmap.fill( Qt::black );
    QPainter painter(&pixmap);
    painter.setPen( Qt::white );
    painter.setFont( font );
    painter.drawText( -rect.left(), -rect.top(), text );
    QImage img = pixmap.toImage().convertToFormat(QImage::Format_ARGB32);
    //img.setAlphaBuffer( true );
    for ( int i = 0; i < img.height(); i++ ) {
        QRgb* rgb = (QRgb*) img.scanLine(i);
        for ( int j = 0; j < img.width(); j++ ) {
            rgb[j] = qRgba( col.red(), col.green(), col.blue(), qRed(rgb[j]) );
        }
    }
    img = QGLWidget::convertToGLFormat(img);

   // glEnable(GL_BLEND);
 //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRasterPos3i( x, y, z );
    //glScalef(getWax()/rect.width(), getWay()/rect.height(), 0);
    //glPixelZoom(getWax()/rect.width(), getWax()/rect.width());
    glDrawPixels( rect.width(), rect.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits() );
    //glDisable(GL_BLEND);
    /*glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );*/
  //  glPopMatrix();
  //  //qDebug() <<"myRenderText end";

    /*
     *
     * IMAGE VERSION
    QFontMetrics fm(font);
    QRect rect = fm.boundingRect( text);

    QImage img(rect.size(), QImage::Format_RGBA8888);
    img.fill("transparent");
    QPainter painter(&img);
    painter.setPen( Qt::white );
    painter.setFont( font );
    painter.drawText( -rect.left(), -rect.top(), text );
    painter.end();
    img = QGLWidget::convertToGLFormat(img);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRasterPos3i( x, y, z );
    glDrawPixels( rect.width(), rect.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits() );
    glDisable(GL_BLEND);
    glPopMatrix();

     */

}

void OGLWidget::drawQImage(int x, int y, QImage img, int z)
{
    glPushMatrix();
    QImage res = img.convertToFormat(QImage::Format_ARGB32);
    res = QGLWidget::convertToGLFormat(res);

   // glEnable(GL_BLEND);
 //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRasterPos3i( x, y + res.height(), z );
    glDrawPixels( res.width(), res.height(), GL_RGBA, GL_UNSIGNED_BYTE, res.bits() );
    //glDisable(GL_BLEND);
    /*glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );*/
    glPopMatrix();
}

void OGLWidget::fillText( QString str,QColor color,QFont textFont, int x, int y, int z, float scale)
{
 qDebug() << "IN FILL TEXT:"<< x << "   " << y;
   /* // //qDebug() << "ARG1:  " << str.size();
    // //qDebug() << "ARG2:  " << arg2;
    // //qDebug() << "ARG3:  " << arg3;
    if(arg1.isValid() && arg2.isValid() && arg3.isValid())
       if(canvas != NULL)
   */

    qglColor(color);
   // glDisable(GL_DEPTH_TEST);
  //  //qDebug() << "SHOW_Z " << z;

//fillText("eeeeeeeeeeeeeeeeeeee",QColor("red"), QFont("Helvetica",40), 10 , 10, 0,(float) 100);
    //renderText(x, y, str,textFont);
    myRenderText(this,x,y,z,str,color,textFont, scale);
//=======
    qglColor(Qt::white);
//>>>>>>> romaFix_lastGood
    //displayText(str, color);

    //glEnable(GL_DEPTH_TEST);
     //renderText(x, y , QString::fromUtf8("Вы набрали %1 очков:").arg(17),textFont);
    /*if(textFont.strikeOut())
    {
        float x2 = x + fMetrics->width(str);
        float y2 = y - fMetrics->height()/4;
        drawFigure(x, y2 ,x2 , y2,LINE, false, fillColor);
    }

    if(textFont.underline())
    {
        float x2 = x + fMetrics->width(str) ;
        float y2 = y + fMetrics->height()*0.15;
        drawFigure(x ,y2 ,x2 , y2,LINE, false, fillColor);
    }*/
}

bool OGLWidget::crossTextV2()
{
    /*
    if(deleteWT != 0 && !symbolPositionList.isEmpty())
    {
        // //qDebug() << deleteWT << "WT == symbolPositionList" << symbolPositionList.size();
        if(deleteWT > symbolPositionList.length())
            deleteWT = symbolPositionList.length();

        QPoint delPos = symbolPositionList.at(symbolPositionList.length() - deleteWT); // -2 is popravka
        if(deleteWT != 1)
        {
            int i = 0;
            while(listWords.at(listWords.size() - i - 1) <= 0x20 && i != listWords.size() - 1)
            {
                i++;
            }
            int pos2 = symbolPositionList.length() - i - 1;

            int n = pos2;
            int m = pos2;
            int lastH = symbolPositionList[n].y();
            deleteWT--;
            while(deleteWT != 0 && n > 0)
            {

                while ( --n > 0 && lastH == symbolPositionList[n].y() && listWords[n] > 0x20 && deleteWT != 0)
                {
                    deleteWT--;
                }
                // //qDebug() << "startNEW with:  "<< hex << listWords[n + 1];
                delPos = symbolPositionList.at(m); // -2 is popravka
                int x2 = delPos.x() + fMetrics->width(listWords[m]);;
                int y2 = delPos.y() - fMetrics->height()/4;
                if( n == 0 )
                    delPos = symbolPositionList.at(n); // -2 is popravka
                else
                    delPos = symbolPositionList.at(n + 1); // -2 is popravka
                int x1 = delPos.x();
                int y1 = delPos.y() - fMetrics->height()/4;
                if(crossWithAnimation)
                {
                    // //qDebug() << "set animation speed";
                    drawAnimationFigure(x1, y1, x2, y2, LINE, 0);
                }
                else
                    drawFigure(x1, y1, x2, y2, LINE, 0);
                lastH = symbolPositionList[n].y();
                while ( n > 0 && listWords[n] <= 0x20)
                    n--;
                m = n;
                if(n != 0)
                    n++;
            }
        }
        else{
            int i = 1;
            while(symbolPositionList.length() != i && listWords.at(listWords.size() - i) == ' ')
                i++;
            delPos = symbolPositionList.at(symbolPositionList.length() - i);
            QColor temp = fillColor;
            setFillColor(QColor("#ff0000"));
            fillText("/", delPos.x(), delPos.y());
            fillText("\\", delPos.x(), delPos.y());
            setFillColor(temp);
        }
        deleteWT = 0;
    }
    else
        deleteWT = 0;
    deleteWT = 0;
    crossWithAnimation = false;*/
}

QPoint OGLWidget::drawWrapText(QString str)
{
   /* busy = true;
    //if(!crossTextV2())
     //   return QPoint(0, 0);
    crossTextV2();
    int width = fMetrics->width(str)*1.125 ;//+ fMetrics->leftBearing(str.at(0)) + fMetrics->rightBearing(str.at(0));

    if(str[0] <= 0x20){
         listChars.clear();
         widthToClean=0;
     }
        if(width + x > maxWidth)
        {
         // //qDebug()<<listChars;

                //fillText("-", x, y);
                //listChars += str;
                //listWords.remove(indexInList,1);
          int clearWidth = fMetrics->width(listChars); //

             // if(y  + scroll*indexRow > this->height() )
             clear(x-widthToClean,y-fMetrics->height(), this->width(),fMetrics->height()*1.25);

             // listStr.push_back( listChars.length() );//не юзається.
              // indexInList++;//не юзається.
          //indexInList+=listChars.length();
             nextRow();
             isLastRow();
            fillText(listChars,fillColor,x,y);
           // listWords += listChars.trimmed();
           // listWords +=listChars;
            //listStr.push_back( listWords.length() );

            listChars.clear();
            widthToClean=0;
            x+=clearWidth;
        }
    isLastRow();
    //fillAnimationText(str, x, y, 6);
    fillText(str,fillColor,x, y);
    QPoint res(x,y);
    listWords += str;
    listChars += str.trimmed();
    x += width;
    widthToClean+=width;
    symbolPositionList.push_back(res);
    //tickTimer.start(delay);
    /*while (tickTimer.isActive()) {
       qApp->processEvents();
    }*/
   // busy = false;
 //   // //qDebug() << "Y: " << y;
   // // //qDebug() << "Y: " << y;
    //return res;*/
}








void OGLWidget::storeMousePos()
{
    if (isMousePress){

        if (drawBrushElm->getCoords().length()==0)drawBrushElm->addBrush(m_manager.getCreatedBrush());
            drawBrushElm->addCoord(QPoint(mousePos.x(),mousePos.y()));
   // //qDebug()<<"position stored:"<<QCursor::pos();
    }
}




ListControll* OGLWidget::getTimeLine()
{
    return timeLine;
}



void OGLWidget::testWrap(int kIndexOfRow)
{
   /* int i = kIndexOfRow;
    int length = stringList.length();
    while(stringList.length() > i)
    {
        QString &str =  stringList[i];
        int width = fMetrics->width(stringList[i]) ;//+ fMetrics->leftBearing(str.at(0)) + fMetrics->rightBearing(str.at(0));
        ////// //qDebug() <<"str:"<< maxWidth;
        if(width > maxWidth)
        {

            int j = stringList[i].size() - 1;
            while( j >= 0 && str[j] > ' ')
            {
             //   // //qDebug() << str[j];
                j--;
            }


            if(j < 0)
                j = stringList[i].length() - 1;

         //   // //qDebug() <<"strSize:    " << stringList.size() << "    SIZE_i    " << stringList[i] << "     " << j;
            nextRow(j, i, false);
            wrapShift.append(getFirstSymbolOfString(i + 1));
                // //qDebug() << "WRAPSHIFT"<< wrapShift;

        }
        i++;
    }*/
}


void OGLWidget::displayText(QString const &text, QColor color,QFont font)
{

        QImage textimg(1000, 1000, QImage::Format_RGBA8888);
        QPainter painter(&textimg);
        painter.fillRect(0, 0, 1000, 1000, QColor(0,0,0,0));
        painter.setBrush(color);
        painter.setPen(color);
        painter.setFont(font);
        painter.drawText(0, 0, text);

    glBindTexture(GL_TEXTURE_2D, 0);
}
