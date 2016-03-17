
#ifndef __SystemFrameBuffer_H__
#define __SystemFrameBuffer_H__

#include "SupportHeader.h"

class ScreenShader;

//
class SystemFrameBuffer : public Singleton<SystemFrameBuffer>
{
public:
    
    SystemFrameBuffer();
    ~SystemFrameBuffer();
    
    //
    void destroy();

    //
    void build();
    
    //
    void useBeforeDrawScene();
    void useAfterDrawScene();
    
    //
    void setUseFrameBuffer(bool setting);
    
private:
    
    GLuint          _quadVAO;
    GLuint          _quadVBO;
    bool            _useFrameBuffer;
    GLuint          _framebuffer;
    GLuint          _textureColorbuffer;
    GLuint          _rbo;
    ScreenShader*   _screenShader;
};

#endif /* __SystemFrameBuffer_H__ */
