
#include "openglwidget.h"
#include <qglfunctions.h>
#include "drawSystem/drawsystem.h"
#include "../TimeLine/listcontroll.h"

/*
 *scroll
 *
int k = canvas->property("scroll").toInt() - 10;
canvas->setProperty("scroll", k);
*/

GLuint OGLWidget::loadTexture(QImage img){
    makeCurrent();
    if(img.isNull()) // QCoreApplication::applicationDirPath()+"/star.png"
    {
        //loads correctly
        qWarning() << "ERROR LOADING IMAGE";// + QCoreApplication::applicationDirPath()+"/star.png";
        return -1;
    }
    //qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();
    QImage GL_formatted_image = convertToGLFormat(img);
    //qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();
    // qDebug() << "image converted to GL format";
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
      // qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();
    //   qDebug() << texture;
       glBindTexture(GL_TEXTURE_2D, texture); // Set as the current texture
 //qDebug(" after  glBindTexture(GL_TEXTURE_2D, texture);");
       //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


       glTexImage2D(GL_TEXTURE_2D, 0, 4, GL_formatted_image.width(), GL_formatted_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits());
  //     qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();
      //// qDebug() <<
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      // qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();
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
       //qDebug() << "GL_ERROR_STATUS LOAD_TEXTURE:   "<< glGetError();
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

void OGLWidget::drawTexture( int x, int y, int width, int height, GLuint texture,int angle,float scaleX,float scaleY, int z){
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
    //// qDebug() << "void OGLWidget::drawTexture(int x, int y, int width, int height, int index)";
}


QList<DrawElement *> &OGLWidget::getList()
{
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
            elm->setDrawWidget(this);   //12345
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
void OGLWidget::paintBrushInBuffer(QVector<QPoint> coords,QVector<BrushBeginingIndex> brushes,int keyFrame){
    glBindFramebuffer(GL_FRAMEBUFFER , fbo); // Bind our frame buffer for rendering
int recordedBrushN = 0;

//qDebug() << "keyFrame:"<<keyFrame;

//bool isBrushUsed = false;
    for (; recordedBrushN < brushes.length(); )
    {
        //qDebug() << "brushes["<<recordedBrushN<<"].pointIndex"<<brushes[recordedBrushN].pointIndex;
    if (brushes[recordedBrushN].pointIndex==keyFrame){
       qDebug() << "KEY_FRAME:"<<keyFrame;
       // qDebug() << "mouse play index:"<<keyFrame;

        currentBrushOfDrawSystem = brushes[recordedBrushN].brush;
        brushTexture = loadTexture(currentBrushOfDrawSystem.color_img);
        qDebug() << "recordedBrushN:"<<recordedBrushN;
       // isBrushUsed=true;
     //qDebug() << "recordedBrushN:"<<recordedBrushN;
     break;
    }
    recordedBrushN++;
    }

    //glUseProgram(ShaderProgram);
    glBindTexture(GL_TEXTURE_2D,brushTexture);
   // if (isBrushUsed) {
     //   qDebug() << "recordedBrushN:" << recordedBrushN;
      //  currentBrushOfDrawSystem = brushes[recordedBrushN].brush;
    //}

     //qDebug() << "recordedBrushN:"<<recordedBrushN;
    //if (recordedBrushN>=brushes.length())recordedBrushN=brushes.length()-1;
   // qDebug() << "recordedBrushN:"<<recordedBrushN;


    QSize brushTextureSize = getTextureSize();
    int BRUSH_SIZE=currentBrushOfDrawSystem.size + currentBrushOfDrawSystem.size_delta/2 - rand()%(int)(currentBrushOfDrawSystem.size_delta + 1);
    //qDebug() << "LOADED BRUSH SIZE DRAW:"<<BRUSH_SIZE;
    float scaleX=1,scaleY=1;
    float randScalePtX = 0;
    float randScalePtY = 0;
    if(currentBrushOfDrawSystem.afinn != 0)
    {
        randScalePtX = currentBrushOfDrawSystem.afinn/2 - rand() % ((int)currentBrushOfDrawSystem.afinn);
        randScalePtY = currentBrushOfDrawSystem.afinn/2 - rand() % ((int)currentBrushOfDrawSystem.afinn);
    }

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
         // qDebug() << r << g << b << a;
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
                // qDebug()<<"mouseRecorder.getBrushBeginings().length():"<<brushes.length();
                 // qDebug() << "xPos:"<<xPos;
                 // qDebug() << "yPos:"<<yPos;
                 xPos=coords[keyFrame].x();
                 yPos=coords[keyFrame].y();
                 // qDebug() << "AFTER123";
               // qDebug() << "x:"<<xPos;
               // qDebug() << "y:"<<yPos;
                //qDebug() << "keyFrame:"<<keyFrame;
                     if (mousePlayIndex >= coords.length()-1)
                     {
                     isMousePlay=false;
                     mousePlayIndex=0;
                     }
                     else
                      mousePlayIndex++;


        drawTexture(xPos-BRUSH_SIZE/2 + dispersX ,yPos-BRUSH_SIZE/koff/2 + dispersY,BRUSH_SIZE,BRUSH_SIZE/koff,
                brushTexture,angle,scaleX,scaleY);
        }
// glUseProgram(NULL);


glBindTexture(GL_TEXTURE_2D,0);
glBindFramebuffer(GL_FRAMEBUFFER , 0); // Unbind our texture
}
bool OGLWidget::isShowLastDrawing(){
    return showingLastDrawing;
}
void OGLWidget::setShowLastDrawing(bool val){
     showingLastDrawing=val;
}

void OGLWidget::slotBlockEdited()
{
    qDebug() << "1234566666666666666";
 // ms_for_debug.show();
 /*QPoint t = timeLine->getSelectedBlockPoint();
editingRectangle.rect = timeLine->getDrawRect(t.x(), t.y());
*/
selElm = QPoint(-1,-1);
}

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    init = false;
    timeLine = new ListControll;
    connect(timeLine,SIGNAL(stopSignal()),this,SIGNAL(stopSignal()));
    connect(timeLine,SIGNAL(playSignal()),this,SIGNAL(startSignal()));
    connect(timeLine,SIGNAL(pauseSignal()),this,SIGNAL(pauseSignal()));

    connect(timeLine,SIGNAL(blockEditedSignal()),this,SLOT(slotBlockEdited()));

    isNotPainting = false;
    selElm = QPoint(-1,-1); //because it undefined

    //qRegisterMetaType<DrawData>("DrawData");
    // engine()->rootContext()->setContextProperty(QLatin1String("forma"), this);
    m_encoder = new AV_REncoder(this);
    fMetrics = NULL;
    editingRectangle.rect.setWidth(100);
    editingRectangle.rect.setHeight(100);
    editingRectangle.rect.setX(50);
    editingRectangle.rect.setY(50);
    editingRectangle.leftCornerSize=10;
    bRecord = false;
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    //this->setResizeMode(QQuickWidget::SizeRootObjectToView ); //TODO
    /*
     * init
    */

    //
    ColorMarker startMarker;
    startMarker.startIndex=0;
    startMarker.value=getMainFillColor();

    lineHeight = 25;
    marginLeft = 20;
    marginTop = 40;
    maxWidth; //размер поле, где выводится текст
    pt = 36;
    font = "LC Chalk";
    isWord  =  true;
    wax=500; way=500; // начальный размер окна
    x = marginLeft;
    y = lineHeight + pt;
    indexW = 1;
    indexRow = 0;
    scroll = 0;
    delay = 1000/3;
    //listStr[0] = 0;
    indexInList = 1;
    deleteWT = 0;
    fMetrics = new QFontMetrics(QFont(font));
    curStatus = STOP;
    tickTimer.setSingleShot(false);
    tickTimer.setInterval(1000/25);
    mouseTimer.setInterval(drawBrushElm->SPEED_OF_RECORDING_MS);
    mouseTimer.setSingleShot(false);
    realDelay = 0;

    maxWidth = width() - marginLeft;
    stringList.append("");
    //stringList.reserve(600000);
    indexRowInList = 0;
    cursorIndex = 0;
    isCrossingNow = false;
     drawBrushElm = new DrawBrushElm(this,this);//record mouse movement
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
   timer->start(5);
   connect(&mouseTimer, SIGNAL(timeout()), this, SLOT(storeMousePos()));
   mouseTimer.start();
   connect(&m_manager,SIGNAL(currentBrushChanged()),this,SLOT(brushParamsChanged()));


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
    // qDebug() << "CALL RESIZE";
}
void OGLWidget::paintBufferOnScreen( int x, int y, int width, int height, int z){
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,fbo_texture);
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

