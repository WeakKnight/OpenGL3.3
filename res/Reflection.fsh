// Reflection Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

//out vec4 vFragColor;

uniform samplerCube cubeMap;
uniform sampler2D   tarnishMap;

varying vec3 vVaryingTexCoord;
varying vec2 vTarnishCoords;

void main(void)
{
    gl_FragColor = textureCube(cubeMap, vVaryingTexCoord.stp);
    gl_FragColor *= texture2D(tarnishMap, vTarnishCoords);
}
    