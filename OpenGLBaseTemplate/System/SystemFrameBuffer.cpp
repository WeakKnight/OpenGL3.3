
#include "SystemFrameBuffer.hpp"
#include "SystemWindow.hpp"
#include "SystemShader.hpp"
#include "ScreenShader.hpp"

GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // Positions   // TexCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    
    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

// Generates a texture that is suited for attachments to a framebuffer
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
    // What enum to use?
    GLenum attachment_type = 0;
    if (!depth && !stencil)
    {
        attachment_type = GL_RGB;
    }
    else if (depth && !stencil)
    {
        attachment_type = GL_DEPTH_COMPONENT;
    }
    else if (!depth && stencil)
    {
        attachment_type = GL_STENCIL_INDEX;
    }
    
    
    //Generate texture ID and load texture data
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if(!depth && !stencil)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, attachment_type,
                     SystemWindow::getInstance().getWidth(),
                     SystemWindow::getInstance().getHeight(),
                     0, attachment_type, GL_UNSIGNED_BYTE, NULL);
    }
    
    else
    {
        // Using both a stencil and depth test, needs special format arguments
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8,
                     SystemWindow::getInstance().getWidth(),
                     SystemWindow::getInstance().getHeight(),
                     0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return textureID;
}

//====================================================================================================
SystemFrameBuffer::SystemFrameBuffer()
{
    destroy();
}
//====================================================================================================
SystemFrameBuffer::~SystemFrameBuffer()
{
    destroy();
}
//====================================================================================================
void SystemFrameBuffer::destroy()
{
    _quadVAO = 0;
    _quadVBO = 0;
    _useFrameBuffer = false;
    _framebuffer = 0;
    _textureColorbuffer = 0;
    _rbo = 0;
    _screenShader = nullptr;
}
//====================================================================================================
void SystemFrameBuffer::build()
{
    //
    _framebuffer = 0;
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    
    // Create a color attachment texture
    _textureColorbuffer = generateAttachmentTexture(false, false);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureColorbuffer, 0);
    
    // Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    _rbo = 0;
    glGenRenderbuffers(1, &_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,
                          GL_DEPTH24_STENCIL8,
                          SystemWindow::getInstance().getWidth(),
                          SystemWindow::getInstance().getHeight());
    
    // Use a single renderbuffer object for both a depth AND stencil buffer.
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo); // Now actually attach it
    
    // Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    ///GLuint quadVAO, quadVBO;
    glGenVertexArrays(1, &_quadVAO);
    glGenBuffers(1, &_quadVBO);
    glBindVertexArray(_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
    
    //
    _screenShader = (ScreenShader*)SystemShader::getInstance().getShader("ScreenShader");
}
//====================================================================================================
void SystemFrameBuffer::useBeforeDrawScene()
{
    if (!_useFrameBuffer)
    {
        return;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}
//====================================================================================================
void SystemFrameBuffer::useAfterDrawScene()
{
    if (!_useFrameBuffer)
    {
        return;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    
    //
    _screenShader->_textureColorbuffer = _textureColorbuffer;
    _screenShader->use();
    
    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    //
    glEnable(GL_DEPTH_TEST);
}
//====================================================================================================
void SystemFrameBuffer::setUseFrameBuffer(bool setting)
{
    _useFrameBuffer = setting;
}
//====================================================================================================














