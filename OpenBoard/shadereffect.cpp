#include "shadereffect.h"

ShaderEffect::ShaderEffect(ShaderProgramWrapper *shaderWrp)
{
    qDebug() << "shaderWrapper=shaderWrp";
shaderWrapper=shaderWrp;
}

ShaderEffect::ShaderEffect()
{

}

ShaderEffect::~ShaderEffect()
{

}

ShaderProgramWrapper *ShaderEffect::getShaderWrapper()
{
    return shaderWrapper;
}

void ShaderEffect::setUniformAnimationKey(OGLWidget *oglWidget,ShaderEffect shaderEffect, float keyFrame)
{
    GLint keyUnifrom = oglWidget->context()->functions()->glGetUniformLocation(shaderEffect.getShaderWrapper()->getShaderProgram()
                        ,"animationKey");
    //oglWidget->getShaderPrograms()[OGLWidget::ALPHA_SHADER].getShaderProgram()
         //   float keyFrame = (float)(pDrawWidget->getTimeLine()->getPlayTime()-startDrawTime)/lifeTime;

            qDebug() << "KEY FRAME:"<<keyFrame<<"keyuniform:"<<keyUnifrom;
            //oglWidget->context()->functions()->glUseProgram( oglWidget->getShaderPrograms()[0].getShaderProgram());
            oglWidget->context()->functions()->glUniform1f(keyUnifrom,keyFrame);
}
