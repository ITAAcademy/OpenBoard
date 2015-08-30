#include "shaderprogramwrapper.h"

ShaderProgramWrapper::ShaderProgramWrapper(OGLWidget *pWidget)
{
    parentWidget=pWidget;
    glf=parentWidget->getOglFuncs();
}

ShaderProgramWrapper::ShaderProgramWrapper()
{

}

ShaderProgramWrapper::~ShaderProgramWrapper()
{
    glf->glDeleteShader(ShaderProgram);
}

int ShaderProgramWrapper::initShader(QString fShaderFilePath,QString vShaderFilePath)
{
    QFile fragmentShadeFile(fShaderFilePath);

    QFile vertexShaderFile(vShaderFilePath);

    QString fragmentShaderCode;
    QString vertexShaderCode;
    errorStatus=0;
             if(fragmentShadeFile.open(QIODevice::ReadOnly | QIODevice::Text))
             {
                 QTextStream in(&fragmentShadeFile);
                 fragmentShaderCode = in.readAll();
                  fragmentShadeFile.close();
                 //qDebug() << "fragmentShaderCode:"<<fragmentShaderCode;
             }
            else
             {
                qDebug() << "error on fragmentShader.glsl resource open";
                errorStatus=-1;
                return -1;

             }


             if(vertexShaderFile.open(QIODevice::ReadOnly | QIODevice::Text))
             {
                 QTextStream in(&vertexShaderFile);
                 vertexShaderCode = in.readAll();
                  vertexShaderFile.close();
             }
             else
             {
                    qDebug() << "error on vertexShader.glsl resource open";
                    errorStatus=-1;
                    return -1;

             }


              ShaderProgram = glf->glCreateProgram();
              GLuint vertexShaderObj = glf->glCreateShader(GL_VERTEX_SHADER);
              GLuint fragmentShaderObj = glf->glCreateShader(GL_FRAGMENT_SHADER);

              const GLchar* p[1];
              p[0] = vertexShaderCode.toLatin1().constData();
              GLint Lengths[1];
              Lengths[0]= vertexShaderCode.length();
              glf->glShaderSource(vertexShaderObj, 1, p, Lengths);

              const GLchar* p2[1];
              p2[0] = fragmentShaderCode.toLatin1().constData();
              GLint Lengths2[1];
              Lengths2[0]= fragmentShaderCode.length();
              glf->glShaderSource(fragmentShaderObj, 1, p2, Lengths2);

              glf->glCompileShader(vertexShaderObj);
              glf->glCompileShader(fragmentShaderObj);

              //Get compile status and errors detected by compiler
              GLint success;
              glf->glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &success);
              if (!success) {
                  GLchar infoLog[1024];
                  glf->glGetShaderInfoLog(vertexShaderObj, sizeof(infoLog), NULL, infoLog);
                   qDebug() <<"Error compiling shader type:" << "GL_VERTEX_SHADER" << infoLog;
                    errorStatus=-1;
                  return -1;

              }
              glf->glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &success);
              if (!success) {
                  GLchar infoLog[1024];
                  glf->glGetShaderInfoLog(fragmentShaderObj, sizeof(infoLog), NULL,infoLog);
                   qDebug() <<"Error compiling shader type:" << "GL_FRAGMENT_SHADER" << infoLog;
                    errorStatus=-1;
                  return -1;

              }

         glf->glAttachShader(ShaderProgram,vertexShaderObj);
          glf->glAttachShader(ShaderProgram,fragmentShaderObj);
        glf->glLinkProgram(ShaderProgram);
        glf->glDeleteShader(vertexShaderObj);
        glf->glDeleteShader(fragmentShaderObj);
        glf->glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
        GLchar errorLog[1024];
        //if (success == 0) {
        if (success == 0) {
            glf->glGetProgramInfoLog(ShaderProgram, sizeof(errorLog), NULL, errorLog);
             qDebug() << "Error linking shader program:" << errorLog;
              errorStatus=-1;
            return -1;

        }
        else
            //qDebug() << "Linking shader program success";
        glf->glValidateProgram(ShaderProgram);
          qDebug() << "Shader supported:"<<parentWidget->isShaderSupported();
            //glLinkProgram(program);
            //glUseProgram(program);
    return -1; // 0

}

GLuint ShaderProgramWrapper::getShaderProgram()
{
    return ShaderProgram;
}

bool ShaderProgramWrapper::isInited()
{
    return inited;
}

