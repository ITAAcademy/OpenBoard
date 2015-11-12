#include "shadereffect.h"


int ShaderEffect::getStartTimeMS() const
{
    return startTimeMS;
}

void ShaderEffect::setStartTimeMS(int value)
{
    startTimeMS = value;
}

int ShaderEffect::getEffectTimeHowLong() const
{
    return effectTimeHowLong;
}

void ShaderEffect::setEffectTimeHowLong(int value)
{
    effectTimeHowLong = value;
}

bool ShaderEffect::save(QDataStream &stream,float version)
{
    stream << startTimeMS << effectTimeHowLong << shaderWrapperIndex << reverse;

    //shaderWrapper->getParentWidget()->getTimeLine()->get
    if (version > 2.8)
        stream <<count << elementSize ;
    stream << moving << rotateAngle << toPosX << toPosY << toScaleX << toScaleY << moveEffect;

}
bool ShaderEffect::load(QDataStream &stream,float version)
{
    stream >> startTimeMS >> effectTimeHowLong >> shaderWrapperIndex >> reverse;
    if (version > 2.8)
        stream >> count >> elementSize;
    if(version >= 3.2 )
    {
        stream >> moving >> rotateAngle >> toPosX >> toPosY >> toScaleX >> toScaleY >> moveEffect;
    }

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

int ShaderEffect::getCount() const
{
    return count;
}

void ShaderEffect::setCount(int value)
{
    count = value;
}

int ShaderEffect::getElementSize() const
{
    return elementSize;
}

void ShaderEffect::setElementSize(int value)
{
    elementSize = value;
}

bool ShaderEffect::getMoving() const
{
    return moving;
}

void ShaderEffect::setMoving(bool value)
{
    moving = value;
}

int ShaderEffect::getRotateAngle() const
{
    return rotateAngle;
}

void ShaderEffect::setRotateAngle(int value)
{
    rotateAngle = value;
}

int ShaderEffect::getToPosX() const
{
    return toPosX;
}

void ShaderEffect::setToPosX(int value)
{
    toPosX = value;
}

int ShaderEffect::getToPosY() const
{
    return toPosY;
}

void ShaderEffect::setToPosY(int value)
{
    toPosY = value;
}

bool ShaderEffect::getMoveEffect() const
{
    return moveEffect;
}

void ShaderEffect::setMoveEffect(bool value)
{
    moveEffect = value;
}

double ShaderEffect::getToScaleX() const
{
    return toScaleX;
}

void ShaderEffect::setToScaleX(double value)
{
    toScaleX = value;
}

double ShaderEffect::getToScaleY() const
{
    return toScaleY;
}

void ShaderEffect::setToScaleY(double value)
{
    toScaleY = value;
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
void ShaderEffect::setShaderWrapperIndex(int i){
    shaderWrapperIndex=i;
}

int ShaderEffect::getShaderWrapperIndex()
{
    return shaderWrapperIndex;
}
bool ShaderEffect::setUniform(QString name, QVariant value){
    shaderWrapper->setUniform(name,value);
}
bool ShaderEffect::setUniform(QString name, float val1,float val2){
    shaderWrapper->setUniform(name,val1,val2);
}

