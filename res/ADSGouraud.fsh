// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

//out vec4 vFragColor;
varying vec4 vVaryingColor;

void main(void)
{
   gl_FragColor = vVaryingColor;
}