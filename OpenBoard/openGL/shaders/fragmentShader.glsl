//#version 120
//precision highp float;
varying vec2 vUV;
uniform sampler2D textureSampler;
uniform vec4 toColor;
uniform float radial_blur=0.15;   // blur factor
//uniform int bloorStep;
/*vec4 smoothing(vec2 tc,sampler2D u_texture,vec2 u_Scale);

 const vec2 gaussFilter[7] =
 {
        vec2(-3.0,	0.015625),
        vec2(-2.0,	0.09375),
        vec2(-1.0,	0.234375),
        vec2(0.0,	0.3125),
        vec2(1.0,	0.234375),
        vec2(2.0,	0.09375),
        vec2(3.0,	0.015625)
};*/
vec2 Center=vec2(0.5, 0.5 ); ///center of the screen (could be any place)
float BlurStart = 0.1f; /// blur offset
//float BlurWidth = 0.1; ///how big it should be
//float nsamples = 10;

 float BlurWidth=0.1;
vec4 PS_RadialBlur(vec2 UV );
void main(void) {
    vec4 resultColor;
    //vec4 col = texture2D(textureSampler, gl_TexCoord[0].st);
    vec4 col = PS_RadialBlur(vUV);
    //vec2 step = vec2(0,0.001*bloorStep);
    //vec4 col = smoothing(gl_TexCoord[0].st,textureSampler,step);// 1/width
    float max = col.r;
    if (col.g>max)max=col.g;
    if (col.b>max)max=col.b;
   col=vec4(max,max,max,col.a);
    if (max==0)// && col.a==1)
    {
        resultColor=vec4(toColor.rgb,col.a);
    }
    else
    resultColor = col*toColor;

    gl_FragColor=resultColor;
}
vec4 PS_RadialBlur(vec2 UV )
{
    vec2 TexCoord = vec2(gl_TexCoord[0]);
 float radial_bright=1;
      vec4 SumColor = vec4(0.0, 0.0, 0.0, 0.0);
      TexCoord += BlurWidth * 0.5 - Center;

      for (int i = 0; i < 12; i++)
      {
        float scale = 1.0 - radial_blur * (float(i) / 11.0);
        SumColor += texture2D(textureSampler, TexCoord * scale + Center);
      }

     return SumColor / 12.0 * radial_bright;
}

/*vec4 smoothing(vec2 tc,sampler2D u_texture,vec2 u_Scale){
    vec4 color = vec4(0.0);
            for( int i = 0; i < 7; i++ )
            {
                    color += texture2D( u_texture, vec2( tc.x+gaussFilter[i].x*u_Scale.x, tc.y+gaussFilter[i].x*u_Scale.y ) )*gaussFilter[i].y;
            }

            return color;
}*/
