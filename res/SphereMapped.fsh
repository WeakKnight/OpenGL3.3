// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

//out vec4 vFragColor;

uniform sampler2D sphereMap;

varying vec2 vVaryingTexCoord;

void main(void)
{
    gl_FragColor = texture2D(sphereMap, vVaryingTexCoord);
}
    