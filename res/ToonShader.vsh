// Cell lighting Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

// Incoming per vertex... position and normal
attribute vec4 vVertex;
attribute vec3 vNormal;


//smooth out float textureCoordinate;
varying float textureCoordinate;

uniform vec3	vLightPosition;
uniform mat4	mvpMatrix;
uniform mat4	mvMatrix;
uniform mat3	normalMatrix;


void main(void) 
{
    // Get surface normal in eye coordinates
    vec3 vEyeNormal = normalMatrix * vNormal;

    // Get vertex position in eye coordinates
    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

    // Get vector to light source
    vec3 vLightDir = normalize(vLightPosition - vPosition3);

    // Dot product gives us diffuse intensity
    textureCoordinate = max(0.0, dot(vEyeNormal, vLightDir));

    // Don't forget to transform the geometry!
    gl_Position = mvpMatrix * vVertex;
}