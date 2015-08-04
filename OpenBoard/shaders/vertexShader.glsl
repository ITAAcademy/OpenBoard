uniform vec3 normal;
varying vec3 fNormal;
uniform mat3 normalMatrix;

attribute vec2 a_texCoord;
void main()
{
    // Transforming The Vertex
    fNormal = normalize(normalMatrix * normal);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
