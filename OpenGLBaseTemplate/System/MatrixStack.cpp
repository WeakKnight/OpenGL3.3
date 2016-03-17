
#include "MatrixStack.hpp"



std::deque<glm::mat4> matrixStack;
//glm::mat4 emptyMatrix;

//====================================================================================================
void MatrixStack::init()
{
    matrixStack.clear();
}
//====================================================================================================
void MatrixStack::pushMatrix()
{
    if (!matrixStack.empty())
    {
        glm::mat4 copy = matrixStack.back();
        matrixStack.push_back(copy);
    }
    else
    {
        glm::mat4 m;
        matrixStack.push_back(m);
    }
}
//====================================================================================================
void MatrixStack::popMatrix()
{
    if (!matrixStack.empty())
    {
        matrixStack.pop_back();
    }
}
//====================================================================================================
glm::mat4 MatrixStack::getLastMatrix()
{
    if (!matrixStack.empty())
    {
        return matrixStack.back();
    }
    
    return glm::mat4();
}
//====================================================================================================
glm::mat4 MatrixStack::getMatrix()
{
    if (!matrixStack.empty())
    {
        glm::mat4 m = matrixStack[0];
        for (auto index = 1; index < matrixStack.size(); ++index)
        {
            m *= matrixStack[index];
        }
        
        return m;
    }
    
    return glm::mat4();
}
//====================================================================================================
void MatrixStack::setLastMatrix(glm::mat4 m4)
{
    if (matrixStack.empty())
    {
        return;
    }
    
    //
    auto& ref = matrixStack.back();
    ref = m4;
}
//====================================================================================================












