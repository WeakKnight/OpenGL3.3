// SpaceFlight Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

// Incoming per vertex... position and normal
attribute vec4 vVertex;
attribute vec4 vColor;

uniform mat4   mvpMatrix;
uniform float  timeStamp;

varying vec4 vStarColor;

void main(void) 
{
    vec4 vNewVertex = vVertex;
    vStarColor = vColor;
    
    // Offset by running time, makes it move closer
    vNewVertex.z += timeStamp;
    
    // If out of range, adjust
    if(vNewVertex.z > -1.0)
    {
        vNewVertex.z -= 999.0;
    }
    
    //
    gl_PointSize = 30.0 + (vNewVertex.z / sqrt(-vNewVertex.z));
    
    // If they are very small, fade them up
    if(gl_PointSize < 4.0)
    {
        vStarColor = smoothstep(0.0, 4.0, gl_PointSize) * vStarColor;
    }
    
    // Don't forget to transform the geometry!
    gl_Position = mvpMatrix * vNewVertex;
}
