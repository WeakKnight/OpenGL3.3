
#include "Light.hpp"
#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemSimpleDraw.hpp"
#include "MatrixStack.hpp"
#include "PointLightShader.hpp"


std::vector<Light*> Light::directLights;
std::vector<Light*> Light::pointLights;
std::vector<Light*> Light::spotLights;
//=========================================================================
Light::~Light()
{
    const auto itr1 = std::find(directLights.cbegin(), directLights.cend(), this);
    if (itr1 != directLights.cend())
    {
        directLights.erase(itr1);
    }
    
    const auto itr2 = std::find(pointLights.cbegin(), pointLights.cend(), this);
    if (itr2 != pointLights.cend())
    {
        pointLights.erase(itr2);
    }
    
    const auto itr3 = std::find(spotLights.cbegin(), spotLights.cend(), this);
    if (itr3 != spotLights.cend())
    {
        spotLights.erase(itr3);
    }
}
//=========================================================================
Light* Light::create(LIGHT_MODE model, const std::string& shaderName)
{
    Light* sp = new Light;
    if (!sp->init(model, shaderName))
    {
        delete sp;
        sp = nullptr;
        return nullptr;
    }
    
    return sp;
}
//=========================================================================
Light* Light::createDirectLight(const glm::vec3& dir,
                                const glm::vec3& amb,
                                const glm::vec3& diff,
                                const glm::vec3& spec)
{
    auto lt = Light::create(LIGHT_MODE::DIRECTION, "");
    if (!lt)
    {
        return nullptr;
    }
    
    lt->_direction = dir;
    lt->_ambient = amb;
    lt->_diffuse = diff;
    lt->_specular = spec;
    
    //
    const auto itr1 = std::find(directLights.cbegin(), directLights.cend(), lt);
    if (itr1 == directLights.cend())
    {
        directLights.push_back(lt);
    }
    
    //
    return lt;
}
//=========================================================================
Light* Light::createPointLight( const glm::vec3& pos,
                                const glm::vec3& amb,
                                const glm::vec3& diff,
                                const glm::vec3& spec,
                                float cons,
                                float linear,
                                float quadratic)
{
    auto lt = Light::create(LIGHT_MODE::POINT, "PointLightShader");
    if (!lt)
    {
        return nullptr;
    }
    
    //
    lt->setPosition(pos);

    //
    lt->_ambient = amb;
    lt->_diffuse = diff;
    lt->_specular = spec;
    lt->_constant = cons;
    lt->_linear = linear;
    lt->_quadratic = quadratic;
    
    if (dynamic_cast<PointLightShader*>(lt->_shader) != nullptr)
    {
         ((PointLightShader*)lt->_shader)->_lightNode = lt;
    }
    
    //
    const auto itr1 = std::find(pointLights.cbegin(), pointLights.cend(), lt);
    if (itr1 == pointLights.cend())
    {
        pointLights.push_back(lt);
    }

    return lt;
}
//=========================================================================
bool Light::init(LIGHT_MODE model, const std::string& shaderName)
{
    if (!Node::init())
    {
        return false;
    }
    
    //
    _model = model;
    _shaderName = shaderName;
    _shader = SystemShader::getInstance().getShader(shaderName);
   
    return true;
}
//=========================================================================
void Light::renderSelf()
{
    Node::renderSelf();
    
    if (_shader)
    {
        _shader->use();
        SystemSimpleDraw::getInstance().drawCube();
    }
}
//=========================================================================
void Light::cleanUp()
{
    Node::cleanUp();
    
    //
    _model = LIGHT_MODE::NOTHING;
    _shaderName.clear();
    _shader = nullptr;
    _direction = glm::vec3(0.0f, 0.0f, 0.0f);
    _ambient = glm::vec3(0.0f, 0.0f, 0.0f);
    _diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
    _specular = glm::vec3(0.0f, 0.0f, 0.0f);
    _constant = 0.0f;
    _linear = 0.0f;
    _quadratic = 0.0f;
    _cutOff = 0.0f;
    _outerCutOff = 0.0f;
}
//=========================================================================
void Light::beforeRenderSelf()
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}
//=========================================================================
void Light::afterRenderSelf()
{
    glDisable(GL_CULL_FACE);
}
//=========================================================================