void OGLWidget::paintBrushInBuffer() {
glBindFramebuffer(GL_FRAMEBUFFER , fbo); // Bind our frame buffer for rendering
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
        //// qDebug() << "before index";
//// qDebug() << "paint brush in buffer";
    GLuint texture = brushTexture;
    //// qDebug()<<"texture:"<<texture;
  // if (!ismouseWasPressedBeforeDrag)

       /* glBegin (GL_POINTS);
        glColor3f (1.0, 0.4, 0.4);
        glVertex3f (mousePos.x(), mousePos.y(),0.0);
        // qDebug() << mousePos.x();
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
            randScalePtX = m_manager.getAffine()/2 - rand() % (m_manager.getAffine());
            randScalePtY = m_manager.getAffine()/2 - rand() % (m_manager.getAffine());
        }

        float MAX_SCALE = 2;
        //100 - 2 (MAX_SCALE)
        //1 - x
        //x = 2/100=0.02
        if(randScalePtX!=0)
            scaleX=MAX_SCALE/randScalePtX;
        if(randScalePtY!=0)
            scaleY=MAX_SCALE/randScalePtY;
       // // qDebug() <<"scaleX:"<<scaleX;
       // // qDebug() <<"scaleY:"<<scaleY;
        //// qDebug() << "brushSize.width():"<<brushTextureSize.width();
        //// qDebug() << "brushSize.height():"<<brushTextureSize.height();

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
             // qDebug() << r << g << b << a;
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

//qDebug() <<"mousePos.x() = " << mousePos.x() << " mousePos.y() = " << mousePos.y();

            drawTexture(xPos-BRUSH_SIZE/2 + dispersX ,yPos-BRUSH_SIZE/koff/2 + dispersY,BRUSH_SIZE,BRUSH_SIZE/koff,
                    texture,angle,scaleX,scaleY);
            }
              //glUseProgram(NULL);
        /*
    else{
      glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D,texture);
      QSize brushTextureSize = getTextureSize();
      int BRUSH_SIZE=30;
      // qDebug() << "brushSize.width():"<<brushTextureSize.width();
      // qDebug() << "brushSize.height():"<<brushTextureSize.height();
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
        // qDebug() << "fragmentShaderCode:"<<fragmentShaderCode;
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
           qDebug() << "error on vertexShader.glsl open path: "<<shaderDir+"/shaders/vertexShader.glsl";

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
            qDebug() <<"Error compiling shader type:" << "GL_VERTEX_SHADER" << infoLog;
      }
      glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &success);
      if (!success) {
          GLchar infoLog[1024];
          glGetShaderInfoLog(fragmentShaderObj, sizeof(infoLog), NULL,infoLog);
          qDebug() <<"Error compiling shader type:" << "GL_FRAGMENT_SHADER" << infoLog;
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
    qDebug() << "Error linking shader program:" << errorLog;
}
else
    qDebug() << "Linking shader program success";
glValidateProgram(ShaderProgram);

    //glLinkProgram(program);
    //glUseProgram(program);
}





void OGLWidget::initFrameBufferDepthBuffer() {
glGenRenderbuffers(1, &fbo_depth); // Generate one render buffer and store the ID in fbo_depth
glBindRenderbuffer(GL_RENDERBUFFER , fbo_depth); // Bind the fbo_depth render buffer
GLenum error = glGetError();
qDebug() << "GL_ERROR_STATUS glBindRenderbuffer:"<<error;
glRenderbufferStorage(GL_RENDERBUFFER , GL_DEPTH_COMPONENT, wax, way); // Set the render buffer storage to be a depth component, with a width and height of the window
 error = glGetError();
qDebug() << "GL_ERROR_STATUS glRenderbufferStorage:"<<error;
//glFramebufferRenderbuffer(GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_RENDERBUFFER ,fbo_depth); // Set the render buffer of this buffer to the depth buffer
 //error = glGetError();
//qDebug() << "GL_ERROR_STATUS glFramebufferRenderbuffer:"<<error;
glBindRenderbuffer(GL_RENDERBUFFER , 0); // Unbind the render buffer
 error = glGetError();
qDebug() << "GL_ERROR_STATUS glBindRenderbuffer:"<<error;
}

void OGLWidget::initFrameBufferTexture() {
    glEnable(GL_TEXTURE_2D);
    //glDeleteTextures(1,&fbo_texture);
glGenTextures(1, &fbo_texture); // Generate one texture
glBindTexture(GL_TEXTURE_2D, fbo_texture); // Bind the texture fbo_texture

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wax, way, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); // Create a standard texture with the width and height of our window

// Setup the basic texture parameters
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// Unbind the texture
glBindTexture(GL_TEXTURE_2D, 0);
glDisable(GL_TEXTURE_2D);
}


void OGLWidget::initFrameBuffer() {
    GLenum error = glGetError();
    qDebug() << "GL_ERROR_STATUS initFrameBuffer:"<<error;
    glEnable(GL_DEPTH_TEST);
    glGenFramebuffers(1, &fbo); // Generate one frame buffer and store the ID in fbo

initFrameBufferDepthBuffer(); // Initialize our frame buffer depth buffer
 error = glGetError();
qDebug() << "GL_ERROR_STATUS initFrameBufferDepthBuffer:"<<error;
glBindFramebuffer(GL_FRAMEBUFFER , fbo); // Bind our frame buffer
initFrameBufferTexture(); // Initialize our frame buffer texture

error = glGetError();
qDebug() << "GL_ERROR_STATUS initFrameBufferTexture:"<<error;


glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, fbo_texture, 0); // Attach the texture fbo_texture to the color buffer in our frame buffer

//glFramebufferRenderbuffer(GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_RENDERBUFFER , fbo_depth); // Attach the depth buffer fbo_depth to our frame buffer
error = glGetError();
qDebug() << "GL_ERROR_STATUS:"<<error;
GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER ); // Check that status of our generated frame buffer

if (status != GL_FRAMEBUFFER_COMPLETE ) // If the frame buffer does not report back as complete
{
 qDebug() << "Couldn't create frame buffer\n" ; // Output an error to the console
exit(0); // Exit the application
}

glBindFramebuffer(GL_FRAMEBUFFER , 0); // Unbind our frame buffer
}

void OGLWidget::initializeGL()
{
    initializeGLFunctions();
    qglClearColor(Qt::black); // Черный цвет фона
     //glEnable(GL_TEXTURE_2D);
    backGroundTexture = loadTextureFromFile(":/ThirdPart/images/start.png");
    m_manager.getCreatedBrush().color_img=BrushPainter::getInstance()->applyColor(m_manager.getCreatedBrush());
    brushTexture = loadTexture(m_manager.getCreatedBrush().color_img);
    //loadTextureFromFile(":/ThirdPart/images/brush.png");
    initFrameBuffer(); // Create our frame buffer object
     initShader();
    setAutoBufferSwap(false);
    qApp->processEvents(QEventLoop::AllEvents, 1000);
   /* list_1.append(GenerationDrawElement("kaka.text", this, 0));
    list_1.append(GenerationDrawElement("brush.png", this, 0));*/

}

