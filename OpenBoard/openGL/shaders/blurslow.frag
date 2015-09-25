// goto https://glsl.io/transition/206b96128ad6085f9911 and paste
#ifdef GL_ES
precision highp float;
#endif

#define QUALITY 32
#define N 20

// General parameters
uniform sampler2D from;
uniform sampler2D to;
uniform float animationKey;
uniform bool reverse;
  float key;
 vec2 resolution=vec2(640,480);

// Custom parameters
uniform float size;

const float GOLDEN_ANGLE = 2.399963229728653; // PI * (3.0 - sqrt(5.0))

vec4 blur(sampler2D t, vec2 c, float radius) {
  vec4 sum = vec4(0.0);
  float q = float(QUALITY);
  // Using a "spiral" to propagate points.
  for (int i=0; i<QUALITY; ++i) {
    float fi = float(i);
    float a = fi * GOLDEN_ANGLE;
    float r = sqrt(fi / q) * radius;
    vec2 p = c + r * vec2(cos(a), sin(a));
    sum += texture2D(t, p);
  }
  return sum / q;
}

vec4 blur2(sampler2D t, vec2 p)
{
  vec4 sum = vec4(0.0);
  int count = 0;
  vec2 delta = vec2(1.0, 1.0) / resolution.xy;
  for (int i=-N; i < N; i++)
  {
    for (int j = -N; j < N; j++)
    {
      vec2 uv;
      uv.x = p.x + float(i) * delta.x;
      uv.y = p.y + float(j) * delta.y;
      sum += texture2D(t, uv);
      count ++;
    }
  }
  return sum / float(count);
}

void main()
{
    if (reverse)key=1.0-animationKey;
    else key=animationKey;
  vec2 p = gl_FragCoord.xy / resolution.xy;
  gl_FragColor = blur(from, p, 0.01);
  //gl_FragColor = blur2(from, p);
}
