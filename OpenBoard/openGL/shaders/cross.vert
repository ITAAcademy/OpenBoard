attribute vec4 qt_Vertex;
attribute vec4 qt_MultiTexCoord0;

void main(void)
{
    gl_Position = gl_ModelViewProjectionMatrix * qt_Vertex;
    gl_TexCoord[0]=gl_MultiTexCoord0;
}

