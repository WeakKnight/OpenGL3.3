
#ifndef __DrawNormalShader_H__
#define __DrawNormalShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"
#include "App.hpp"
#include "SkyBoxNode.hpp"

class DrawNormalShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    DrawNormalShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath, const GLchar* geometrySourcePath):
    Shader(vertexSourcePath, fragmentSourcePath, geometrySourcePath)
    {
        
    }
    
    void use()
    {
        Shader::use();
        setTransform();
    }
    
public:
    
};


#endif /* __GeometryTestShader_H__ */
