// ProvokingVertex flat shader demo
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

attribute vec4 vVertex;
attribute vec4 vColor;

varying vec4 vVaryingColor;

void main(void) 
{
    vVaryingColor = vColor;
    gl_Position = vVertex;
}