
#ifndef __SkyBoxShader_H__
#define __SkyBoxShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"


class SkyBoxShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    SkyBoxShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
    Shader(vertexSourcePath, fragmentSourcePath),
    _texture(nullptr)
    {
        
    }
    
    void use()
    {
        Shader::use();
        
        if (_texture)
        {
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(glGetUniformLocation(_shaderProgram, "skybox"), 0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, _texture->_textureId);
        }
        
        //
        glm::mat4 view = glm::mat4(glm::mat3(CameraController::getViewMatrix()));
        glm::mat4 projection = CameraController::getProjectMatrix();
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        
    }
    
public:
    
    CubeMapTexture* _texture;
    
};


#endif /* __SkyBoxShader_H__ */
