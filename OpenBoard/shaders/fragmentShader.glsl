vec4 getInputColor()
{
  return vec4(vec3(0,1,0), 1.0); // Just a test
}

vec4 toGrayscale(in vec4 color)
{
  float average = (color.r + color.g + color.b) / 3.0;
  return vec4(average, average, average, 1.0);
}

vec4 colorize(in vec4 grayscale, in vec4 color)
{
  return (grayscale * color);
}

void main()
{
  // This is the color you want to apply
  // in the "colorize" step. Shoul ultimately be a uniform var.
  vec4 c = vec4(1.0, 0.0, 1.0, 1.0);

  // The input fragment color.
  // Can come from a texture, a varying or a contant.
  vec4 inputColor = getInputColor();

  // Convert to grayscale first:
  vec4 grayscale = toGrayscale(inputColor);

  // Then "colorize" by simply multiplying the grayscale
  // with the desired color.
  vec4 colorizedOutput = colorize(grayscale, c);

  // Done!
  gl_FragColor = colorizedOutput;
}
