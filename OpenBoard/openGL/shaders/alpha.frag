
uniform sampler2D textureSampler;
uniform float animationKey;
uniform bool reverse;
void main(void)
{
    vec4 col = texture2D(textureSampler, vec2(gl_TexCoord[0]));
    float alpha = animationKey;
    if (alpha>col.a)alpha=col.a;
    if (reverse)alpha=1.0-alpha;
    gl_FragColor = vec4(col.rgb,alpha);
}

