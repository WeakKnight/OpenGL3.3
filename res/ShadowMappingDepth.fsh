#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D textureOfPlane;

void main()
{
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    color = texture(textureOfPlane, TexCoords);
}