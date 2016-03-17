
#ifndef __PlaneShader_H__
#define __PlaneShader_H__

#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "SystemShadow.hpp"

class PlaneShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    PlaneShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
    Shader(vertexSourcePath, fragmentSourcePath)
    {
        _texture1 = SystemTexture::getInstance().createTGA2DTexture("res/brick.tga",
                                                                    GL_LINEAR_MIPMAP_LINEAR,
                                                                    GL_LINEAR,
                                                                    GL_REPEAT);
    }
    
    void use()
    {
        Shader::use();
        
        if (_texture1)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _texture1->_textureId);
            glUniform1i(glGetUniformLocation(_shaderProgram, "textureOfPlane"), 0);
        }
        
        //
        if (_texture2)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, SystemShadow::getInstance().depthMap);
            glUniform1i(glGetUniformLocation(_shaderProgram, "textureOfShadow"), 1);
        }
        
        //
        setTransform();
    }
    
public:
    
    Texture* _texture1;
    Texture* _texture2;
};


#endif /* __GeometryTestShader_H__ */
