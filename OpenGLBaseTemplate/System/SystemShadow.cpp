
#include "SystemShadow.hpp"
#include "SystemWindow.hpp"
#include "SystemShader.hpp"
#include "ScreenShader.hpp"
#include "App.hpp"
#include "Node.hpp"


const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
GLfloat quadVertices1[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // Positions   // TexCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    
    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

//====================================================================================================
SystemShadow::SystemShadow()
{
    destroy();
}
//====================================================================================================
SystemShadow::~SystemShadow()
{
    destroy();
}
//====================================================================================================
void SystemShadow::destroy()
{
    debugDepthShadow = false;
}
//====================================================================================================
void SystemShadow::build()
{
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //
    GLfloat near_plane = 1.0f, far_plane = 7.5f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0));
    lightSpaceMatrix = lightProjection * lightView;
}
//====================================================================================================
void SystemShadow::useBeforeDrawScene()
{

}
//====================================================================================================
void SystemShadow::useAfterDrawScene()
{

}
//====================================================================================================
void SystemShadow::setUseFrameBuffer(bool setting)
{
    
}
//====================================================================================================
void SystemShadow::generateShadowMap()
{
    //
    debugDepthShadow = true;
    
    //
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    //glClear(GL_DEPTH_BUFFER_BIT);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //
    App::getRootNode()->render(0);
    
    //RenderScene(simpleDepthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    debugDepthShadow = false;
}
//====================================================================================================














