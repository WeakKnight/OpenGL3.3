// Reflection Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

// Incoming per vertex... position and normal
attribute vec4 vVertex;
attribute vec3 vNormal;
attribute vec2 vTexCoords;

uniform mat4   mvpMatrix;
uniform mat4   mvMatrix;
uniform mat3   normalMatrix;
uniform mat4   mInverseCamera;

// Texture coordinate to fragment program
varying vec3 vVaryingTexCoord;
varying vec2 vTarnishCoords;

void main(void) 
{
    // Normal in Eye Space
    vec3 vEyeNormal = normalMatrix * vNormal;
    
    // Vertex position in Eye Space
    vec4 vVert4 = mvMatrix * vVertex;
    vec3 vEyeVertex = normalize(vVert4.xyz / vVert4.w);
    
    // Get reflected vector
    vec4 vCoords = vec4(reflect(vEyeVertex, vEyeNormal), 1.0);
   
    // Rotate by flipped camera
    vCoords = mInverseCamera * vCoords;
    vVaryingTexCoord.xyz = normalize(vCoords.xyz);
	
    vTarnishCoords = vTexCoords.st;

    // Don't forget to transform the geometry!
    gl_Position = mvpMatrix * vVertex;
}
