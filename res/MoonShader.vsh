// MoonShader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

attribute vec4 vVertex;
attribute vec4 vTexCoords;

uniform mat4 mvpMatrix;
uniform float fTime;

varying vec3 vMoonCoords;

void main(void) 
{
    vMoonCoords.st = vTexCoords.st;
    vMoonCoords.p = fTime;

    gl_Position = mvpMatrix * vVertex;
}