void OGLWidget::moveEvent(QMoveEvent *event)
{
    if(isVisible())
    {
        QPoint curentPos = this->pos();
        curentPos.setY(curentPos.y() + this->height());
        timeLine->setViewPosition(curentPos);
    }
}



void OGLWidget::destroy(bool destroyWindow, bool destroySubWindow){
    glDeleteFramebuffers(1,&fbo);
    //glDeleteRenderbuffers(1,&render_buf);
}

void OGLWidget::clearFrameBuffer(){

    glBindFramebuffer(GL_FRAMEBUFFER , fbo); // Bind our frame buffer for rendering
   std::vector<GLubyte> emptyData(wax * way * 4, 0);
   glBindTexture(GL_TEXTURE_2D, fbo_texture);
     glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, wax, way, GL_RGBA, GL_UNSIGNED_BYTE, &emptyData[0]);
      glBindTexture(GL_TEXTURE_2D,0);

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        isClearFrameBuffer=false;
      glBindFramebuffer(GL_FRAMEBUFFER , 0);
      // qDebug()<<"clearFrameBuffer";

}

void OGLWidget::paintGL()
{
     glBindFramebuffer(GL_FRAMEBUFFER , 0);
    if(m_encoder->newImage)
        m_encoder->setFrame(grabFrameBuffer());
    //// qDebug() << "isClearFrameBuffer:"<<isClearFrameBuffer;
    if(isClearFrameBuffer)clearFrameBuffer();

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
       glOrtho(0,wax,way,0, 1000000, -200000); // подготавливаем плоскости для матрицы
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
    drawTexture(0, 0, wax, way, backGroundTexture, 0, 1, 1, 100000);
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


for(int i = 0; i < getList().size(); i++)
{
   // // qDebug() << "draw   " << i;
    if( timeLine->isBlocked == false && getList()[i] != NULL && timeLine->getMaxTrackTime() > 0)
        getList()[i]->paint();
    else
        break;
}

if (editingRectangle.isEditingRectangleVisible)
{
   // paintBufferOnScreen(0, 0, wax, way);
    //rectangle
    glLineWidth(3);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3i(x1,y1, -10);
    glVertex3i(x2,y1, -10);

    glVertex3i(x2,y1, -10);
    glVertex3i(x2,y2, -10);

    glVertex3i(x2,y2, -10);
    glVertex3i(x1,y2, -10);

    glVertex3i(x1,y2, -10);
    glVertex3i(x1,y1, -10);
    glEnd();

    //left corner
     glColor3f(0.0f, 1.0f, 0.0f);
     glLineWidth(3);
     glBegin(GL_QUADS);   //We want to draw a quad, i.e. shape with four sides
          // glColor3i(1, 0, 0); //Set the colour to red
       glVertex3i(leftCornerX1, leftCornerY1, -10);            //Draw the four corners of the rectangle
       glVertex3i(leftCornerX2, leftCornerY1, -10);
       glVertex3i(leftCornerX2, leftCornerY2, -10);
       glVertex3i(leftCornerX1, leftCornerY2, -10);
     glEnd();
}
//glDisable(GL_DEPTH_TEST);
if(isMousePress) {
    //editingRectangle.setX(0);
   // editingRectangle.setY(0);

        if (editingRectangle.editingRectangleMode==EDIT_RECTANGLE_UNBINDED && editingRectangle.isEditingRectangleVisible)
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
    // // qDebug()<<"EDIT_RECTANGLE_MOVE width"<<editingRectangle.rect.width();
     if (isNotPainting)
     {
     editingRectangle.rect.moveTo(mousePos.x() - mousePressPos.x(), //-editingRectangle.rect.width()/2
                            mousePos.y() - mousePressPos.y() ); //-editingRectangle.rect.height()/2
     }

     //editingRectangle.setX(mousePos.x()-editingRectangle.width()/2);
     //editingRectangle.setY(mousePos.y()-editingRectangle.height()/2);
    // // qDebug()<< "leftCornerX1:"<<leftCornerX1;
     //// qDebug()<< "leftCornerY1:"<<leftCornerY1;
     // // qDebug()<< "leftCornerX2:"<<leftCornerX2;
     // // qDebug()<< "leftCornerY2:"<<leftCornerY2;
 break;
 case EDIT_RECTANGLE_RESIZE:
     canDrawByMouse=false;
     // qDebug()<<"EDIT_RECTANGLE_RESIZE";
      if (isNotPainting)
     {
         editingRectangle.rect.setX(mousePos.x());
         editingRectangle.rect.setY(mousePos.y());
     }

    break;
 }
 testRectangle();
    if (canDrawByMouse && m_manager.isAbleToDraw()) paintBrushInBuffer();
}
if (showingLastDrawing && drawBrushElm->getBrushes().length()>0)
{
 int recordedBrushN = 0;
    for (; recordedBrushN < drawBrushElm->getBrushes().length(); )
    {
        //qDebug() << "brushes["<<recordedBrushN<<"].pointIndex"<<brushes[recordedBrushN].pointIndex;
     if (drawBrushElm->getBrushes()[recordedBrushN].pointIndex==currentLastDrawingPointIterator){
      // qDebug() << "KEY_FRAME:"<<keyFrame;
       // qDebug() << "mouse play index:"<<keyFrame;

       currentBrushOfLastDrawing =drawBrushElm->getBrushes()[recordedBrushN].brush;
        brushTexture = loadTexture(drawBrushElm->getBrushes()[recordedBrushN].brush.color_img);
     break;
    }
    recordedBrushN++;
    }

    paintBrushInBuffer(drawBrushElm->getCoords(),drawBrushElm->getBrushes(),currentLastDrawingPointIterator);
    if (currentLastDrawingPointIterator>=drawBrushElm->getCoords().length())
    {
        showingLastDrawing=false;
        currentLastDrawingPointIterator=0;
    }
    currentLastDrawingPointIterator++;

}

