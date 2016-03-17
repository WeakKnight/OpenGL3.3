
#include "Sprite.hpp"
#include "SystemShader.hpp"
#include "Shader.hpp"
#include "SystemSimpleDraw.hpp"
#include "MatrixStack.hpp"
#include "DrawNormalShader.hpp"

//=========================================================================
Sprite* Sprite::create(MODEL model, const std::string& shaderName)
{
    Sprite* sp = new Sprite;
    if (!sp->init(model, shaderName))
    {
        delete sp;
        sp = nullptr;
        return nullptr;
    }
    
    return sp;
}
//=========================================================================
bool Sprite::init(MODEL model, const std::string& shaderName)
{
    if (!Node::init())
    {
        return false;
    }
    
    //
    _model = model;
    _shaderName = shaderName;
    _shader = SystemShader::getInstance().getShader(shaderName);
    _normalShader = (DrawNormalShader*)SystemShader::getInstance().getShader("DrawNormalShader");
   
    return true;
}
//=========================================================================
void Sprite::renderSelf()
{
    Node::renderSelf();
    
    if (getTag() == 4)
    {
        int a = 0;
    }
    
    if (_shader)
    {
        _shader->use();
    }
    
    //if (_model == MODEL::CUBE)
    {
        if (_drawBorder)
        {
            //glClear(GL_STENCIL_BUFFER_BIT);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
        }

        //
        drawSimple();

        //
        if (_drawBorder)
        {
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            //glStencilFunc(GL_GEQUAL, 0, 0xFF);
            glStencilMask(0x00);
            //glDisable(GL_DEPTH_TEST);
        
            if (!_drawBorderShader)
            {
                _drawBorderShader = SystemShader::getInstance().getShader("SingleColorShader");
            }
            
            //
            MatrixStack::setLastMatrix(_borderMatrix);
            _drawBorderShader->use(); //这里面会传入transform
            MatrixStack::setLastMatrix(_transformMatrix);
            
            //
            drawSimple();
            
            //
            glStencilMask(0xFF);
            //glEnable(GL_DEPTH_TEST);
            glClear(GL_STENCIL_BUFFER_BIT);
        }
        
        if (_drawNormal)
        {
            if (_normalShader)
            {
                _normalShader->use();
                drawSimple();
            }
        }
    }
}
//=========================================================================
void Sprite::cleanUp()
{
    Node::cleanUp();
    
    //
    _model = MODEL::NOTHING;
    _shaderName.clear();
    _shader = nullptr;
    _drawBorder = false;
    _drawBorderShader = nullptr;
    _normalShader = nullptr;
    _drawNormal = false;
}
//=========================================================================
void Sprite::setDrawBorder(bool setting)
{
    _drawBorder = setting;
}
//=========================================================================
void Sprite::setDrawNormal(bool setting)
{
    _drawNormal = setting;
}
//=========================================================================
void Sprite::setShader(Shader* sh)
{
    _shader = sh;
}
//=========================================================================
void Sprite::beforeRenderSelf()
{
    glStencilMask(0x00);
    
    //
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}
//=========================================================================
void Sprite::afterRenderSelf()
{
    glDisable(GL_CULL_FACE);
}
//=========================================================================
void Sprite::transformSelf()
{
    //
    _borderMatrix = MatrixStack::getLastMatrix();
    
    //
    const auto scaleValue = 1.1f;
    _borderMatrix = glm::scale(_borderMatrix, glm::vec3(scaleValue, scaleValue, scaleValue));
    _borderMatrix = glm::translate(_borderMatrix, glm::vec3(_position.x/scaleValue, _position.y/scaleValue, _position.z/scaleValue));

    //
    Node::transformSelf();
}
//=========================================================================
void Sprite::drawSimple()
{
    if (_model == MODEL::CUBE)
    {
        SystemSimpleDraw::getInstance().drawCube();
    }
    else if (_model == MODEL::PLANE)
    {
        SystemSimpleDraw::getInstance().drawPlane();
    }
}
//=========================================================================














