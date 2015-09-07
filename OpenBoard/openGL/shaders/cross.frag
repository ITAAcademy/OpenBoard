#ifdef GL_ES
precision mediump float;
#endif
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float crossSize;
uniform sampler2D textureSampler;


void main( void ) {
vec4 col =  texture2D(textureSampler,
vec2(gl_TexCoord[0]));
        vec2 position = ( gl_FragCoord.xy / resolution.xy ) + mouse / 4.0;
        float pixelWidth = 5;
        float pixelHeight =5;

        float colorID2 = clamp(mod(gl_FragCoord.y,pixelHeight)/1.0,0.0,1.5);
        float colorID = clamp(mod(gl_FragCoord.x,pixelWidth)/1.0,0.0,1.5);
        //vec3 color = vec3(position.x);
        vec3 color = vec3(colorID*colorID2);
        gl_FragColor =vec4(col.rgb*color.rgb/2,col.a);
}
