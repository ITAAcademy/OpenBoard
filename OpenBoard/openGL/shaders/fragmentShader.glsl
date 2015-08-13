#version 120
//precision highp float;
varying vec2 vUV;
uniform sampler2D textureSampler;
uniform vec4 toColor;
uniform int bloorStep;
vec4 smoothing(vec2 tc,sampler2D u_texture,vec2 u_Scale);

  vec2 gaussFilter[7] = vec2[]
 (
        vec2(-3.0,	0.015625),
        vec2(-2.0,	0.09375),
        vec2(-1.0,	0.234375),
        vec2(0.0,	0.3125),
        vec2(1.0,	0.234375),
        vec2(2.0,	0.09375),
        vec2(3.0,	0.015625)
);
void main(void) {
    vec4 resultColor;
    //vec4 col = texture2D(textureSampler, gl_TexCoord[0].st);
    vec2 step = vec2(0,0.1*bloorStep);
    vec4 col = smoothing(gl_TexCoord[0].st,textureSampler,step);// 1/width
    float max = col.r;
    if (col.g>max)max=col.g;
    if (col.b>max)max=col.b;
   col=vec4(max,max,max,col.a);
    if (max==0 && col.a!=0)resultColor=toColor;
    else
    resultColor = col*toColor;

    gl_FragColor=resultColor;
}
vec4 smoothing(vec2 tc,sampler2D u_texture,vec2 u_Scale){
    /*vec4 color = vec4(0.0);
            for( int i = 0; i < 7; i++ )
            {
                    color += texture2D( u_texture, vec2( tc.x+gaussFilter[i].x*u_Scale.x, tc.y+gaussFilter[i].x*u_Scale.y ) )*gaussFilter[i].y;
            }

            return color;*/

    vec4 sum = vec4(0.0); //результирующий цвет

    vec2 startDir = -0.5*u_Scale*float(7-1); //вычисляем начальную точку размытия
    for (int i=0; i<7; i++) //проходимся по всем коэффициентам
    {
        sum += texture2D(u_texture, tc + startDir + u_Scale*float(i))*gaussFilter[i].y;
        sum.a =  gaussFilter[i].y;
    }
    return sum;
}
