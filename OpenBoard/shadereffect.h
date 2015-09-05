#ifndef SHADEREFFECT_H
#define SHADEREFFECT_H
#include "shaderprogramwrapper.h"

class ShaderEffect
{
     int startTimeMS = 0;
     int effectTimeHowLong = 0;
    bool reverse = false;
    bool anchorToEnd = false;
   ShaderProgramWrapper *shaderWrapper = nullptr;
   int shaderWrapperIndex = -1;


public:
    ShaderEffect(ShaderProgramWrapper *shaderWrp, int shaderIndex);
    ShaderEffect(int shaderIndex);
    ShaderEffect();
    ~ShaderEffect();


    ShaderProgramWrapper* getShaderWrapper();
    void setShaderWrapper(ShaderProgramWrapper* shader);
    static void setUniformAnimationKey(OGLWidget *oglWidget, ShaderEffect shaderEffect, float value);
    static void setUniformResolution(OGLWidget *oglWidget, ShaderEffect shaderEffect, float width, float height);
    static void setUniformReverse(OGLWidget *oglWidget, ShaderEffect shaderEffect,bool val);
     int getStartTimeMS() const;
    void setStartTimeMS(unsigned int value);
     int getEffectTimeHowLong() const;
    void setEffectTimeHowLong(unsigned int value);
    bool save(QDataStream &stream);


    int getShaderWrapperIndex();
    bool load(QDataStream &stream);
    bool getReverse() const;
    void setReverse(bool value);
    bool getAnchorToEnd() const;
    void setAnchorToEnd(bool value);
};

#endif // SHADEREFFECT_H
