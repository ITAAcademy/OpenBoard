#ifndef SHADEREFFECT_H
#define SHADEREFFECT_H
#include "shaderprogramwrapper.h"

class ShaderEffect
{
    unsigned int startTimeMS = 0;
    unsigned int effectTimeHowLong = 0;
   ShaderProgramWrapper *shaderWrapper = nullptr;

public:
    ShaderEffect(ShaderProgramWrapper *shaderWrp);
    ShaderEffect();
    ~ShaderEffect();
    ShaderProgramWrapper* getShaderWrapper();
    static void setUniformAnimationKey(OGLWidget *oglWidget, ShaderEffect shaderEffect, float value);
};

#endif // SHADEREFFECT_H
