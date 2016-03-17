
#ifndef __DepthTestShader_H__
#define __DepthTestShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"

class DepthTestShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    DepthTestShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
    Shader(vertexSourcePath, fragmentSourcePath)
    {
        
    }
    
    void use()
    {
        Shader::use();
        setTransform();
    }
    
public:
    
};


#endif /* __TestShader_H__ */
