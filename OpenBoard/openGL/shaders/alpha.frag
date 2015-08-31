
uniform sampler2D textureSampler;
uniform float animationKey;
void main(void)
{
    vec4 col = texture2D(textureSampler, vec2(gl_TexCoord[0]));
    float alpha = animationKey;
    if (alpha>col.a)alpha=col.a;
    gl_FragColor = vec4(col.rgb,alpha);
}

