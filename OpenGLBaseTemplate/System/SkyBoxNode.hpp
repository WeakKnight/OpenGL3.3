
#ifndef ___SkyBoxNode_H___
#define ___SkyBoxNode_H___

#include "SupportHeader.h"
#include "Node.hpp"

class Shader;
class CubeMapTexture;
class SkyBoxShader;

class SkyBoxNode : public Node
{
public:
    
    static SkyBoxNode* create(const std::string& right,
                              const std::string& left,
                              const std::string& top,
                              const std::string& bottom,
                              const std::string& back,
                              const std::string& front);

    static SkyBoxNode* create(const std::vector<std::string>& textures);
    
    
    CubeMapTexture* getSkyBoxTexture() const { return _cubeMapTexture; }
    
private:
    
    void renderSelf();
    
    bool init(const std::vector<std::string>& textures);
    
    void cleanUp();
    
    void beforeRenderSelf();
    
    void afterRenderSelf();
        
private:
    
    CubeMapTexture* _cubeMapTexture;
    GLuint          _skyboxVAO;
    GLuint          _skyboxVBO;
    SkyBoxShader*   _shader;
};

#endif /* ___Node_H___ */
