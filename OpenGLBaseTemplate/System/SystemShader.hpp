
#ifndef __SystemShader_H__
#define __SystemShader_H__

#include "SupportHeader.h"

//
class Shader;

//
class SystemShader : public Singleton<SystemShader>
{
public:
    
    SystemShader();
    ~SystemShader();
    
    void build();
    
    void destroy();
    
    Shader* getShader(const std::string& shaderName) const;
    
private:
    
    std::unordered_map<std::string, Shader*> _shaderCache;
};

#endif /* __SystemShader_H__ */
