#ifndef SHADEREFFECT_H
#define SHADEREFFECT_H
#include "shaderprogramwrapper.h"

class ShaderEffect
{
    unsigned int startTimeMS = 0;
    unsigned int effectTimeHowLong = 0;
    bool reverse = false;
   ShaderProgramWrapper *shaderWrapper = nullptr;
   int shaderWrapperIndex = -1;

public:
    ShaderEffect(ShaderProgramWrapper *shaderWrp, int shaderIndex);
    ShaderEffect();
    ~ShaderEffect();


    ShaderProgramWrapper* getShaderWrapper();
    void setShaderWrapper(ShaderProgramWrapper* shader);
    static void setUniformAnimationKey(OGLWidget *oglWidget, ShaderEffect shaderEffect, float value);
    static void setUniformResolution(OGLWidget *oglWidget, ShaderEffect shaderEffect, float width, float height);
    static void setUniformReverse(OGLWidget *oglWidget, ShaderEffect shaderEffect,bool val);
    unsigned int getStartTimeMS() const;
    void setStartTimeMS(unsigned int value);
    unsigned int getEffectTimeHowLong() const;
    void setEffectTimeHowLong(unsigned int value);
    bool save(QDataStream &stream);


    int getShaderWrapperIndex();
    bool load(QDataStream &stream);
    bool getReverse() const;
    void setReverse(bool value);
};

#endif // SHADEREFFECT_H
