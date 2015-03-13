#include "glwidget.h"
#include <QFont>

static GLWidget *msRender = 0;

GLWidget *GLWidget::glRender()
{
    return msRender;
}

GLWidget::GLWidget()

{
    msRender = this;
    //-------------------------------------------
    mFont.setPixelSize(16);
    mFont.setBold(true);
    QFontMetrics metricts(mFont);
    mX = 0;
    mY = metricts.height();
    mCharWidth = metricts.width('w');
    mCharHeight = metricts.height();
    //mIsShowCursor = true;
}

void GLWidget::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.5,0.5,0.5,1);

    glOrtho(0, 450, 600, 0, 0, 1);

    glEnable(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_TEXTURE_2D);

}
void GLWidget::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //glMatrixMode( GL_PROJECTION );
   glLoadIdentity();

   glOrtho( 0.0, width(), height(), 0.0, -1.0, 1.0 );
   glMatrixMode( GL_MODELVIEW );
   glColor3ub(254, 254, 254);

    //drawText(str);
   /*int y = mY;
   for(int i = 0; i < textArray.size(); ++i)
   {
       renderText(mX, y, textArray[i], mFont);
       y += mCharHeight;
   }*/

   //static int i = 0;
    //int y = mY;
      for(int i = 0; i < textArray.size(); ++i){
          drawText(textArray[i]);

      //++i;
      }
      //update();
}

void GLWidget::resizeGL()
{
    glViewport( 0, 0, width(), height() );
}
void GLWidget::drawText(QString textArray){

    //GLWidget::glRender()->renderText( 10.0, 20.0, 0.0, str, QFont("Arial", 12, QFont::Bold, false) );
    int y = mY;
        renderText(mX, y, textArray, mFont);
        y += mCharHeight;

}

