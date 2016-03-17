
#ifndef ___Sprite_H___
#define ___Sprite_H___

#include "SupportHeader.h"
#include "Node.hpp"

class Shader;

enum class MODEL
{
    NOTHING = 0,
    CUBE = 1,
    PLANE = 2
};

class DrawNormalShader;

class Sprite : public Node
{
public:
    
    static Sprite* create(MODEL model, const std::string& shaderName);
    
    void setDrawBorder(bool setting);
    
    void setDrawNormal(bool setting);

    void setShader(Shader* sh);
    
private:
    
    void renderSelf();
    
    bool init(MODEL model, const std::string& shaderName);
    
    void cleanUp();
    
    void beforeRenderSelf();
    
    void afterRenderSelf();
    
    void transformSelf();
    
    void drawSimple();

private:
    
    MODEL               _model;
    std::string         _shaderName;
    Shader*             _shader;
    bool                _drawBorder;
    glm::mat4           _borderMatrix;
    Shader*             _drawBorderShader;
    DrawNormalShader* _normalShader;
    bool                _drawNormal;

};

#endif /* ___Node_H___ */
