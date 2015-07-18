
#include "openglwidget.h"
/*
 *scroll
 *
int k = canvas->property("scroll").toInt() - 10;
canvas->setProperty("scroll", k);
*/

OGLWidget::loadTextures(){

    if(!img.load(":/ThirdPart/images/start.png")) // QCoreApplication::applicationDirPath()+"/star.png"
    {
        //loads correctly
        qWarning() << "ERROR LOADING IMAGE" + QCoreApplication::applicationDirPath()+"/star.png";
    }
    GL_formatted_image = QGLWidget::convertToGLFormat(img);
    if(GL_formatted_image.isNull())
        qWarning("IMAGE IS NULL");
    else
        qWarning("IMAGE NOT NULL");
    //generate the texture name
    glEnable(GL_TEXTURE_2D); // Enable texturing

       glGenTextures(1, &texture); // Obtain an id for the texture
       glBindTexture(GL_TEXTURE_2D, texture); // Set as the current texture

       //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


       glTexImage2D(GL_TEXTURE_2D, 0, 4, GL_formatted_image.width(), GL_formatted_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits());
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);



       glDisable(GL_TEXTURE_2D);

    //bind the texture ID
}
OGLWidget::drawImage(){
//loadTextures();
  // glLoadIdentity();
     qglColor(Qt::white);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_QUADS);
            //Draw Picture
    glTexCoord2i(0,0); glVertex2i(0,way);
    glTexCoord2i(0,1); glVertex2i(0,0);
    glTexCoord2i(1,1); glVertex2i(wax,0);
    glTexCoord2i(1,0); glVertex2i(wax,way);

    glEnd();
    glDisable(GL_TEXTURE_2D);

}

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    //qRegisterMetaType<DrawData>("DrawData");
   // engine()->rootContext()->setContextProperty(QLatin1String("forma"), this);
    m_encoder = new AV_REncoder(this);

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
    realDelay = 0;

    maxWidth = width() - marginLeft;
    stringList.append("");
    //stringList.reserve(600000);
    indexRowInList = 0;
    cursorIndex = 0;
    isCrossingNow = false;

    //OPENGL
    setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
       glDepthFunc(GL_LEQUAL); // Буфер глубины
       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
       timer->start(5);

}

OGLWidget::~OGLWidget()
{

}

void OGLWidget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    wax=nWidth;
    way=nHeight;
}
void OGLWidget::initializeGL()
{
    qglClearColor(Qt::black); // Черный цвет фона
     //glEnable(GL_TEXTURE_2D);
     loadTextures();
}

void OGLWidget::moveEvent(QMoveEvent *event)
{

}

void OGLWidget::paintGL()
{
    m_encoder->setFrame(grabFrameBuffer());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
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
       glOrtho(0,wax,way,0,1,0); // подготавливаем плоскости для матрицы
       glEnable(GL_BLEND);
       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      // qglColor(Qt::white);
        drawImage();
        drawBuffer();

        //busy = true;

        // glBegin и glEnd - обозначают блок для рисования объекта(начало и конец), glBegin принимает параметр того, что нужно рисовать.
       // qglColor(Qt::green);

         //Начинаем отрисовку, аргумент означает отрисовку прямоугольника.
         //Каждый вызов glVertex3f задает одну вершину прямоугольника
       // swapBuffers();


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
    QGLWidget::resizeEvent(envent);
    maxWidth = width() - marginLeft;
}

void OGLWidget::closeEvent(QCloseEvent *event)
{
    stopAnimated();
    pause(500);
    if(fMetrics != NULL)
        delete fMetrics;
    isClose = true;
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    //crossOutLastSymbol();
}

QString OGLWidget::getDrawText()
{
    return drawText;
}

void OGLWidget::setDrawText(QString data)
{
    drawText = data;
}



void OGLWidget::drawAnimated(bool record)
{
    if(curStatus == this->PAUSE)
    {
        //m_recorder->resume();
        curStatus = PLAY;
        m_encoder->pause();
        return;
    }
    if(record)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Choose file..."), qApp->applicationDirPath(), tr("Videos (*.avi *.mp4)"));
        if(!fileName.size())
            return;
        m_encoder->setFileName(fileName);
        m_encoder->setGrabWidget(this);
        m_encoder->startRecord();
        qDebug() << "Start record into file";
    }
    curStatus = PLAY;
    bRecord = record;
    tickTimer.start();
    qDebug() << "Start play";
}

