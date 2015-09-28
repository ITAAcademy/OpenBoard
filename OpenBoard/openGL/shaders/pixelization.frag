//pixelize
uniform sampler2D from;
 uniform float animationKey;
 uniform bool reverse;
 uniform int elementSize;
 vec2 resolution=vec2(640,480);
float key;
float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
     if (reverse)key=1-animationKey;
     else key=animationKey;
  float revProgress = (1.0 - key);
  float distFromEdges = min(key, revProgress);
  float squareSize = (elementSize * distFromEdges) + 1.0;

  vec2 p = (floor((gl_FragCoord.xy + squareSize * 0.5) / squareSize) * squareSize) / resolution.xy;
  vec4 fromColor = texture2D(from, p);
  vec4 toColor = vec4(fromColor.rgb,0);
  vec4 testColor = vec4(0.12,0.5,0.3,1);
  gl_FragColor = mix(fromColor, toColor, key);
}
