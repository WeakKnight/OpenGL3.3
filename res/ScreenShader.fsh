#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

const float offset = 1.0f/300.0f;

vec2 offsets[9] = vec2[](
                         vec2(-offset, offset),  // top-left
                         vec2(0.0f,    offset),  // top-center
                         vec2(offset,  offset),  // top-right
                         vec2(-offset, 0.0f),    // center-left
                         vec2(0.0f,    0.0f),    // center-center
                         vec2(offset,  0.0f),    // center-right
                         vec2(-offset, -offset), // bottom-left
                         vec2(0.0f,    -offset), // bottom-center
                         vec2(offset,  -offset)  // bottom-right
                         );

float kernel[9] = float[](
                          
                          //锐化
//                        -1.0f, -1.0f, -1.0f,
//                        -1.0f,  9.0f, -1.0f,
//                        -1.0f, -1.0f, -1.0f
                          
                          //blur
                        1.0 / 16, 2.0 / 16, 1.0 / 16,
                        2.0 / 16, 4.0 / 16, 2.0 / 16,
                        1.0 / 16, 2.0 / 16, 1.0 / 16
                          
                          //边缘检测
//                          1.0f, 1.0f, 1.0f,
//                          1.0f, -8.0f, 1.0f,
//                          1.0f, 1.0f, 1.0f
                          );

uniform float near_plane;
uniform float far_plane;

void main()
{
    const int tag = 0;
    
    //
    color = texture(screenTexture, TexCoords);
    
    //
    if (tag == 0)
    {
        
    }
    else if (tag == 1)
    {
        //叠色
        color *= vec4(1.0f, 1.5f, 0.1f, 1.0f);
    }
    else if (tag == 2)
    {
        //反色
        color = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
    }
    else if (tag == 3)
    {
        //黑白
        color = texture(screenTexture, TexCoords);
        float average = (color.r + color.g + color.b) / 3.0;
        color = vec4(average, average, average, 1.0);
    }
    else if (tag == 4)
    {
        //黑白
        color = texture(screenTexture, TexCoords);
        float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
        color = vec4(average, average, average, 1.0);
    }
    else if (tag == 5)
    {
        //。。。。
        vec3 sampleTex[9];
        for(int i = 0; i < 9; i++)
        {
            sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
        }
        
        vec3 col = vec3(0.0f, 0.0f, 0.0f);
        for(int i = 0; i < 9; i++)
        {
            col += sampleTex[i] * kernel[i];
        }
        
        color = vec4(col, 1.0);
    }
}












