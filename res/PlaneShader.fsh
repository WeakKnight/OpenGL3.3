#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D textureOfPlane;
uniform sampler2D textureOfShadow;

void main()
{
    //color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    color = texture(textureOfPlane, TexCoords);
    
    //
    //vec4 shadowColor = texture(textureOfShadow, vec2(TexCoords[0], 1.0f - TexCoords[1]));
    //shadowColor = texture(textureOfShadow, TexCoords);

    //color = shadowColor;
}