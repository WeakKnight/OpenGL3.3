#include "Shader.hpp"
//#include "MatrixStack.hpp"
//#include "CameraController.hpp"

//============================================================================================================
Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath, const GLchar * geometryPath):
_shaderProgram(0)
{
    // 1. 从文件路径获得vertex/fragment源码
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try
    {
        // 打开文件
        std::ifstream vShaderFile(vertexPath);
        std::ifstream fShaderFile(fragmentPath);
        
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件缓冲到流
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        // 关闭文件句柄
        vShaderFile.close();
        fShaderFile.close();
        
        // 将流转为GLchar数组
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
        if (geometryPath)
        {
            std::ifstream gShaderFile(geometryPath);
            
            std::stringstream gShaderStream;
            // 读取文件缓冲到流
            gShaderStream << gShaderFile.rdbuf();
            
            // 关闭文件句柄
            gShaderFile.close();
            
            // 将流转为GLchar数组
            geometryCode = gShaderStream.str();
        }
    }
    catch(std::exception e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    // 2. 编译着色器
    GLuint vertex = 0;
    GLuint fragment = 0;
    GLint success = 0;
    GLchar infoLog[512];
    
    //顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    GLchar* vtxStringPtr[1];
    vtxStringPtr[0] = (GLchar*)vertexCode.c_str();
    glShaderSource(vertex, 1, (const GLchar**)vtxStringPtr, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // 对片段着色器进行类似处理
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar* fragStringPtr[1];
    fragStringPtr[0] = (GLchar*)fragmentCode.c_str();
    glShaderSource(fragment, 1, (const GLchar**)fragStringPtr, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    GLuint geometry = 0;
    if (!geometryCode.empty())
    {
        //几何着色器
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        GLchar* geometryStringPtr[1];
        geometryStringPtr[0] = (GLchar*)geometryCode.c_str();
        glShaderSource(geometry, 1, (const GLchar**)geometryStringPtr, NULL);
        glCompileShader(geometry);
        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(geometry, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
    }
    
    // 着色器程序
    this->_shaderProgram = glCreateProgram();
    glAttachShader(this->_shaderProgram, vertex);
    glAttachShader(this->_shaderProgram, fragment);
    
    if (geometry > 0)
    {
        glAttachShader(this->_shaderProgram, geometry);
    }
    
    glLinkProgram(this->_shaderProgram);
    
    // 打印连接错误
    glGetProgramiv(this->_shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(this->_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // 删除着色器
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
}
//============================================================================================================
void Shader::use()
{
    glUseProgram(this->_shaderProgram);
}
//============================================================================================================
//void Shader::setTransform()
//{
//    // Create camera transformations
//    glm::mat4 model = MatrixStack::getMatrix();
//    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    
//    //注意，我们将矩阵向我们要进行移动场景的反向移动
//    glm::mat4 view;
//    view = CameraController ::getViewMatrix();
//    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//    
//    //
//    glm::mat4 projection;
//    projection = CameraController::getProjectMatrix();
//    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//}
//============================================================================================================


