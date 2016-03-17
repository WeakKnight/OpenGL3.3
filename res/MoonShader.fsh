// MoonShader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

// Another NVidia Driver non-conformance bug
// You should not have to put this here for a 3.3 driver.
#extension GL_EXT_gpu_shader4: enable

//out vec4 vFragColor;

uniform sampler2DArray moonImage;

varying vec3 vMoonCoords;

void main(void)
{
   gl_FragColor = texture2DArray(moonImage, vMoonCoords.stp);
}