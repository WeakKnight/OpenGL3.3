
#include "SkyBoxNode.hpp"
#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemSimpleDraw.hpp"
#include "MatrixStack.hpp"
#include "SystemTexture.hpp"
#include "SkyBoxShader.hpp"

const float radius = 100.0f;

GLfloat skyboxVertices[] = {
    // Positions
    -1.0f * radius,  1.0f * radius, -1.0f * radius,
    -1.0f * radius, -1.0f * radius, -1.0f * radius,
    1.0f * radius, -1.0f * radius, -1.0f * radius,
    1.0f * radius, -1.0f * radius, -1.0f * radius,
    1.0f * radius,  1.0f * radius, -1.0f * radius,
    -1.0f * radius,  1.0f * radius, -1.0f * radius,
    
    -1.0f * radius, -1.0f * radius,  1.0f * radius,
    -1.0f * radius, -1.0f * radius, -1.0f * radius,
    -1.0f * radius,  1.0f * radius, -1.0f * radius,
    -1.0f * radius,  1.0f * radius, -1.0f * radius,
    -1.0f * radius,  1.0f * radius,  1.0f * radius,
    -1.0f * radius, -1.0f * radius,  1.0f * radius,
    
    1.0f * radius, -1.0f * radius, -1.0f * radius,
    1.0f * radius, -1.0f * radius,  1.0f * radius,
    1.0f * radius,  1.0f * radius,  1.0f * radius,
    1.0f * radius,  1.0f * radius,  1.0f * radius,
    1.0f * radius,  1.0f * radius, -1.0f * radius,
    1.0f * radius, -1.0f * radius, -1.0f * radius,
    
    -1.0f * radius,  -1.0f * radius,  1.0f * radius,
    -1.0f * radius,  1.0f * radius,  1.0f * radius,
    1.0f * radius,  1.0f * radius,  1.0f * radius,
    1.0f * radius,  1.0f * radius,  1.0f * radius,
    1.0f * radius, -1.0f * radius,  1.0f * radius,
    -1.0f * radius, -1.0f * radius,  1.0f * radius,
    
    -1.0f * radius,  1.0f * radius, -1.0f * radius,
    1.0f * radius,  1.0f * radius, -1.0f * radius,
    1.0f * radius,  1.0f * radius,  1.0f * radius,
    1.0f * radius,  1.0f * radius,  1.0f * radius,
    -1.0f * radius,  1.0f * radius,  1.0f * radius,
    -1.0f * radius,  1.0f * radius, -1.0f * radius,
    
    -1.0f * radius, -1.0f * radius, -1.0f * radius,
    -1.0f * radius, -1.0f * radius,  1.0f * radius,
    1.0f * radius, -1.0f * radius, -1.0f * radius,
    1.0f * radius, -1.0f * radius, -1.0f * radius,
    -1.0f * radius, -1.0f * radius,  1.0f * radius,
    1.0f * radius, -1.0f * radius,  1.0f * radius
};




//=========================================================================
SkyBoxNode* SkyBoxNode::create(const std::string& right,
                          const std::string& left,
                          const std::string& top,
                          const std::string& bottom,
                          const std::string& back,
                          const std::string& front)
{
    std::vector<std::string> faces;
    faces.push_back(right);
    faces.push_back(left);
    faces.push_back(top);
    faces.push_back(bottom);
    faces.push_back(back);
    faces.push_back(front);
    
    return SkyBoxNode::create(faces);
}
//=========================================================================
SkyBoxNode* SkyBoxNode::create(const std::vector<std::string>& textures)
{
    SkyBoxNode* skyNode = new SkyBoxNode;
    if (!skyNode->init(textures))
    {
        delete skyNode;
        skyNode = nullptr;
        return nullptr;
    }
    
    return skyNode;
}
////=========================================================================
bool SkyBoxNode::init(const std::vector<std::string>& textures)
{
    if (!Node::init())
    {
        return false;
    }
    
    //
    _cubeMapTexture = (CubeMapTexture*)SystemTexture::getInstance().createCubeMapTexture("res/skybox", textures);

    //
    glGenVertexArrays(1, &_skyboxVAO);
    glGenBuffers(1, &_skyboxVBO);
    glBindVertexArray(_skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
    
    //
    _shader = (SkyBoxShader*)SystemShader::getInstance().getShader("SkyBoxShader");
    if (_shader)
    {
        _shader->_texture = _cubeMapTexture;
    }
    
    //
    //this->setScale(2.0f);
   
    //
    return true;
}
//=========================================================================
void SkyBoxNode::renderSelf()
{
    Node::renderSelf();
    
    if (_shader)
    {
        _shader->use();
    }
    
    //
    glBindVertexArray(_skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
//=========================================================================
void SkyBoxNode::cleanUp()
{
    Node::cleanUp();
    
    //
    _cubeMapTexture = nullptr;
    _skyboxVAO = 0;
    _skyboxVBO = 0;
    _shader = nullptr;
}
//=========================================================================
void SkyBoxNode::beforeRenderSelf()
{
    //glDepthMask(GL_FALSE);
    
     glDepthFunc(GL_LEQUAL);
}
//=========================================================================
void SkyBoxNode::afterRenderSelf()
{
    //glDepthMask(GL_TRUE);
    
    glDepthFunc(GL_LESS); // Set depth function back to default

}
//=========================================================================














