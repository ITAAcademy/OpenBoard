#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector>
#include <QFont>
#include <QTimer>

#include <QElapsedTimer>
#include "windows.h"

class GLWidget : public QGLWidget
{
public:
    GLWidget();

public:
    bool    mIsAnimatedStart;

    static GLWidget *glRender();
    void drawText(QString textArray);
    void drawText(QString str,int x,int y);
    void drawAnimated();
    void stopAnimated();
    void pauseAnimated();

    QVector<QString> textArray;
    QString strstr;


protected:
    void initializeGL();
    void paintGL();
    void resizeGL();

private:
    int mX;
    int mY;
    int mCharWidth;
    int mCharHeight;

    QString             mStr;
    QFont               mFont;

public:
    QVector<QString>    textArray;

private:
    int     index;

    QElapsedTimer mElapsedTimer;
    QTimer *mTimer;

};

#endif // GLWIDGET_H
