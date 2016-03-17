#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#include <GL/glew.h> // 包含glew获取所有的OpenGL必要headers

class Shader
{
public:
   
    // 构造器读取并创建Shader
    Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath, const GLchar * geometryPath = nullptr);
    
    // 使用Program
    virtual void use();
    
    //virtual void setTransform();
    
public:
    
    // 程序ID
    GLuint _shaderProgram;
    
};

#endif