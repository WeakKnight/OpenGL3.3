#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 diffuse;

void main()
{
    color = vec4(diffuse, 1.0f);
    //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    
//    if(gl_FragCoord.x < 400)
//    {
//        color = vec4(diffuse, 1.0f);
//    }
//    else
//    {
//        color = vec4((1 - diffuse), 1.0f);
//    }
}