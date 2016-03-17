
#ifndef __MatrixStack_H__
#define __MatrixStack_H__


#include "SupportHeader.h"
#include "Camera.hpp"

class MatrixStack
{
public:
    
    static void init();
    
    static void pushMatrix();
    
    static void popMatrix();
    
    static glm::mat4 getLastMatrix();
    
    static glm::mat4 getMatrix();
    
    static void setLastMatrix(glm::mat4 m4);
};

#endif /* __MatrixStack_H__ */