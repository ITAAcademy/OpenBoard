#ifndef SHADEREFFECT_H
#define SHADEREFFECT_H
#include "shaderprogramwrapper.h"

class ShaderEffect
{
     int startTimeMS = 0;
     int effectTimeHowLong = 0;
    bool reverse = false;
    int count= 0;
    bool anchorToEnd = false;
   ShaderProgramWrapper *shaderWrapper = nullptr;
   int shaderWrapperIndex = -1;


public:
    ShaderEffect(ShaderProgramWrapper *shaderWrp, int shaderIndex=0);
    ShaderEffect(int shaderIndex);
    ShaderEffect();
    ~ShaderEffect();


    ShaderProgramWrapper* getShaderWrapper();
    void setShaderWrapper(ShaderProgramWrapper* shader);
   // static void setUniformAnimationKey(ShaderEffect shaderEffect, float value);
     int getStartTimeMS() const;
    void setStartTimeMS(int value);
     int getEffectTimeHowLong() const;
    void setEffectTimeHowLong(int value);
    bool save(QDataStream &stream);


    int getShaderWrapperIndex();
    bool load(QDataStream &stream);
    bool getReverse() const;
    void setReverse(bool value);
    bool getAnchorToEnd() const;
    void setAnchorToEnd(bool value);

    static QVector<ShaderEffect> creatStartEndEffect( int time );
    static QVector<ShaderEffect> creatEndEffect(int time);
    static QVector<ShaderEffect> creatStartEffect( int time );
    static QVector<ShaderEffect> creatEffectByNum( int num, int time );
    void setShaderWrapperIndex(int i);
    bool setUniform(QString name, QVariant value);
    bool setUniform(QString name, float val1, float val2);
    int getCount() const;
    void setCount(int value);
};

#endif // SHADEREFFECT_H
