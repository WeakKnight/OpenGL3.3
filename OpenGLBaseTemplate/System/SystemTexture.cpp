
#include "SystemTexture.hpp"
#include "Shader.hpp"
#include "SOIL.h"

//====================================================================================================
bool TGA2DTexture::init(const std::string& szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
//    GLbyte* pBits = readTGABits(szFileName.c_str(),
//                                   &(_width),
//                                   &(_height),
//                                   &(_components),
//                                   &(_format));
    
    unsigned char * image = SOIL_load_image(szFileName.c_str(), &_width, &_height, &_components, SOIL_LOAD_RGB);
    if(image == nullptr)
    {
        return false;
    }
    
    //
    this->_texturePath = szFileName;
    
    //
    glGenTextures(1, &(this->_textureId));
    glBindTexture(GL_TEXTURE_2D, this->_textureId);
    
    //
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //glGenerateMipmap(GL_TEXTURE_2D);
    
    /*
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_COMPRESSED_RGB,
                 this->_width,
                 this->_height,
                 0,
                 this->_format,
                 GL_UNSIGNED_BYTE, pBits);
    
    free(pBits);
    */
    
    SOIL_free_image_data(image);
    
    if(minFilter == GL_LINEAR_MIPMAP_LINEAR ||
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    //
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return true;
}
//====================================================================================================




//====================================================================================================
CubeMapTexture::CubeMapTexture():
_faces()
{

}
//====================================================================================================
bool CubeMapTexture::init(const std::string& cubeTextureName, const std::vector<std::string>& faces)
{
    if (faces.size() != 6)
    {
        return false;
    }
    
    this->_texturePath = cubeTextureName;
    this->_faces = faces;
    
    glGenTextures(1, &_textureId);
    
    unsigned char* image = nullptr;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i].c_str(), &_width, &_height, 0, SOIL_LOAD_RGB);
//        if (!image)
//        {
//            int a = 0;
//        }
        
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return true;
}
//====================================================================================================



//====================================================================================================
SystemTexture::SystemTexture()
{
    destroy();
}
//====================================================================================================
SystemTexture::~SystemTexture()
{
    destroy();
}
//====================================================================================================
void SystemTexture::destroy()
{
    for (auto& t : _textureCache)
    {
        if (!t.second)
        {
            continue;
        }
        
        if (t.second->_textureId > 0)
        {
            glDeleteTextures(1, &t.second->_textureId);
        }
        
        delete t.second;
    }
    
    _textureCache.clear();
}
//====================================================================================================
const Texture* SystemTexture::getTexture(const std::string& fileName) const
{
    auto itr = _textureCache.find(fileName);
    if (itr == _textureCache.cend())
    {
        return nullptr;
    }
    
    return itr->second;
}
//====================================================================================================
bool SystemTexture::addTextureCache(Texture* texture)
{
    if (!texture)
    {
        return false;
    }
    
    auto findTex = getTexture(texture->getTexturePath());
    if (!findTex)
    {
        _textureCache[texture->getTexturePath()] = texture;
    }
    
    return true;
}
//====================================================================================================
Texture* SystemTexture::createTGA2DTexture(const std::string& szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    auto findTex = getTexture(szFileName);
    if (findTex)
    {
        return (Texture*)findTex;
    }
    
    //
    auto newTAGTexture = new TGA2DTexture;
    if (!newTAGTexture->init(szFileName, minFilter, magFilter, wrapMode))
    {
        delete newTAGTexture;
        newTAGTexture = nullptr;
        return nullptr;
    }
   
    //
    addTextureCache(newTAGTexture);
    return newTAGTexture;
}
//====================================================================================================
Texture* SystemTexture::createCubeMapTexture(const std::string& cubeTextureName, const std::vector<std::string>& faces)
{
    auto findTex = getTexture(cubeTextureName);
    if (findTex)
    {
        return (Texture*)findTex;
    }
    
    //
    auto newCubeMapTexture = new CubeMapTexture;
    if (!newCubeMapTexture->init(cubeTextureName, faces))
    {
        delete newCubeMapTexture;
        newCubeMapTexture = nullptr;
        return nullptr;
    }
    
    //
    addTextureCache(newCubeMapTexture);
    return newCubeMapTexture;
}
//====================================================================================================
















