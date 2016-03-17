
#ifndef __SystemShadow_H__
#define __SystemShadow_H__

#include "SupportHeader.h"

class ScreenShader;

//
class SystemShadow : public Singleton<SystemShadow>
{
public:
    
    SystemShadow();
    ~SystemShadow();
    
    //
    void destroy();

    //
    void build();
    
    //
    void useBeforeDrawScene();
    void useAfterDrawScene();
    
    void generateShadowMap();

    
    //
    void setUseFrameBuffer(bool setting);
    
public:
    
    //
    GLuint depthMapFBO;
    GLuint depthMap;
    glm::mat4 lightProjection;
    glm::mat4 lightView;
    glm::mat4 lightSpaceMatrix;
    bool debugDepthShadow;
};

#endif /* __SystemShadow_H__ */
