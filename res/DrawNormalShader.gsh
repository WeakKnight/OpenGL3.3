// ================
// Geometry shader:
// ================
#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.5f;

out vec3 fColor;

void GenerateLine(int index, vec3 color)
{
    fColor = color;

    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0f) * MAGNITUDE;
    EmitVertex();
    
    EndPrimitive();
}

void main()
{
    GenerateLine(0, vec3(1.0f, 0.0f, 0.0f)); // First vertex normal
    GenerateLine(1, vec3(0.0f, 1.0f, 0.0f)); // Second vertex normal
    GenerateLine(2, vec3(0.0f, 0.0f, 1.0f)); // Third vertex normal
}