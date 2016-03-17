
#ifndef __ExplodeShader_H__
#define __ExplodeShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"
#include "App.hpp"
#include "SkyBoxNode.hpp"

class ExplodeShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    ExplodeShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath, const GLchar* geometrySourcePath):
    Shader(vertexSourcePath, fragmentSourcePath, geometrySourcePath)
    {
        
    }
    
    void use()
    {
        Shader::use();
        
        // Add time component to geometry shader in the form of a uniform
        glUniform1f(glGetUniformLocation(_shaderProgram, "time"), glfwGetTime());
        
        //
        setTransform();
    }
    
public:
    
};


#endif /* __GeometryTestShader_H__ */