void OGLWidget::stopAnimated()
{
    pause(100);
    curStatus = STOP;
    tickTimer.stop();
    m_encoder->stop();
    // max speed // stop draw function
    double t_animationSpeed = animationSpeed;
/*    int t_delay = delay;

    animationSpeed = 1;
    delay = 1;
    while(busy)
    {
         qApp->processEvents();
    }
    animationSpeed = t_animationSpeed;
    delay = t_delay;
*/
    bRecord = false;
 //   pause(200);
    qDebug() << "Stop play";

}

void OGLWidget::pauseAnimated()
{
    curStatus = PAUSE;
    qDebug() << "Pause play";
    m_encoder->pause();
    //m_recorder->pause();
}
bool OGLWidget::isRecord() const
{
    return bRecord;
}


void OGLWidget::clearCanvas()
{
    //QMetaObject::invokeMethod(canvas, "clear");
    symbolPositionList.clear();
    listWords.clear();
    listStr.clear();
    indexRow = 0;
    indexW = 1;
    x = marginLeft;
    y = lineHeight + pt;
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
    deleteWT = 0;
    crossWithAnimation = false;
}

void OGLWidget::clearSymbol(int index){
QMetaObject::invokeMethod(canvas, "clearSymbol",  Q_ARG(QVariant, QVariant(index)));
}

