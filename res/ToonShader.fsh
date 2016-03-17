// Cell lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

uniform sampler1D colorTable;
//out vec4 vFragColor;

//smooth in float textureCoordinate;
varying float textureCoordinate;

void main(void)
{
   //gl_FragColor = texture1D(colorTable, textureCoordinate);
    gl_FragColor = texture1D(colorTable, textureCoordinate);
}