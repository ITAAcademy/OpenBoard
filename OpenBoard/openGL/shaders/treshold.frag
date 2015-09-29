#ifdef GL_ES
precision highp float;
#endif


// Hardcoded parameters --------

uniform sampler2D from, to;
uniform float animationKey;
uniform bool reverse;
vec2 resolution=vec2(640,480);
float key;

// Transition parameters --------

// default barWidth = 10
 int barWidth=10; // Number of bars

// default amplitude = 2
 float amplitude=2; // 0 = no variation when going down, higher = some elements go much faster

// default noise = 0.1
 float noise=0.1; // 0 = no noise, 1 = super noisy

// default frequency = 1
 float frequency=1; // the bigger the value, the shorter the waves

// The code proper --------

float rand(int num) {
  return fract(mod(float(num) * 67123.313, 12.0) * sin(float(num) * 10.3) * cos(float(num)));
}

float wave(int num) {
  float fn = float(num) * frequency * 0.1  * float(barWidth);
  return cos(fn * 0.5) * cos(fn * 0.13) * sin((fn+10.0) * 0.3) / 2.0 + 0.5;
}

float pos(int num) {
  return noise == 0.0 ? wave(num) : mix(wave(num), rand(num), noise);
}

void main() {
    if (reverse)key=1-animationKey;
    else key=animationKey;
  int bar = int(gl_FragCoord.x) / barWidth;
  float scale = 1.0 + pos(bar) * amplitude;
  float phase = key * scale;
  float posY = gl_FragCoord.y / resolution.y;
  vec2 p;
  vec4 c;
  if (phase + posY < 1.0) {
    p = vec2(gl_FragCoord.x, gl_FragCoord.y + mix(0.0, resolution.y, phase)) / resolution.xy;
    c = texture2D(from, p);
  } else {
    p = gl_FragCoord.xy / resolution.xy;
    c = vec4(c.rgb, 0);
  }

  // Finally, apply the color
  gl_FragColor = c;
}
