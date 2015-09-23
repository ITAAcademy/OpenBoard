 vec2 resolution=vec2(640,480);
 uniform float animationKey;
uniform sampler2D tex0;
float key;
uniform bool reverse;
void main(void)
{
    if (reverse)key=1-animationKey;
    else key=animationKey;
vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    vec2 uv;

    float a = atan(p.y,p.x);
    float r = sqrt(dot(p,p));

    uv.x = r - 0.25*key;
    uv.y = cos(a*2.0 + 2.0*sin(key+7.0*r)) ;


    vec3 col =  (.5+.5*uv.y)*texture2D(tex0,uv).xyz;

    gl_FragColor = vec4(col,1.0);
}
