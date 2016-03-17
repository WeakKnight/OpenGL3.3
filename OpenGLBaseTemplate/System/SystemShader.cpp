
#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemTexture.hpp"
#include "App.hpp"
#include "CameraController.hpp"
#include "TestShader.hpp"
#include "DepthTestShader.hpp"
#include "PointLightShader.hpp"
#include "ScreenShader.hpp"
#include "SkyBoxShader.hpp"
#include "ReflectionShader.hpp"
#include "DrawNormalShader.hpp"
#include "ExplodeShader.hpp"
#include "PlaneShader.hpp"

//====================================================================================================
SystemShader::SystemShader()
{
    destroy();
}
//====================================================================================================
SystemShader::~SystemShader()
{
    destroy();
}
//====================================================================================================
void SystemShader::build()
{
    //
    destroy();
    
    //
    _shaderCache["TriangleShader"] = new Shader("res/TriangleShader.vsh", "res/TriangleShader.fsh");
    
    //
    _shaderCache["TestShader"] = new TestShader("res/TestShader1.vsh", "res/TestShader1.fsh");
    
    //
    _shaderCache["DepthTestShader"] = new DepthTestShader("res/DepthTestShader.vsh", "res/DepthTestShader.fsh");
    
    //
    _shaderCache["SingleColorShader"] = new DepthTestShader("res/SingleColorShader.vsh", "res/SingleColorShader.fsh");
    
    //
    _shaderCache["PointLightShader"] = new PointLightShader("res/PointLightShader.vsh", "res/PointLightShader.fsh");
    
    //
    _shaderCache["ScreenShader"] = new ScreenShader("res/ScreenShader.vsh", "res/ScreenShader.fsh");
    
    //
    _shaderCache["SkyBoxShader"] = new SkyBoxShader("res/SkyBoxShader.vsh", "res/SkyBoxShader.fsh");
    
    //
    _shaderCache["ReflectionShader"] = new ReflectionShader("res/ReflectionShader.vsh", "res/ReflectionShader.fsh");
    _shaderCache["RefractionShader"] = new ReflectionShader("res/RefractionShader.vsh", "res/RefractionShader.fsh");
    
    //
    _shaderCache["DrawNormalShader"] = new DrawNormalShader("res/DrawNormalShader.vsh",
                                                            "res/DrawNormalShader.fsh",
                                                            "res/DrawNormalShader.gsh");
    
    _shaderCache["ExplodeShader"] = new ExplodeShader("res/ExplodeShader.vsh",
                                                         "res/ExplodeShader.fsh",
                                                         "res/ExplodeShader.gsh");
    
    //
    _shaderCache["PlaneShader"] = new PlaneShader("res/PlaneShader.vsh", "res/PlaneShader.fsh");
}
//====================================================================================================
void SystemShader::destroy()
{
    for (auto& s : _shaderCache)
    {
        if (!s.second)
        {
            continue;
        }
        
        delete s.second;
    }
    
    _shaderCache.clear();
}
//====================================================================================================
Shader* SystemShader::getShader(const std::string& shaderName) const
{
    const auto itr = _shaderCache.find(shaderName);
    if (itr != _shaderCache.cend())
    {
        return itr->second;
    }
    
    return nullptr;
}
//====================================================================================================

















