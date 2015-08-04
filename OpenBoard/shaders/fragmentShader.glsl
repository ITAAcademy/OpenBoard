varying vec3 normal;
varying vec3 fNormal;
uniform vec4 color;
uniform sampler2D s_texture;
//vec4 getInputColor()
//{
 // return color; // Just a test
//}

vec4 toGrayscale(in vec4 color)
{
  float average = (color.r + color.g + color.b) / 3.0;
  return vec4(average, average, average, 1.0);
}

vec4 colorize(in vec4 grayscale, in vec4 color)
{
// return vec4((grayscale.r + color.r)/2,(grayscale.g+color.g)/2,(grayscale.b+color.b)/2,(grayscale.a+color.a)/2);
    return grayscale+color;
}

void main()
{
  // This is the color you want to apply
  // in the "colorize" step. Shoul ultimately be a uniform var.
//  vec4 c =color;

  // The input fragment color.
  // Can come from a texture, a varying or a contant.
 // vec4 inputColor = getInputColor();

  // Convert to grayscale first:
  vec4 grayscale = toGrayscale(gl_Color);

  // Then "colorize" by simply multiplying the grayscale
  // with the desired color.
  vec4 colorizedOutput = colorize(grayscale, color);

  // Done!
 // gl_FragColor = colorizedOutput;
   gl_FragColor = texture2D( s_texture, vec3(gl_MultiTexCoord0) );
}
