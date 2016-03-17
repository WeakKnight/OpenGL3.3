
#ifndef __ReflectionShader_H__
#define __ReflectionShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"
#include "App.hpp"
#include "SkyBoxNode.hpp"

class ReflectionShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    ReflectionShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
    Shader(vertexSourcePath, fragmentSourcePath),
    _texture(nullptr)
    {
        
    }
    
    void use()
    {
        Shader::use();
        
        if (!_texture)
        {
            auto skyNode = (SkyBoxNode*)App::getRootNode()->getChildNode(10000);
            if (skyNode)
            {
                _texture = skyNode->getSkyBoxTexture();
            }            
        }
        
        if (_texture)
        {
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(glGetUniformLocation(_shaderProgram, "skybox"), 0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, _texture->_textureId);
        }

        //
        glUniform3f(glGetUniformLocation(_shaderProgram, "cameraPos"),
                    CameraController::getCameraPosition().x,
                    CameraController::getCameraPosition().y,
                    CameraController::getCameraPosition().z);
        
        //
        setTransform();
    }
    
public:
    
    CubeMapTexture* _texture;
    
};


#endif /* __ReflectionShader_H__ */
