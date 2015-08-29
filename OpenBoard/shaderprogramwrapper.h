#ifndef SHADERPROGRAMWRAPPER_H
#define SHADERPROGRAMWRAPPER_H

#include <QObject>
#include <QFile>
#include <QtOpenGL>
#include "openglwidget.h"
 class OGLWidget;
class ShaderProgramWrapper
{

GLuint ShaderProgram;
bool inited = false;
int errorStatus = 0;
OGLWidget *parentWidget;
QGLFunctions *glf;
public:
    ShaderProgramWrapper(OGLWidget *pWidget);
    ShaderProgramWrapper();
    ~ShaderProgramWrapper();
   int initShader(QString fragmentShaderCode,QString vertexShaderCode);
   GLuint getShaderProgram();
   bool isInited();
};

#endif // SHADERPROGRAMWRAPPER_H
