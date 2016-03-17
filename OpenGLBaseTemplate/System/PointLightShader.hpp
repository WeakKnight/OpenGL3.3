
#ifndef __PointLightShader_H__
#define __PointLightShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"
#include "Light.hpp"

class PointLightShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    PointLightShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
    Shader(vertexSourcePath, fragmentSourcePath),
    _lightNode(nullptr)
    {
        
    }
    
    void use()
    {
        if (!_lightNode)
        {
            return;
        }
        
        Shader::use();
        
        //
        glUniform3f(glGetUniformLocation(_shaderProgram, "diffuse"),
                    _lightNode->_diffuse.r,
                    _lightNode->_diffuse.g,
                    _lightNode->_diffuse.b);

        
        //
        setTransform();
    }
    
public:
    
    Light* _lightNode;
    
};


#endif /* __TestShader_H__ */
