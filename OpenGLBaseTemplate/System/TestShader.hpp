
#ifndef __TestShader_H__
#define __TestShader_H__

#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "MatrixStack.hpp"
#include "Light.hpp"
#include "SkyBoxNode.hpp"
#include "SystemShadow.hpp"

class TestShader : public Shader
{
public:
    
    // 构造器读取并创建Shader
    TestShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath):
    Shader(vertexSourcePath, fragmentSourcePath),
    _texture1(nullptr),
    _texture2(nullptr),
    _dirLight(nullptr),
    _cubeTexture(nullptr)
    {
        //
        _texture1 = SystemTexture::getInstance().createTGA2DTexture("res/Block5.tga",
                                                                    GL_LINEAR_MIPMAP_LINEAR,
                                                                    GL_LINEAR,
                                                                    GL_REPEAT);
        
        //
        _texture2 = SystemTexture::getInstance().createTGA2DTexture("res/ceiling.tga",
                                                                    GL_LINEAR_MIPMAP_LINEAR,
                                                                    GL_LINEAR,
                                                                    GL_REPEAT);
    }
    
    //
    void use()
    {
        Shader::use();
        
        if (_texture1)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _texture1->_textureId);
        }
        
        if (_texture2)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, _texture2->_textureId);
        }
        
        if (!_cubeTexture)
        {
            auto skyNode = (SkyBoxNode*)App::getRootNode()->getChildNode(10000);
            if (skyNode)
            {
                _cubeTexture = skyNode->getSkyBoxTexture();
            }
            //_cubeTexture = App::getRootNode();
        }
        
        if (_cubeTexture)
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeTexture->_textureId);
            glUniform1i(glGetUniformLocation(_shaderProgram, "skybox"), 2);
        }
        
        //
        glUniform1i(glGetUniformLocation(_shaderProgram, "material.diffuse"), 0);
        glUniform1i(glGetUniformLocation(_shaderProgram, "material.specular"), 1);
        
        //
        GLfloat timer = glfwGetTime();
        glUniform1f(glGetUniformLocation(_shaderProgram, "timer"), timer);
        
        
        // Use cooresponding shader when setting uniforms/drawing objects
        
        GLint viewPosLoc = glGetUniformLocation(_shaderProgram, "viewPos");
        glUniform3f(viewPosLoc,
                    CameraController::getCameraPosition().x,
                    CameraController::getCameraPosition().y,
                    CameraController::getCameraPosition().z);
        
        // Set material properties
        glUniform1f(glGetUniformLocation(_shaderProgram, "material.shininess"), 32.0f);
        // == ==========================
        // Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
        // the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
        // by defining light types as classes and set their values in there, or by using a more efficient uniform approach
        // by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
        // ============================
        
        // Directional light
        if (!_dirLight && !Light::directLights.empty())
        {
            _dirLight = Light::directLights.front();
        }
        
        if (_dirLight)
        {
            glUniform3f(glGetUniformLocation(_shaderProgram, "dirLight.direction"),
                        _dirLight->_direction.x,
                        _dirLight->_direction.y,
                        _dirLight->_direction.z);
            
            glUniform3f(glGetUniformLocation(_shaderProgram, "dirLight.ambient"),
                        _dirLight->_ambient.r,
                        _dirLight->_ambient.g,
                        _dirLight->_ambient.b);
            
            glUniform3f(glGetUniformLocation(_shaderProgram, "dirLight.diffuse"),
                        _dirLight->_diffuse.r,
                        _dirLight->_diffuse.g,
                        _dirLight->_diffuse.b);

            glUniform3f(glGetUniformLocation(_shaderProgram, "dirLight.specular"),
                        _dirLight->_specular.r,
                        _dirLight->_specular.g,
                        _dirLight->_specular.b);
        }
        
        //Point Light
        glUniform1i(glGetUniformLocation(_shaderProgram, "pointlightNum"), (int)Light::pointLights.size());
        
        char buff[255] = {0};
        for (auto index = 0; index < Light::pointLights.size(); ++index)
        {
            auto node = Light::pointLights[index];
            
            //
            sprintf(buff, "pointLights[%d].position", index);
            glUniform3f(glGetUniformLocation(_shaderProgram, buff),
                        node->getPosition().x,
                        node->getPosition().y,
                        node->getPosition().z);
            
            
            sprintf(buff, "pointLights[%d].ambient", index);
            glUniform3f(glGetUniformLocation(_shaderProgram, buff),
                        node->_ambient.r,
                        node->_ambient.g,
                        node->_ambient.b);
            
            sprintf(buff, "pointLights[%d].diffuse", index);
            glUniform3f(glGetUniformLocation(_shaderProgram, buff),
                        node->_diffuse.r,
                        node->_diffuse.g,
                        node->_diffuse.b);
            
            sprintf(buff, "pointLights[%d].specular", index);
            glUniform3f(glGetUniformLocation(_shaderProgram, buff),
                        node->_specular.r,
                        node->_specular.g,
                        node->_specular.b);
            
            sprintf(buff, "pointLights[%d].constant", index);
            glUniform1f(glGetUniformLocation(_shaderProgram, buff), node->_constant);
            
            sprintf(buff, "pointLights[%d].linear", index);
            glUniform1f(glGetUniformLocation(_shaderProgram, buff), node->_linear);
            
            sprintf(buff, "pointLights[%d].quadratic", index);
            glUniform1f(glGetUniformLocation(_shaderProgram, buff), node->_quadratic);
        }
        
        //
        glUniform1i(glGetUniformLocation(_shaderProgram, "useCameraSpotLight"), (int)(CameraController::useCameraSpotLight ? 1 : 0));
        if (CameraController::useCameraSpotLight)
        {
            // SpotLight
            glUniform3f(glGetUniformLocation(_shaderProgram, "spotLight.position"),
                        CameraController::getCameraPosition().x,
                        CameraController::getCameraPosition().y,
                        CameraController::getCameraPosition().z);
            
            glUniform3f(glGetUniformLocation(_shaderProgram, "spotLight.direction"),
                        CameraController::getCameraDirection().x,
                        CameraController::getCameraDirection().y,
                        CameraController::getCameraDirection().z);
            
            glUniform3f(glGetUniformLocation(_shaderProgram, "spotLight.ambient"),
                        CameraController::ambient.r,
                        CameraController::ambient.g,
                        CameraController::ambient.b);
            
            glUniform3f(glGetUniformLocation(_shaderProgram, "spotLight.diffuse"),
                        CameraController::diffuse.r,
                        CameraController::diffuse.g,
                        CameraController::diffuse.b);
            
            glUniform3f(glGetUniformLocation(_shaderProgram, "spotLight.specular"),
                        CameraController::specular.r,
                        CameraController::specular.g,
                        CameraController::specular.b);

            //
            glUniform1f(glGetUniformLocation(_shaderProgram, "spotLight.constant"), CameraController::constant);
            glUniform1f(glGetUniformLocation(_shaderProgram, "spotLight.linear"), CameraController::linear);
            glUniform1f(glGetUniformLocation(_shaderProgram, "spotLight.quadratic"), CameraController::quadratic);
            glUniform1f(glGetUniformLocation(_shaderProgram, "spotLight.cutOff"), glm::cos(glm::radians(CameraController::cutOff)));
            glUniform1f(glGetUniformLocation(_shaderProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(CameraController::outerCutOff)));
        }
        
        //
        glm::mat4 model = MatrixStack::getMatrix();
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        
        //
        glUniformBlockBinding(_shaderProgram, glGetUniformBlockIndex(_shaderProgram, "Matrices"), 0);
        
        //
        glm::mat4 lightSpaceMatrix = SystemShadow::getInstance().lightSpaceMatrix;
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
        
        //
        glUniform1i(glGetUniformLocation(_shaderProgram, "debugDepthShadow"), SystemShadow::getInstance().debugDepthShadow ? 1 : 0);
    }
    
public:
    
    Texture*    _texture1;
    Texture*    _texture2;
    Light*      _dirLight;
    Texture*    _cubeTexture;
};


#endif /* __TestShader_H__ */
