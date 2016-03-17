#version 330 core

uniform samplerCube cubemap;  // Cubemap纹理采样器
out vec4 color;

in vec3 TexCoords;

void main()
{
    color = texture(cubemap, TexCoords);
}


