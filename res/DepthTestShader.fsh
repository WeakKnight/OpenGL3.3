#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

float LinearizeDepth(float depth)
{
    float near = 0.1f;
    float far = 100.0f;
    float z = depth * 2.0f - 1.0f; // Back to NDC
    return (2.0f * near) / (far + near - z * (far - near));
}

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z);
    color = vec4(vec3(depth * 10.0f), 1.0f);
}