if(curStatus == STOP)
    paintBufferOnScreen(0, 0, wax, way,-100);

glDisable(GL_BLEND);
GLuint error = glGetError();

glFinish();
swapBuffers();
glFlush();

init = true;

//qDebug() << "GL_ERROR_STATUS end:"<<error;
}

void OGLWidget::paintEvent(QPaintEvent *event)
{
    if(bRecord)
    {
       // m_encoder->mutex.lock();
        m_encoder->setFrame(grabFrameBuffer());
        //m_encoder->mutex.unlock();
    }
 //   if(curStatus == PLAY && bRecord)
    {
    //    m_encoder->encodeVideoFrame(this->grabFramebuffer());
        /*if (fps_stabilitron % 25 == 0) {
            while (m_encoder->encodedFrameCount() != fps_stabilitron) { qApp->processEvents(); }
            m_encoder->encodeVideoFrame(this->grabFramebuffer());

        }
            fps_stabilitron++;*/
    }
}

void OGLWidget::resizeEvent(QResizeEvent *envent)
{
    resizeGL(envent->size().width(), envent->size().height());
    maxWidth = width() - marginLeft;
}

void OGLWidget::closeEvent(QCloseEvent *event)
{
    stopAnimated();
    if(fMetrics != NULL)
      delete fMetrics;
    pause(500);
    isClose = true;
    m_manager.close();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{

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
        isMousePlay = false;
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
           isNotPainting = true;

       //for rectangle resize
       GLint x1 = editingRectangle.rect.x();
         GLint y1 = editingRectangle.rect.y();

       int leftCornerX1=x1-editingRectangle.leftCornerSize/2;
               int leftCornerY1=y1-editingRectangle.leftCornerSize/2;
                       int leftCornerX2=x1 + editingRectangle.leftCornerSize/2;
                        int leftCornerY2=y1 + editingRectangle.leftCornerSize/2;

     if ((mousePos.x() >= leftCornerX1 && mousePos.x() <= leftCornerX2)
      && (mousePos.y() >= leftCornerY1 && mousePos.y() <= leftCornerY2))
           isNotPainting = true;
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

    isNotPainting = false;
}

void OGLWidget::mouseMoveEvent ( QMouseEvent * event ){

    //mouseDrag
if (event->buttons() & Qt::LeftButton) {
    mousePos.setX(event->x());
   mousePos.setY(event->y());

   ismouseWasPressedBeforeDrag=true;
   //// qDebug()<<"mouseRecorderTimer.elapsed():"<<mouseRecorderTimer.elapsed();

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
    QSize textureSize;
    GLint width;
    GLint height;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &height);
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
        m_encoder->pause();
        return true;
    }
    if(record)
    {
        //QString fileName = QFileDialog::getSaveFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Videos (*.avi *.mp4)"), 0, QFileDialog::DontUseNativeDialog);

        QString suf;
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                        tr("Videos (*.avi *.mp4)"), &suf, QFileDialog::DontUseNativeDialog | QFileDialog::DontConfirmOverwrite);
        fileName =  mSuffixFromFilter(suf, fileName);

        if(fileName.size() == 0)
            return false;
        qDebug() << "OKKKKKKKKKKKKKKKKKKKKKKK";
      //  qDebug() << "SHOW_FILE_NAME " << fileName;
        m_encoder->setFileName(fileName);
        m_encoder->setGrabWidget(this);
        m_encoder->startRecord();
        // qDebug() << "Start record into file";
    }
    curStatus = PLAY;
    bRecord = record;
    tickTimer.start();
    // qDebug() << "Start play";
    emit startSignal();
    return true;
}

void OGLWidget::stopAnimated()
{
    //pause(100);
    curStatus = STOP;
    tickTimer.stop();
    m_encoder->stop();
    // max speed // stop draw function
    double t_animationPersentOfCross = animationPersentOfCross;
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
     qDebug() << "Stop play";
    emit stopSignal();

}

void OGLWidget::pauseAnimated()
{
    curStatus = PAUSE;
    // qDebug() << "Pause play";
    m_encoder->pause();
    emit pauseSignal();
    //m_recorder->pause();
}

void OGLWidget::brushParamsChanged()
{
    if (!m_manager.isAbleToDraw())return;
    m_manager.getCreatedBrush().color_img=BrushPainter::getInstance()->applyColor(m_manager.getCreatedBrush());
    brushTexture = loadTexture(m_manager.getCreatedBrush().color_img);
    drawBrushElm->addBrush(m_manager.getCreatedBrush());
    qDebug() << "brushParamsChanged";

}
bool OGLWidget::isRecord() const
{
    return bRecord;
}


void OGLWidget::clearCanvas(int m_x, int m_y)
{
    //QMetaObject::invokeMethod(canvas, "clear");
    symbolPositionList.clear();
    listWords.clear();
    listStr.clear();
    indexRow = 0;
    indexW = 1;
    marginLeft = m_x;
    marginTop = m_y;
    x = m_x;
    y = m_y + lineHeight + pt;
    scroll = 0;
    //listStr[0] = 0;
    indexInList = 1;
    indexRowInList = 0;


}
void OGLWidget::clearBuffer()
{
     colors.clear();
     ColorMarker startMarker;
     startMarker.startIndex=0;
     startMarker.value=getMainFillColor();
     colors.append(startMarker);
    cross.clear();
    cross.append(0); // для визова зачеркування якщо стрічка зацінчується
    stringList.clear();
    stringList.append("");
    cursorIndex = 0;
    wrapShift;
    deleteWT = 0;
    crossWithAnimation = false;
}

