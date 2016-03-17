
#ifndef __SingleColorShader_H__
#define __SingleColorShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"

class SingleColorShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    SingleColorShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
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


#endif /* __SingleColorShader_H__ */
