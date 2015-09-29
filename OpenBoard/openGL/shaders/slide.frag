// Converted from https://github.com/rectalogic/rendermix-basic-effects/blob/master/assets/com/rendermix/Slide/Slide.frag

#ifdef GL_ES
precision highp float;
#endif
uniform sampler2D from;
uniform float animationKey;
uniform vec2 resolution;
uniform bool reverse;

float key;
// Slide Down: translateX = 0, translateY = -1
// Slide Left: translateX = -1, translateY = 0
// Slide Right: translateX = 1, translateY = 0
// Slide Up: translateX = 0, translateY = 1
 float translateX=1;
 float translateY=0;

void main() {
    if (reverse)key=1-animationKey;
    else key=animationKey;
    vec2 texCoord = gl_FragCoord.xy / resolution.xy;
    float x = key * translateX;
    float y = key * translateY;

    if (x >= 0.0 && y >= 0.0) {
        if (texCoord.x >= x && texCoord.y >= y) {
            gl_FragColor = texture2D(from, texCoord - vec2(x, y));
        }
        else {
            vec2 uv;
            if (x > 0.0)
                uv = vec2(x - 1.0, y);
            else if (y > 0.0)
                uv = vec2(x, y - 1.0);
           // gl_FragColor = texture2D(to, texCoord - uv);
            gl_FragColor = vec4(0,0,0,0);
        }
    }
    else if (x <= 0.0 && y <= 0.0) {
        if (texCoord.x <= (1.0 + x) && texCoord.y <= (1.0 + y))
            gl_FragColor = texture2D(from, texCoord - vec2(x, y));
        else {
            vec2 uv;
            if (x < 0.0)
                uv = vec2(x + 1.0, y);
            else if (y < 0.0)
                uv = vec2(x, y + 1.0);
            //gl_FragColor = texture2D(to, texCoord - uv);
             gl_FragColor = vec4(0,0,0,0);
        }
    }
    else
        gl_FragColor = vec4(0.0);
}
