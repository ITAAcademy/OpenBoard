
//pixelize
uniform sampler2D from;
uniform float animationKey;
uniform bool reverse;
vec4 to=vec4(0,0,0,0);
vec2 resolution=vec2(640,480);
float key;
ivec2 size=ivec2(10,10);
float smoothness=0.05;
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    if (reverse)key=1.0-animationKey;
    else key=animationKey;
    vec2 p = gl_FragCoord.xy / resolution.xy;
    float r = rand(floor(vec2(size) * p));
    float m = smoothstep(0.0, -smoothness, r - (key * (1.0 + smoothness)));
    gl_FragColor = mix(texture2D(from, p), to, m);
}