void OGLWidget::drawFigure(int x, int y, int x2, int y2, OGLWidget::FigureType type, bool fill = true, QColor col = "#FF0000", float size = 2)
{
    //// qDebug()<<"void OGLWidget::drawFigure";
    glDisable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
    qglColor(QColor(Qt::red));
    glBegin(GL_LINES);
     glLineWidth(3.0f);
       glVertex2i( x,y);
       glVertex2i( x2,y);
       // qDebug()<<"x:"<<x;
        // qDebug()<<"y:"<<y;
         // qDebug()<<"x2:"<<x2;
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

bool OGLWidget::drawAnimationFigure(int x, int y, int width, int height, double persent, OGLWidget::FigureType type, bool fill)
{
    isCrossingNow=true;
    qDebug() << "wqweqweqwe "  << persent;
    if(persent < 0.98f)
    {
        drawFigure(x, y, x + (width - x)*persent + 0.01, height, type, fill);
         //qDebug() << delPos.x() << "             " << delPos.x() + (maxWidth - delPos.x())*persent;
        //persent += animationPersentOfCross;
       // QThread::currentThread()->msleep(10);
        if(curStatus == STOP )
        {
            isCrossingNow=false;
            return true;
        }
        isCrossingNow=false;
        return false;
    }
    else
    {
        drawFigure(x, y, width, height, type, fill);
        isCrossingNow=false;
        return true;
    }

}

bool OGLWidget::drawAnimationFigure(AnimationFigure &figure)
{
    return drawAnimationFigure(figure.rect.x(), figure.rect.y(), figure.rect.width(), figure.rect.height(), animationPersentOfCross, (FigureType)figure.type, figure.fill);
}

void OGLWidget::crossOutLastSymbol( int n)
{
   // QPoint delPos = symbolPositionList.at(symbolPositionList.length() - 1 - deleteWT);
    //int k = 0;
    //QString str = listWords.right(1 + deleteWT);

    /*int widht = fMetrics->width(str)*1.5;
    int deltaY = deltaY = (widht - x) /(maxWidth - marginLeft);

    if(x - widht <= marginLeft)
    {
        deltaY++;
    }

    tx = maxWidth *deltaY - (widht - x + marginLeft);

    ty -= (lineHeight + pt)*deltaY;

    fillText("/", delPos.x(), delPos.y());
    fillText("\\", delPos.x(), delPos.y());*/
    //if()
    deleteWT += n;

}

void OGLWidget::crossOutWithAnimation(int n)
{
  //  // qDebug() << "URAAAA!!!  " << deleteWT;
    crossOutLastSymbol(n);
    crossWithAnimation = true;
}

void OGLWidget::generateFrames()
{

}

double OGLWidget::getAnimationPersentOfCross() const
{
    return animationPersentOfCross;
}

void OGLWidget::setAnimationPersentOfCross(double value)
{
    animationPersentOfCross = value;
  //  qDebug() << "QWE    " << value;
}

bool OGLWidget::getIsBrushWindowOpened() const
{
    return isBrushWindowOpened;
}

void OGLWidget::setIsBrushWindowOpened(bool value)
{
    isBrushWindowOpened = value;
}


int OGLWidget::getCursorIndex() const
{
    return cursorIndex;
}

void OGLWidget::setCursorIndex(int value)
{
    cursorIndex = value;
}




bool OGLWidget::getBusy() const
{
    return busy;
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
    setList(timeLine->getPointedBlocksDE());

    QPoint t = timeLine->getSelectedBlockPoint();

    if(curStatus != PLAY && t.x() >= 0)
    {
        editingRectangle.isEditingRectangleVisible = true;
        if(t != selElm )
        {
            clearBuffer();
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
       // qDebug() << "SBLOCK " << t;
        selElm = t;
        editingRectangle.isEditingRectangleVisible = false;
    }
    updateGL();
}

QColor OGLWidget::getMainFillColor() const
{
    return mainFillColor;
}

void OGLWidget::setMainFillColor(const QColor &value)
{
    mainFillColor = value;
    setFillColor(value);
}

int OGLWidget::getDelay() const
{
    return delay;
}

void OGLWidget::setDelay(int value)
{
    delay = value;
    animationPersentOfCross = (double)1/(value*0.6);
    // qDebug() << animationPersentOfCross;
}

int OGLWidget::getCountDeleteWT() const
{
    return deleteWT;
}

QFont OGLWidget::getTextFont() const
{
    return textFont;
}

void OGLWidget::setTextFont(const QFont &value)
{
    textFont = value;
    if(fMetrics != NULL)
        delete fMetrics;
    fMetrics = new QFontMetrics(value);
    pt = value.pointSize();

}

void OGLWidget::setFillColor(QColor col)
{
    QString sColor = QString("rgba(%1, %2, %3, %4)").arg(col.red()).arg(col.green()).arg(col.blue()).arg(col.alpha());
    fillColor = col;
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
void OGLWidget::myRenderText( QGLWidget* w, int x, int y,int z, const QString& text, const QColor& col , const QFont& font  )
{
    if (text.isEmpty()) return;

   // qDebug() <<"myRenderText begin";
    /*glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0, w->width(), w->height(), 0, 1000000, -2000000 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    //glLoadIdentity();*/

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRasterPos3i( x, y, z );
    glDrawPixels( rect.width(), rect.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits() );
    glDisable(GL_BLEND);
    /*glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );*/
    glPopMatrix();
  //  qDebug() <<"myRenderText end";

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
void OGLWidget::fillText( QString str,QColor color, int x, int y, int z)
{

   /* // qDebug() << "ARG1:  " << str.size();
    // qDebug() << "ARG2:  " << arg2;
    // qDebug() << "ARG3:  " << arg3;
    if(arg1.isValid() && arg2.isValid() && arg3.isValid())
       if(canvas != NULL)
   */

    qglColor(color);
   // glDisable(GL_DEPTH_TEST);
  //  qDebug() << "SHOW_Z " << z;


    //renderText(x, y, str,textFont);
    myRenderText(this,x,y,z,str,color,textFont);
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
        // qDebug() << deleteWT << "WT == symbolPositionList" << symbolPositionList.size();
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
                // qDebug() << "startNEW with:  "<< hex << listWords[n + 1];
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
                    // qDebug() << "set animation speed";
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
    busy = true;
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
         // qDebug()<<listChars;

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
    tickTimer.start(delay);
    /*while (tickTimer.isActive()) {
       qApp->processEvents();
    }*/
    busy = false;
 //   // qDebug() << "Y: " << y;
   // // qDebug() << "Y: " << y;
    return res;
}

void OGLWidget::drawTextBuffer( int m_x, int m_y, int m_width, int m_height, int z, bool cross)
{
     busy = true;
    //if(!crossTextV2())
     //   return QPoint(0, 0);
    //int width = fMetrics->width(str)*1.125 ;//+ fMetrics->leftBearing(str.at(0)) + fMetrics->rightBearing(str.at(0));

    clearCanvas(m_x, m_y);
    int maxDrawElm = (m_height/(lineHeight + pt)) - 1;
    //qDebug() << "DRAW   "   <<  maxDrawElm;
    int CurRow = convertTextBoxToBufferIndex(cursorIndex).y();
    if(CurRow >= indexRowInList + maxDrawElm)
    {
        indexRowInList += CurRow - (indexRowInList + maxDrawElm) + 1;
    }
    if(CurRow < indexRowInList)
    {
        indexRowInList = CurRow;
    }
    indexFirstDrawSymbol = getFirstSymbolOfString(indexRowInList, false);

    int lastRow = indexRowInList + maxDrawElm - 1;
    if(lastRow >= stringList.length())
        lastRow = stringList.length() - 1;
    if(lastRow < 0)
        lastRow = 0;
    indexLastDrawSymbol = getLastSymbolOfString(lastRow, false);

    //qDebug() << "First  " << indexFirstDrawSymbol <<    "   " <<  indexRowInList << "    " << indexLastDrawSymbol;
  //  // qDebug() << indexRowInList << "   indexFirstDrawSymbol   :           " << indexFirstDrawSymbol << cross;
 //   // qDebug() << "START draw with indexRowInList " << indexRowInList << "MAX elm " << maxElm << "CUR " << CurRow;
    int i = indexRowInList;
    while( i < stringList.length() && i < indexRowInList + maxDrawElm)
    {
       //// qDebug() << stringList[i] << "@";
        QStringList tabulationStr = stringList[i].split("\t");
        //TODO SET TEXT COLOR TO CANVAS COLOR
        setFillColor(fillColor);
       // for(int j = 0; j < tabulationStr.size(); j++)
       // {
        //    fillText(tabulationStr[j], x, y);
       //     x += fMetrics->width(tabulationStr[j] + "\t");
      //  }
      //  // qDebug() << "C:"<<colors.length();
    for (int k = 0 ; k< colors.length();k++)
    {
        int columnOfColorStrBegin;
        int columnOfColorStrEnd;

           int rowOfColorStrBegin =  convertTextBoxToBufferIndex(colors[k].startIndex).y();//Рядок в якому починається стрічка з кольором
           int rowOfColorStrEnd = 0;
           //Якщо не дійшли до останнього кольору, то встановл. рядок кінця стрічи з початку наступної кольорової
           if (k<colors.length()-1)rowOfColorStrEnd=convertTextBoxToBufferIndex(colors[k+1].startIndex ).y();
           //Якщо останній колір, то така стрічка закінчується в останньому рядку
           else rowOfColorStrEnd=stringList.length()-1;
           //Якщо ColorIndex в цій стрічці відсутній, то переходим на інший ColorIndex
             if (!(i>=rowOfColorStrBegin && i<=rowOfColorStrEnd))
                 continue;
           //Якщо на рядку, в якому починається кольорова стрічка — то стовпчик початку берем одразу з QList<ColorIndex> colors
           if (i==rowOfColorStrBegin)
               columnOfColorStrBegin =  convertTextBoxToBufferIndex(colors[k].startIndex ).x();
           //Інакше стовпчик початку - нульовий стовпчик . Інфа 100%
           else columnOfColorStrBegin = 0;
           //Якщо на останньому кольорі, то стовпчик кінця — індекс останнього символу стрічки.
             if (k==colors.length()-1) columnOfColorStrEnd =  stringList[i].length();
             else
                 //якщо не останній колір і на останній стрічці, то стовпчик кінця — стовпчик початку наступної стрічки з кольором
           if (i==stringList.length()-1)  columnOfColorStrEnd =  convertTextBoxToBufferIndex(colors[k+1].startIndex ).x();
            //Якщо не останній колір і не остання стрічка, то стовпчик кінця —
           else
           {
               //Якщо в цій самій стрічці починається інша кольорова стрічка то кінцевий стовпчик поточної
               //Кольорової стрічки - це почато наступної
               if (convertTextBoxToBufferIndex(colors[k+1].startIndex ).y()==i)
               columnOfColorStrEnd =  convertTextBoxToBufferIndex(colors[k+1].startIndex ).x();
               //Інакше КС(кінцевий стовпчик) — це кінець стрічки
               else columnOfColorStrEnd =  stringList[i].length();
           }
             QString textToWarp;
            //Якщо перша кольорова стрічка, то додаєм до локального Х ширину стрічки, що йшла до кольорової стрічки
            if (k==0)
           textToWarp= stringList[i].mid(0,columnOfColorStrBegin);
           else  {
                int  columnOfColorStrBeginPrev=0;
                if (convertTextBoxToBufferIndex(colors[k-1].startIndex ).y()==i)
                    columnOfColorStrBeginPrev=convertTextBoxToBufferIndex(colors[k-1].startIndex ).x();
                textToWarp= stringList[i].mid(columnOfColorStrBeginPrev,columnOfColorStrBegin-columnOfColorStrBeginPrev);
            }
            x+=fMetrics->width(textToWarp);
            setFillColor(colors[k].value);
            QString textToFill = stringList[i].mid(columnOfColorStrBegin,columnOfColorStrEnd-columnOfColorStrBegin);
            fillText(textToFill,fillColor,x , y, z);
           // localX+=fMetrics->width(textToFill);
            //setFillColor(QColor(255,255,255));//Костиль, удалити, вистачить верхнього setColor, добавити на початок colors колір канви
           /*  // qDebug() << "columnOfColorStrEnd:" << columnOfColorStrEnd;
             // qDebug() << "columnOfColorStrBegin:" << columnOfColorStrBegin;
            // qDebug()<<"textToFill:"<<textToFill;
              // qDebug()<< "textToWarp:" << textToWarp;
              // qDebug()<<"rowOfColorStrBegin:"<<rowOfColorStrBegin;*/
    }

        y += lineHeight + pt;
        x = m_x;
       // localX=marginLeft;
        i++;
    }
    if(cross)
        crossTextDraw();
    busy = false;

   // updateGL();

}

void OGLWidget::insertToBuffer(const QChar ch)
{
    crossText();
   // crossTextDraw();
    while (isCrossingNow);
    QPoint convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
   // // qDebug() << convertedIndex << " " << stringList.size() << " " << ch;
    QString &str =  stringList[convertedIndex.y()];
    if (convertedIndex.x()>=str.length())
        str.append(ch);
    else
        str.insert(convertedIndex.x(), ch);
    cross.insert(cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y(), 0);
  //  qDebug() << "insert " << cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y() << "        " << cross;

  //  DrawTextElm(convertedIndex.y());
    listChars.append(ch);

    emit drawTextChanged();

   // pause(delay);

}

void OGLWidget::deleteFromBuffer(int n)
{

    update();
    int mustDell = qAbs(n);
    int crossCursor = cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y();
    int i = n;
    int deletePositionBegin = cursorIndex;
    QStack<int> colorsToDelete;
    for (int numOfColor = 0; numOfColor < colors.length();numOfColor++){
        ColorMarker& colorMarker = colors[numOfColor];
        bool isLast = numOfColor==colors.length()-1;
        int& startIndex = colorMarker.startIndex;
        if (deletePositionBegin+n<startIndex)startIndex-=n-deletePositionBegin;
        else if (!isLast)
        {
            int nextColorStartIndex = colors[numOfColor+1].startIndex;
            if ( deletePositionBegin+n < nextColorStartIndex )
            {
                startIndex -=n-deletePositionBegin;
            }
            else colorsToDelete.push(numOfColor);
        }
       // {
       // colorsToDelete.push(startIndex);
       // }
    }
    while (!colorsToDelete.isEmpty()){
        colors.removeAt(colorsToDelete.pop());
    }

    while( i != 0)
    {
        cross.removeAt(crossCursor  + i);
        if(i > 0)
            i--;
        else
            i++;
        // qDebug() << "QQQ" << crossCursor + i << "   " << " ::  " << cross;
    }
    while(mustDell > 0)
    {
        QPoint convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
       // cross.insert(cursorIndex - convertedIndex.y(), 0);
        // qDebug() << convertedIndex << "DELL   " << mustDell;
        QString &str =  stringList[convertedIndex.y()];
        int realDell;
        if(n > 0)
        {
            if(mustDell > str.length() - convertedIndex.x())
                realDell = str.length() - convertedIndex.x();
            else
                realDell = mustDell;
            str.remove(convertedIndex.x(), realDell);
            mustDell -= realDell;
            if(mustDell > 0)
            {
                if(convertedIndex.y() + 1 < stringList.length())
                {
                  //  cursorIndex--;
                    mustDell--;
                    stringList[convertedIndex.y()].append(stringList[convertedIndex.y() + 1]);
                    stringList.removeAt(convertedIndex.y() + 1);
                }
                else
                    break;
            }
        }
        else
        {
            if(mustDell > convertedIndex.x())
                realDell = convertedIndex.x();
            else
                realDell = mustDell;
            str.remove(convertedIndex.x() - realDell, realDell);
            cursorIndex -= realDell;
            mustDell -= realDell;
            if(mustDell > 0)
            {
                if(convertedIndex.y() != 0)
                {
                    cursorIndex--;
                    mustDell--;
                    stringList[convertedIndex.y() - 1].append(str);
                    stringList.removeAt(convertedIndex.y());
                }
                else
                    break;
            }
        }

    }
    /*
    if (convertedIndex.x()>=str.length())
        str.append(ch);
    else

    DrawTextElm(convertedIndex.y());
    listChars.append(ch);
*/
    emit drawTextChanged();
   // pause(delay);
}

void OGLWidget::moveCursor(int n, bool withWrapShift)
{
    update();
    int j = 0;
    int shift = 0;
    /*if(withWrapShift)
    {
        int max = qAbs (convertTextBoxToBufferIndex(cursorIndex).y() - convertTextBoxToBufferIndex(cursorIndex + n).y());
        while( j < wrapShift.size() && j < max) //bhfhfghfghfghfghfghfghfghfghfghfghgf\ml0011
            if(wrapShift[j++] <= cursorIndex)
                shift = j;
    }
    */
   /* int maxSymbol = getLastSymbolOfString(stringList.length() - 1, false);
    if( maxSymbol < n)
        n = maxSymbol;*/
   // qDebug() << "MAX_SYMBOL" << maxSymbol;
    if(n > 0)
        cursorIndex += n + shift;
    else
        cursorIndex += n -  shift;
    //cursorIndex += n;
    if(cursorIndex < 0)
        cursorIndex = 0;
 //   // qDebug() << "Cursor move to n " << n <<"=== cur state " << cursorIndex << "QPOINT  " << convertTextBoxToBufferIndex(cursorIndex);

}
int OGLWidget::getCountNullString(int index)
{
    int i = 0;
    int sumLength = 0;
    while( i <= index)
    {
        int nextLen = stringList[i].length();
        if(nextLen == 0)
            sumLength++;
        i++;
    }
    return sumLength;
}

void OGLWidget::storeMousePos()
{
    if (isMousePress){

        if (drawBrushElm->getCoords().length()==0)drawBrushElm->addBrush(m_manager.getCreatedBrush());
            drawBrushElm->addCoord(QPoint(mousePos.x(),mousePos.y()));
   // qDebug()<<"position stored:"<<QCursor::pos();
    }
}

int OGLWidget::getFirstSymbolOfString(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    while( i < index)
    {
        int nextLen = stringList[i].length();
        if(!symbol)
            nextLen++;
        sumLength +=  nextLen;
        i++;
    }
    //if(sumLength != 0)
      //  sumLength++;
                return sumLength;
}
int OGLWidget::getLastSymbolOfString(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    while( i <= index)
    {
        int nextLen = stringList[i].length();
        if(!symbol)
            nextLen++;
        sumLength +=  nextLen;
        i++;
    }
    //if(sumLength != 0)
      //  sumLength++;
    return sumLength + 1;
}

QPoint OGLWidget::convertTextBoxToBufferIndex(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    int numParagraph = 0;
    while( i < stringList.length())
    {
      //  // qDebug() <<"stringList:"<<stringList.length();
        int lenNext;
        if(symbol)
            lenNext = stringList[i].length();
        else
            lenNext = stringList[i].length() + 1;
        sumLength += lenNext;
     //   // qDebug() <<"sumLength:"<<sumLength;
//        // qDebug() <<"index:"<<index;
//        // qDebug() <<"I:"<<i;

        if(sumLength > index)
        {
            int colum = index - (sumLength - lenNext);
            int row = i;
           return QPoint( colum, row);
        }
        i++;
    }
    return QPoint(stringList[i - 1].length(), i - 1);
}

ListControll* OGLWidget::getTimeLine()
{
    return timeLine;
}

int OGLWidget::getRowFromTextBoxIndex(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    while( i < stringList.length())
    {
        int lenNext;
        if(symbol)
            lenNext = stringList[i].length();
        else
            lenNext = stringList[i].length() + 1;
        sumLength += lenNext;
        if(sumLength > index)
        {
           return i;
        }
        i++;
    }
}

void OGLWidget::testWrap(int kIndexOfRow)
{
    int i = kIndexOfRow;
    int length = stringList.length();
    while(stringList.length() > i)
    {
        QString &str =  stringList[i];
        int width = fMetrics->width(stringList[i]) ;//+ fMetrics->leftBearing(str.at(0)) + fMetrics->rightBearing(str.at(0));
        ////// qDebug() <<"str:"<< maxWidth;
        if(width > maxWidth)
        {

            int j = stringList[i].size() - 1;
            while( j >= 0 && str[j] > ' ')
            {
             //   // qDebug() << str[j];
                j--;
            }


            if(j < 0)
                j = stringList[i].length() - 1;

         //   // qDebug() <<"strSize:    " << stringList.size() << "    SIZE_i    " << stringList[i] << "     " << j;
            nextRow(j, i, false);
            wrapShift.append(getFirstSymbolOfString(i + 1));
                // qDebug() << "WRAPSHIFT"<< wrapShift;

        }
        i++;
    }
}

void OGLWidget::nextRow( int n, int Row, bool wrap)
{
    //isLastRow();
    QPoint convertedIndex;
    if(Row == -1)
    {
        if( n == -1)
            convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
        else
            convertedIndex = convertTextBoxToBufferIndex(n);
    }
    else
        convertedIndex = QPoint(n, Row);

    int i = convertedIndex.y() + 1;
    QString lastStr = stringList[i - 1].right(stringList[i - 1].length() - convertedIndex.x());

 //   // qDebug() << "           LASTSTR    " << lastStr << "         " << convertedIndex.x();
    if(i >= stringList.length())
        stringList.append(lastStr);
    else
        stringList.insert(i, lastStr);
    stringList[i - 1].resize(convertedIndex.x());
    moveCursor(1, false );
    /* last work
    moveCursor(lastStr.length() + 1);
    */
   /* if(wrap)
        testWrap(i);*/
    emit drawTextChanged();

}

void OGLWidget::isLastRow()
{
    int maxElm = (height()/lineHeight + pt);

}
void OGLWidget::update(){
    busy = true;
    crossText();
        crossTextDraw();
        moveEvent(NULL);
       // busy = false;
}

bool OGLWidget::crossTextDraw()
{
    glDisable(GL_DEPTH);
    for( int i = 0; i < listOfAnimationFigure.length(); i++)
    {
        if(drawAnimationFigure(listOfAnimationFigure[i]))
        {
            for( int j = listOfAnimationFigure[i].start; j < listOfAnimationFigure[i].stop; j++) // convert to cross without animation
                cross[j] = 1;
            listOfAnimationFigure.remove(i);
  //          qDebug() << cross;
        }

    }
    glEnable(GL_DEPTH);
    int y;
    int x1, x2, x;
    bool lastGood = false;
    bool needNextRow = false;
    int last = cross.length();
    if(indexLastDrawSymbol != 0)
        last = indexLastDrawSymbol;

    for(int i = indexFirstDrawSymbol; i < cross.length(); i++)
    {

        if(cross[i] != 0)
        {
            QPoint conv = convertTextBoxToBufferIndex(i, true);
        //    conv = convertTextBoxToBufferIndex(i + conv.y());
            if(!lastGood)
            {
                x1 = marginLeft + fMetrics->width(stringList[conv.y()].left(conv.x()));
                x = i;
                y = /*(lineHeight + pt)* */  convertTextBoxToBufferIndex(i, true).y();
                lastGood = true;
                continue;
            }
            if(conv.y() == y)
            {
                if(i != cross.length() - 1)
                    continue;
            }
            {
                needNextRow = true;
            }
        }
        if(lastGood)
        {

            QPoint conv = convertTextBoxToBufferIndex(i - 1, true);
        //    conv = convertTextBoxToBufferIndex(i + conv.y() + 1);
            // qDebug() << "YYYYYYYYYYYYYYYYYYYYYYY" << y;
            y -=   indexRowInList;
            // qDebug() << "YYYYYYYYYYYYYYYYYYYYYYY2" << y;
            ++y *= lineHeight + pt;
            // QRect rect = fm.boundingRect( text);
            y -= 0.5f * fMetrics->height();// first paid + midle LABEL1

            x2 = marginLeft + fMetrics->width(stringList[conv.y()].left(conv.x() + 1));
            y += marginTop;
            if( cross[i - 1] == -1 && curStatus == PLAY )
            {
                // qDebug() << "FIRST";
               // drawAnimationFigure(x1, y, x2, y, LINE, 0);
                //drawAnimationFigure(x1, y, x2, y, LINE, 0);
                listOfAnimationFigure.append(AnimationFigure(QRect(x1, y, x2, y), (int)LINE, x, i));
                for( int j = x; j < i; j++) // convert to cross without animation
                    cross[j] = 0;
            }
            else{
                //drawFigure(x1, y, x2, y, LINE, 0);
                drawFigure(x1,y, x2, y, LINE, 0);
                 // qDebug() << "SECOND";
            }
            lastGood = false;
            if(needNextRow)
                i--;
        }
    }

}

bool OGLWidget::crossText()
{
  //  // qDebug() << "www " << deleteWT << cross;
    int spacePaid = 1;
    int row = convertTextBoxToBufferIndex(cursorIndex).y();
    while(deleteWT > 0)
    {
        //// qDebug() << "DW " << deleteWT << convertTextBoxToBufferIndex(cursorIndex);
        int cursor = cursorIndex - row;
       /*   space paid
        *
        *  while( cursor - spacePaid >= 0)
        {
            QPoint convert = convertTextBoxToBufferIndex(cursor - spacePaid, true);
            //// qDebug() << "\nSYMBOL                 :::" << cursor  - spacePaid <<"         " << stringList[convert.y()][convert.x()];
            if(stringList[convert.y()][convert.x()] <= 0x20)
                spacePaid++;
            else
                break;
        }*/
        cursor -= spacePaid;
        if(cursor >= 0 && cursor < cross.length())
        {
            if(crossWithAnimation)
                cross[cursor] = -1;
            else
                cross[cursor] = 1;
        }

        deleteWT--;
        spacePaid++;
    }


}

void OGLWidget::displayText(QString const &text, QColor color)
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
