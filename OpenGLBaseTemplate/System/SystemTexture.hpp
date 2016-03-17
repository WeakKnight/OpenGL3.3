
#ifndef __SystemTexture_H__
#define __SystemTexture_H__

#include "SupportHeader.h"

class Texture
{
public:
    
    Texture():
    _width(0),
    _height(0),
    _texturePath(),
    _textureId()
    {
    
    }
    
    const std::string& getTexturePath() const { return _texturePath; }
    
public:
    
    int             _width;
    int             _height;
    std::string     _texturePath;
    GLuint          _textureId;
};

class TGA2DTexture : public Texture
{
public:
    
    bool init(const std::string& szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);
    
private:
    
    int      _components;
    GLenum   _format;
};


class CubeMapTexture : public Texture
{
public:
    
    CubeMapTexture();
    
    bool init(const std::string& cubeTextureName, const std::vector<std::string>& faces);
    
private:
    
    std::vector<std::string> _faces;
};

//
class SystemTexture : public Singleton<SystemTexture>
{
public:
    
    SystemTexture();
    ~SystemTexture();
    
    //
    void destroy();
    
    //
    const Texture* getTexture(const std::string& fileName) const;
    
    //
    bool addTextureCache(Texture* texture);
    
    //
    Texture* createTGA2DTexture(const std::string& szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);
    Texture* createCubeMapTexture(const std::string& cubeTextureName, const std::vector<std::string>& faces);

    
private:
    
    std::unordered_map<std::string, Texture*> _textureCache;

};

#endif /* __SystemShader_H__ */
