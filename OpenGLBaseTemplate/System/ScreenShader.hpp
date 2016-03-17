
#ifndef __ScreenShader_H__
#define __ScreenShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"

class ScreenShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    ScreenShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
    Shader(vertexSourcePath, fragmentSourcePath)
    {
        
    }
    
    void use()
    {
        Shader::use();
        
        //
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _textureColorbuffer);
        glUniform1i(glGetUniformLocation(_shaderProgram, "screenTexture"), 1);
        
        //
        glUniform1f(glGetUniformLocation(_shaderProgram, "near_plane"), _nearPlane);
        glUniform1f(glGetUniformLocation(_shaderProgram, "far_plane"), _farPlane);
    }
    
public:
    
    GLuint  _textureColorbuffer;
    float   _nearPlane;
    float   _farPlane;
};


#endif /* __ScreenShader_H__ */
