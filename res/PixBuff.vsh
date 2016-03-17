// Rectangle Texture (replace) Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

// Incoming per vertex... position and texture coordinate
attribute vec4 vVertex;
attribute vec2 vTexCoord;

uniform mat4 mvpMatrix;

// Texture Coordinate to fragment program
varying vec2 vVaryingTexCoord;


void main(void) 
{
    // Pass on the texture coordinates 
    vVaryingTexCoord = vTexCoord;
    
    // Don't forget to transform the geometry!
    gl_Position = mvpMatrix * vVertex;
}
