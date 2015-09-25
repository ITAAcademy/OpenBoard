//pixelize
uniform sampler2D from;
 uniform float animationKey;
 uniform int count;
 vec2 resolution=vec2(640,480);
uniform bool reverse;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
float key;
void main() {
    if (reverse)key=1-animationKey;
    else key=animationKey;
    vec2 p = gl_FragCoord.xy / resolution.xy;

      float x = key;

      bool nextImage = distance(fract(p * count), vec2(0.5, 0.5)) < x;
      if(nextImage)
        gl_FragColor = vec4(0,0,0,0);
      else
        gl_FragColor = texture2D(from, p);
}
