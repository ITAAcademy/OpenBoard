#include "shadereffect.h"


unsigned int ShaderEffect::getStartTimeMS() const
{
    return startTimeMS;
}

void ShaderEffect::setStartTimeMS(unsigned int value)
{
    startTimeMS = value;
}

unsigned int ShaderEffect::getEffectTimeHowLong() const
{
    return effectTimeHowLong;
}

void ShaderEffect::setEffectTimeHowLong(unsigned int value)
{
    effectTimeHowLong = value;
}

bool ShaderEffect::save(QDataStream &stream)
{
    stream << startTimeMS << effectTimeHowLong << shaderWrapperIndex;
}
bool ShaderEffect::load(QDataStream &stream)
{
stream >> startTimeMS >> effectTimeHowLong >> shaderWrapperIndex;

}


bool ShaderEffect::getReverse() const
{
    return reverse;
}

void ShaderEffect::setReverse(bool value)
{
    reverse = value;
}

bool ShaderEffect::getAnchorToEnd() const
{
    return anchorToEnd;
}

void ShaderEffect::setAnchorToEnd(bool value)
{
    anchorToEnd = value;
}
ShaderEffect::ShaderEffect(ShaderProgramWrapper *shaderWrp, int shaderIndex)
{
    // qDebug() << "shaderWrapper=shaderWrp";
    shaderWrapper=shaderWrp;
    shaderWrapperIndex=shaderIndex;
}
ShaderEffect::ShaderEffect(int shaderIndex)
{
    // qDebug() << "shaderWrapper=shaderWrp";
    shaderWrapperIndex=shaderIndex;
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

void ShaderEffect::setShaderWrapper(ShaderProgramWrapper *shader)
{
    shaderWrapper=shader;
}
int ShaderEffect::getShaderWrapperIndex()
{
    return shaderWrapperIndex;
}

void ShaderEffect::setUniformAnimationKey(OGLWidget *oglWidget,ShaderEffect shaderEffect, float keyFrame)
{
    GLint keyUnifrom = oglWidget->context()->functions()->glGetUniformLocation(shaderEffect.getShaderWrapper()->getShaderProgram()
                        ,"animationKey");
    //oglWidget->getShaderPrograms()[OGLWidget::ALPHA_SHADER].getShaderProgram()
         //   float keyFrame = (float)(pDrawWidget->getTimeLine()->getPlayTime()-startDrawTime)/lifeTime;

            //qDebug() << "KEY FRAME:"<<keyFrame<<"keyuniform:"<<keyUnifrom;
            //oglWidget->context()->functions()->glUseProgram( oglWidget->getShaderPrograms()[0].getShaderProgram());
            oglWidget->context()->functions()->glUniform1f(keyUnifrom,keyFrame);
}
void ShaderEffect::setUniformResolution(OGLWidget *oglWidget,ShaderEffect shaderEffect, float width, float height)
{
    GLint keyUnifrom = oglWidget->context()->functions()->glGetUniformLocation(shaderEffect.getShaderWrapper()->getShaderProgram()
                        ,"resolution");
    oglWidget->context()->functions()->glUniform2f(keyUnifrom,width,height);
}

void ShaderEffect::setUniformReverse(OGLWidget *oglWidget, ShaderEffect shaderEffect, bool val)
{
    GLint reverseUnifrom = oglWidget->context()->functions()->glGetUniformLocation(shaderEffect.getShaderWrapper()->getShaderProgram()
                        ,"reverse");
    oglWidget->context()->functions()->glUniform1i(reverseUnifrom,val);

}