void OGLWidget::drawFigure(int x, int y, int x2, int y2, OGLWidget::FigureType type, bool fill = true, QColor col = "#FF0000", float size = 2)
{
    //qDebug()<<"void OGLWidget::drawFigure";
    glDisable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
    qglColor(QColor(Qt::red));
    glBegin(GL_LINES);
     glLineWidth(3.0f);
       glVertex2i( x,y);
       glVertex2i( x2,y);
       qDebug()<<"x:"<<x;
        qDebug()<<"y:"<<y;
         qDebug()<<"x2:"<<x2;
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

void OGLWidget::drawAnimationFigure(int x, int y, int width, int height, OGLWidget::FigureType type, bool fill)
{
    isCrossingNow=true;
    float persent;
    while(persent < 1)
    {
        drawFigure(x, y, x + (width - x)*persent, height, type, fill);
     //   qDebug() << delPos.x() << "             " << delPos.x() + (maxWidth - delPos.x())*persent;
        persent += animationSpeed;
        swapBuffers();
         QThread::currentThread()->msleep(10);
     //   pause(10);
        if(curStatus == STOP )
            return;
    }
    drawFigure(x, y, width, height, type, fill);
    isCrossingNow=false;
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
  //  qDebug() << "URAAAA!!!  " << deleteWT;
    crossOutLastSymbol(n);
    crossWithAnimation = true;
}

void OGLWidget::generateFrames()
{
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
    animationSpeed = (double)1/(value*0.6);
    qDebug() << animationSpeed;
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

void OGLWidget::setFillGradient(int x, int y, int width, int height, GradientSetting color)
{

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
void OGLWidget::fillText( QString str,QColor color, int x, int y)
{

   /* qDebug() << "ARG1:  " << str.size();
    qDebug() << "ARG2:  " << arg2;
    qDebug() << "ARG3:  " << arg3;
    if(arg1.isValid() && arg2.isValid() && arg3.isValid())
       if(canvas != NULL)
   */

    qglColor(color);
    renderText(x, y , str,textFont);
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

void OGLWidget::fillAnimationText(QString str, int x, int y, float time)
{
    /*QTimer timer;
    timer.setInterval(time);*/
    GradientSetting color;
    color.addColorStop(0,0,255,0);
    color.addColorStop(0.85f,0,255,0,255);
    int widthX = fMetrics->width(str) + x + 35;
    int widthT = fMetrics->width(str) + 35;
    int heightT = fMetrics->height() + y + 35;
    float nx = x - widthT;
    while(nx <= widthX)
    {
        setFillGradient(x - widthT, y, 250, heightT, color);
        fillText(str,fillColor,x, y);
        this->update();
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        nx += widthT/time;
       // Sleep(time);
    }
}



bool OGLWidget::crossTextV2()
{
    /*
    if(deleteWT != 0 && !symbolPositionList.isEmpty())
    {
        qDebug() << deleteWT << "WT == symbolPositionList" << symbolPositionList.size();
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
                qDebug() << "startNEW with:  "<< hex << listWords[n + 1];
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
                    qDebug() << "set animation speed";
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
         qDebug()<<listChars;

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
 //   qDebug() << "Y: " << y;
   // qDebug() << "Y: " << y;
    return res;
}

void OGLWidget::drawBuffer()
{
     busy = true;
    framDelayTimer.restart();
    //if(!crossTextV2())
     //   return QPoint(0, 0);
    //int width = fMetrics->width(str)*1.125 ;//+ fMetrics->leftBearing(str.at(0)) + fMetrics->rightBearing(str.at(0));
    //qDebug() << "DRAW";
    clearCanvas();
    int maxDrawElm = (height()/(lineHeight + pt)) - 1;
    int CurRow = convertTextBoxToBufferIndex(cursorIndex).y();
    if(CurRow >= indexRowInList + maxDrawElm)
    {
        indexRowInList += CurRow - (indexRowInList + maxDrawElm) + 1;
    }
    if(CurRow < indexRowInList)
    {
        indexRowInList = CurRow;
    }
    indexFirstDrawSymbol = getFirstSymbolOfString(indexRowInList, true);
  //  qDebug() << indexRowInList << "   indexFirstDrawSymbol   :           " << indexFirstDrawSymbol << cross;
 //   qDebug() << "START draw with indexRowInList " << indexRowInList << "MAX elm " << maxElm << "CUR " << CurRow;
    int i = indexRowInList;
    while( i < stringList.length() && i < indexRowInList + maxDrawElm)
    {
       //qDebug() << stringList[i] << "@";
        QStringList tabulationStr = stringList[i].split("\t");
        //TODO SET TEXT COLOR TO CANVAS COLOR
        setFillColor(fillColor);
       // for(int j = 0; j < tabulationStr.size(); j++)
       // {
        //    fillText(tabulationStr[j], x, y);
       //     x += fMetrics->width(tabulationStr[j] + "\t");
      //  }
      //  qDebug() << "C:"<<colors.length();
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
            fillText(textToFill,fillColor,x,y);
           // localX+=fMetrics->width(textToFill);
            //setFillColor(QColor(255,255,255));//Костиль, удалити, вистачить верхнього setColor, добавити на початок colors колір канви
           /*  qDebug() << "columnOfColorStrEnd:" << columnOfColorStrEnd;
             qDebug() << "columnOfColorStrBegin:" << columnOfColorStrBegin;
            qDebug()<<"textToFill:"<<textToFill;
              qDebug()<< "textToWarp:" << textToWarp;
              qDebug()<<"rowOfColorStrBegin:"<<rowOfColorStrBegin;*/
    }

        y += lineHeight + pt;
        x = marginLeft;
       // localX=marginLeft;
        i++;
    }
    crossTextDraw();
    busy = false;

   // updateGL();

}

void OGLWidget::insertToBuffer(const QChar ch)
{
    crossText();
    crossTextDraw();
    while (isCrossingNow);
    QPoint convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
   // qDebug() << convertedIndex << " " << stringList.size() << " " << ch;
    QString &str =  stringList[convertedIndex.y()];
    if (convertedIndex.x()>=str.length())
        str.append(ch);
    else
    str.insert(convertedIndex.x(), ch);
    cross.insert(cursorIndex - convertedIndex.y(), 0);

    testWrap(convertedIndex.y());
    listChars.append(ch);

    emit drawTextChanged();

    pause(delay);

}

void OGLWidget::deleteFromBuffer(int n)
{

    update();
    int mustDell = qAbs(n);
    int crossCursor = cursorIndex - convertTextBoxToBufferIndex(cursorIndex).y();
    int i = n;
    while( i != 0)
    {
        cross.removeAt(crossCursor  + i);
        if(i > 0)
            i--;
        else
            i++;
        qDebug() << "QQQ" << crossCursor + i << "   " << " ::  " << cross;
    }
    while(mustDell > 0)
    {
        QPoint convertedIndex = convertTextBoxToBufferIndex(cursorIndex);
        cross.insert(cursorIndex - convertedIndex.y(), 0);
        qDebug() << convertedIndex << "DELL   " << mustDell;
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

    testWrap(convertedIndex.y());
    listChars.append(ch);
*/
    emit drawTextChanged();
    pause(delay);
}

void OGLWidget::moveCursor(int n)
{
    update();
    cursorIndex += n;
    if(cursorIndex < 0)
        cursorIndex = 0;
 //   qDebug() << "Cursor move to n " << n <<"=== cur state " << cursorIndex << "QPOINT  " << convertTextBoxToBufferIndex(cursorIndex);

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

QPoint OGLWidget::convertTextBoxToBufferIndex(int index, bool symbol)
{
    int i = 0;
    int sumLength = 0;
    int numParagraph = 0;
    while( i < stringList.length())
    {
      //  qDebug() <<"stringList:"<<stringList.length();
        int lenNext;
        if(symbol)
            lenNext = stringList[i].length();
        else
            lenNext = stringList[i].length() + 1;
        sumLength += lenNext;
     //   qDebug() <<"sumLength:"<<sumLength;
//        qDebug() <<"index:"<<index;
//        qDebug() <<"I:"<<i;

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
        ////qDebug() <<"str:"<< maxWidth;
        if(width > maxWidth)
        {
            int j = stringList[i].size() - 1;
            while( j >= 0 && str[j] > ' ')
            {
             //   qDebug() << str[j];
                j--;
            }


            if(j < 0)
                j = stringList[i].length() - 1;

         //   qDebug() <<"strSize:    " << stringList.size() << "    SIZE_i    " << stringList[i] << "     " << j;
            nextRow(j, i, false);

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

 //   qDebug() << "           LASTSTR    " << lastStr << "         " << convertedIndex.x();
    if(i >= stringList.length())
        stringList.append(lastStr);
    else
        stringList.insert(i, lastStr);
    stringList[i - 1].resize(convertedIndex.x());
    moveCursor();
    /* last work
    moveCursor(lastStr.length() + 1);
    */
    if(wrap)
        testWrap(i);
    emit drawTextChanged();

}

void OGLWidget::isLastRow()
{
    int maxElm = (height()/lineHeight + pt);

}
void OGLWidget::update(){
    busy = true;
        crossText();
       // busy = false;
}

bool OGLWidget::crossTextDraw()
{
    int y;
    int x1, x2, x;
    bool lastGood = false;
    bool needNextRow = false;
    for(int i = indexFirstDrawSymbol; i < cross.length(); i++)
    {
        //qDebug() << "CROSS [i]:" << cross[i];
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
            qDebug() << "YYYYYYYYYYYYYYYYYYYYYYY" << y;
            y -=   indexRowInList;
            qDebug() << "YYYYYYYYYYYYYYYYYYYYYYY2" << y;
            ++y *= lineHeight + pt;
            y -= 0.25f * fMetrics->height();// first paid + midle

            x2 = marginLeft + fMetrics->width(stringList[conv.y()].left(conv.x() + 1));
            if( cross[i - 1] == -1)
            {
                qDebug() << "FIRST";
               // drawAnimationFigure(x1, y, x2, y, LINE, 0);
                drawAnimationFigure(x1, y, x2, y, LINE, 0);

                for( int j = x; j < i; j++) // convert to cross without animation
                    cross[j] = 1;
            }
            else{
                //drawFigure(x1, y, x2, y, LINE, 0);
                drawFigure(x1,y, x2, y, LINE, 0);
                 qDebug() << "SECOND";
            }
            lastGood = false;
            if(needNextRow)
                i--;
        }
    }
}

bool OGLWidget::crossText()
{
  //  qDebug() << "www " << deleteWT << cross;
    int spacePaid = 1;
    int row = convertTextBoxToBufferIndex(cursorIndex).y();
    while(deleteWT > 0)
    {
        //qDebug() << "DW " << deleteWT << convertTextBoxToBufferIndex(cursorIndex);
        int cursor = cursorIndex - row;
       /*   space paid
        *
        *  while( cursor - spacePaid >= 0)
        {
            QPoint convert = convertTextBoxToBufferIndex(cursor - spacePaid, true);
            //qDebug() << "\nSYMBOL                 :::" << cursor  - spacePaid <<"         " << stringList[convert.y()][convert.x()];
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
