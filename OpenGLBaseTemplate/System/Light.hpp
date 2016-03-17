
#ifndef ___Light_H___
#define ___Light_H___

#include "SupportHeader.h"
#include "Node.hpp"

class Shader;

enum class LIGHT_MODE
{
    NOTHING = 0,
    DIRECTION = 1,
    POINT = 2,
    SPOT = 3
};

class Light : public Node
{
public:
    
    static Light* create(LIGHT_MODE model, const std::string& shaderName);
    
    static Light* createDirectLight(const glm::vec3& dir,
                                    const glm::vec3& amb,
                                    const glm::vec3& diff,
                                    const glm::vec3& spec);
    
    
    
    static Light* createPointLight( const glm::vec3& pos,
                                    const glm::vec3& amb,
                                    const glm::vec3& diff,
                                    const glm::vec3& spec,
                                    float cons,
                                    float linear,
                                    float quadratic);
    
private:
    
    ~Light();
    
    void renderSelf();
    
    bool init(LIGHT_MODE model, const std::string& shaderName);
    
    void cleanUp();
    
    void beforeRenderSelf();
    
    void afterRenderSelf();

private:
    
    LIGHT_MODE  _model;
    std::string _shaderName;
    Shader*     _shader;
    
public:
    
    glm::vec3   _direction;
    glm::vec3   _ambient;
    glm::vec3   _diffuse;
    glm::vec3   _specular;
    float       _constant;
    float       _linear;
    float       _quadratic;
    float       _cutOff;
    float       _outerCutOff;
    
    static std::vector<Light*> directLights;
    static std::vector<Light*> pointLights;
    static std::vector<Light*> spotLights;
};

#endif /* ___Node_H___ */
