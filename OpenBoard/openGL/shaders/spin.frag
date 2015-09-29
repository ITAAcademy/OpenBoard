#ifdef GL_ES
precision highp float;
#endif
uniform sampler2D from;
uniform float animationKey;
uniform vec2 resolution;
uniform bool reverse;
/*
  (C) Sergey Kosarevsky, 2014

  Available under the terms of MIT license
  http://www.linderdaum.com
*/
float key;
vec4 to = vec4(0,0,0,0);
void main(void)
{
    if (reverse)key=1-animationKey;
    else key=animationKey;

        float Radius = 1.0;

        float T = key;

        vec2 UV = gl_FragCoord.xy / resolution.xy;

        UV -= vec2( 0.5, 0.5 );

        float Dist = length(UV);

        if ( Dist < Radius )
        {
                float Percent = (Radius - Dist) / Radius;
                float A = mix( 0.0, 1.0, T/0.5 );
                float Theta = Percent * Percent * A * 8.0 * 3.14159;
                float S = sin( Theta );
                float C = cos( Theta );
                UV = vec2( dot(UV, vec2(C, -S)), dot(UV, vec2(S, C)) );
        }
        UV += vec2( 0.5, 0.5 );

        vec4 C0 = texture2D( from, UV );
        vec4 C1 = to;

        gl_FragColor = mix( C0, C1, T );
}
