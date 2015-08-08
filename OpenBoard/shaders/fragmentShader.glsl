precision highp float;
varying vec2 vUV;
uniform sampler2D textureSampler;
uniform vec4 toColor;

void main(void) {
    vec4 col = texture2D(textureSampler, gl_TexCoord[0].st);
    float max = col.r;
    if (col.g>max)max=col.g;
    if (col.b>max)max=col.b;
    col=vec4(max,max,max,col.a);
    if (max==0)gl_FragColor=toColor;
    else
    gl_FragColor = col*toColor;
}
