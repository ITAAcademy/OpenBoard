#ifndef SHADERPROGRAMWRAPPER_H
#define SHADERPROGRAMWRAPPER_H

#include <QObject>
#include <QFile>
#include <QtOpenGL>
#include "openglwidget.h"
class QOpenGLFunctions_3_0;
 class OGLWidget;
class ShaderProgramWrapper
{

GLuint ShaderProgram;
bool inited = false;
QString info;
int errorStatus = 0;
OGLWidget *parentWidget = NULL;
QOpenGLFunctions_3_0 *glf;
QString fragCode, vertCode;
public:
    ShaderProgramWrapper(OGLWidget *pWidget);
    ShaderProgramWrapper();
    ~ShaderProgramWrapper();
   int initShader(QString fragmentShaderCode, QString vertexShaderCode, bool isFilePath=true);
   bool setUniform(QString name, QVariant value);
   GLuint getShaderProgram();
   bool isInited();

   bool save(QDataStream &stream);
   bool load(QDataStream &stream);
   QString getInfo() const;
};

#endif // SHADERPROGRAMWRAPPER_H
