// ADS Point lighting Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

// Incoming per vertex... position and normal
attribute vec4 vVertex;
attribute vec3 vNormal;
attribute vec2 vTexCoords0;


uniform mat4   mvpMatrix;
uniform mat4   mvMatrix;
uniform mat3   normalMatrix;
uniform vec3   vLightPosition;

// Color to fragment program
varying vec3 vVaryingNormal;
varying vec3 vVaryingLightDir;
varying vec2 vVaryingTexCoord;


void main(void) 
{
    // Pass on the texture coordinates
    vVaryingTexCoord = vTexCoords0;
    
    // Get surface normal in eye coordinates
    vVaryingNormal = normalMatrix * vNormal;
    
    // Get vertex position in eye coordinates
    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
    
    // Get vector to light source
    vVaryingLightDir = normalize(vLightPosition - vPosition3);
    
    
    // Don't forget to transform the geometry!
    gl_Position = mvpMatrix * vVertex;
}
