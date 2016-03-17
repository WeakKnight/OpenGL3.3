#version 330 core

//
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

//
out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 lightPosition;

//
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//
void main()
{
    ourColor = color;
    
    TexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
    
    Normal = mat3(transpose(inverse(model))) * normal;
    
    mat4 mvp = projection * view * model;
    
    FragPos = vec3(mvp * vec4(position, 1.0f));
    
    lightPosition = vec3(mvp * vec4(0.0f, 2.0f, 0.0f, 1.0f));
    
    gl_Position = mvp * vec4(position, 1.0f);
}








