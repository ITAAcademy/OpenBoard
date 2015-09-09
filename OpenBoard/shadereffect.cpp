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

QVector<ShaderEffect> ShaderEffect::creatStartEndEffect(int time)
{
    QVector<ShaderEffect> res;
    res = creatEndEffect(time) + creatStartEffect(time);
    return res;
}

QVector<ShaderEffect> ShaderEffect::creatEndEffect( int time )
{
    ShaderEffect alphaEffect2(OGLWidget::ALPHA_SHADER);
    alphaEffect2.setEffectTimeHowLong(time);
    alphaEffect2.setReverse(true);
    alphaEffect2.setStartTimeMS(time);
    alphaEffect2.setAnchorToEnd(true);
    QVector<ShaderEffect> res;
    res.append(alphaEffect2);
    return res;
}

QVector<ShaderEffect> ShaderEffect::creatStartEffect(int time)
{
    ShaderEffect alphaEffect(OGLWidget::ALPHA_SHADER);
    alphaEffect.setEffectTimeHowLong(time);
    alphaEffect.setStartTimeMS(0);
    QVector<ShaderEffect> res;
    res.append(alphaEffect);
    return res;

}

QVector<ShaderEffect> ShaderEffect::creatEffectByNum(int num, int time)
{
    QVector<ShaderEffect> res;
    switch (num) {
    case 1:
        res =  creatStartEffect(time);
        break;
    case 2:
        res =  creatEndEffect(time);
        break;
    case 3:
        res =  creatStartEndEffect(time);
        break;
    }
    return res;
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
