#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector>
#include <QFont>

class GLWidget : public QGLWidget
{
public:
    GLWidget();

public:
    static GLWidget *glRender();
    void drawText(QString textArray);


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
};

#endif // GLWIDGET_H
