 vec2 resolution=vec2(640,480);
 uniform float animationKey;
uniform sampler2D tex0;

void main(void)
{

vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    vec2 uv;

    float a = atan(p.y,p.x);
    float r = sqrt(dot(p,p));

    uv.x = r - 0.25*animationKey;
    uv.y = cos(a*2.0 + 2.0*sin(animationKey+7.0*r)) ;


    vec3 col =  (.5+.5*uv.y)*texture2D(tex0,uv).xyz;

    gl_FragColor = vec4(col,1.0);
}