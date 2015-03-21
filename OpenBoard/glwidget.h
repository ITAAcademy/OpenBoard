#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector>
#include <QTimer>

#include <QElapsedTimer>
#include "windows.h"

class GLWidget : public QGLWidget
{
public:
    GLWidget();

    void setDrawText(const QString &str);

public:
    bool    mIsAnimatedStart;

    static GLWidget *glRender();
    void drawAnimated();
    void stopAnimated();
    void pauseAnimated();

    QVector<QString> textArray;
    QString strstr;

protected:
    void initializeGL();
    void resizeGL();
    void paintGL();

private:
    void _recalculate(const QString &str);
    int     index;

    QElapsedTimer mElapsedTimer;
    QTimer *mTimer;
    QFont   mFont;
    int mX;
    int mY;
    int mCharWidth;
    int mCharHeight;

};

#endif // GLWIDGET_H
