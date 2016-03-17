#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 lightSpaceMatrix;

uniform int debugDepthShadow;


void main()
{
    gl_Position = projection * view *  model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = vec2(texCoords.s, 1.0f - texCoords.t);
    
    //深度贴图????
    if (debugDepthShadow > 0)
    {
        gl_Position = lightSpaceMatrix * model * vec4(position, 1.0f);
    }
    
    //vs_out.normal = vec3(projection * vec4(Normal, 1.0));
}