#include "glwidget.h"
#include <QFont>
#include <QDebug>
#include <QThread>
#include <QChar>

static GLWidget *msRender = 0;

GLWidget *GLWidget::glRender()
{
    return msRender;
}

GLWidget::GLWidget()
    :strstr()
    ,index(0)
    ,mIsAnimatedStart(false)

{
    msRender = this;

    mFont.setPixelSize(14);
    mFont.setBold(true);
    mFont.setFamily("Courier");

    QFontMetrics metricts(mFont);

    mX = 5.0;
    mY = metricts.height();
    mCharWidth = metricts.width('w');
    mCharHeight = metricts.height();
}


// for initialize opengl
void GLWidget::initializeGL()
{
    glClearColor(0.5,0.5,0.5,1);                            // background color
    glOrtho(0.0, 450.0, 600.0, 0.0, 1.0, 0.0);              // plane matrix
    glLoadIdentity();                                       // load matrix
}

// for window resizing
void GLWidget::resizeGL()
{
}

// for image display
void GLWidget::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // clean image buffer and depth buffer
   glMatrixMode(GL_PROJECTION);                             // set matrix
   glLoadIdentity();
   //glViewport(0, 0, width(), height());                     // widget size
   qglColor(Qt::white);                                     // text color (default:white)

   double y = mY;
   for(int i = 0; i < textArray.size(); ++i)
   {
       renderText(mX, y, textArray[i], mFont);
       y += mCharHeight;
   }

   //for rendering text into widget in two cases: if mIsAnimatedStart=true and mIsAnimatedStart=false
   for(int i = 0; i < textArray.size(); ++i)
    {
        QString tmp = textArray[i];
        if (mIsAnimatedStart)
        {
            if(index <= tmp.size())
            {
                strstr.append(tmp[index]);
                setDrawText(strstr);
                index++;
            }
            else
            {
                mTimer->stop();
                setDrawText(strstr);
                index = 0;
                mIsAnimatedStart = false;
            }
        }
        else
        {
            setDrawText(tmp);
        }
        ++i;
    }
}

void GLWidget::_recalculate(const QString &str)
{
    static QFontMetrics mtr(mFont);

    textArray.clear();
    QString tmpStr;
    int lineWidth = 0;
    for(int i = 0; i < str.size(); i++)
    {
        lineWidth += mtr.width(str[i]);
        if(lineWidth > 540)
        {
            textArray.push_back(tmpStr);
            lineWidth = 0;
            tmpStr = str[i];
            continue;
        }

        if(str[i] == '\n')
        {
            textArray.push_back(tmpStr);
            lineWidth = 0;
            tmpStr.clear();
        }
        else
            tmpStr += str[i];
    }
    if(tmpStr.size() > 0)
        textArray.push_back(tmpStr);
}

void GLWidget::setDrawText(const QString &str)
{
    _recalculate(str);
}

void GLWidget::drawAnimated()
{
    mIsAnimatedStart = true;
    mTimer = new QTimer(this);
    mTimer->start(300);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(repaint()));
}
void GLWidget::stopAnimated()
{
    mTimer->stop();
    mIsAnimatedStart = false;
    strstr = "";
    index = 0;
}

void GLWidget::pauseAnimated()
{
    mTimer->stop();
    mIsAnimatedStart = false;
}
