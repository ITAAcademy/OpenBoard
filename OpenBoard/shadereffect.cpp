#include "shadereffect.h"


 int ShaderEffect::getStartTimeMS() const
{
    return startTimeMS;
}

void ShaderEffect::setStartTimeMS(unsigned int value)
{
    startTimeMS = value;
}

 int ShaderEffect::getEffectTimeHowLong() const
{
    return effectTimeHowLong;
}

void ShaderEffect::setEffectTimeHowLong(unsigned int value)
{
    effectTimeHowLong = value;
}

bool ShaderEffect::save(QDataStream &stream)
{
    stream << startTimeMS << effectTimeHowLong << shaderWrapperIndex << reverse;
}
bool ShaderEffect::load(QDataStream &stream)
{
stream >> startTimeMS >> effectTimeHowLong >> shaderWrapperIndex >> reverse;

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

void ShaderEffect::setUniformAnimationKey(ShaderEffect shaderEffect, float keyFrame)
{
    OGLWidget *glWidget = shaderEffect.getShaderWrapper()->getParentWidget();
    GLint keyUnifrom = glWidget->context()->functions()->glGetUniformLocation(shaderEffect.getShaderWrapper()->getShaderProgram()
                        ,"animationKey");

            glWidget->context()->functions()->glUniform1f(keyUnifrom,keyFrame);
}
void ShaderEffect::setUniformResolution(ShaderEffect shaderEffect, float width, float height)
{
   shaderEffect.getShaderWrapper()->setUniformResolution(width,height);
}

void ShaderEffect::setUniformReverse(ShaderEffect shaderEffect, bool val)
{
    OGLWidget *glWidget = shaderEffect.getShaderWrapper()->getParentWidget();

    GLint reverseUnifrom = glWidget->context()->functions()->glGetUniformLocation(shaderEffect.getShaderWrapper()->getShaderProgram()
                        ,"reverse");
    glWidget->context()->functions()->glUniform1i(reverseUnifrom,val);

}
