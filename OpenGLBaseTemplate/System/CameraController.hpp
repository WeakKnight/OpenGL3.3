
#ifndef __CameraController_H__
#define __CameraController_H__

#include "SupportHeader.h"
#include "Camera.hpp"

class CameraController
{
public:
    
    //
    static glm::mat4 getViewMatrix();
    static glm::mat4 getProjectMatrix();
    
    static void setCameraPosition(glm::vec3 pos);
    static glm::vec3 getCameraPosition();
    
    //
    static void cameraProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    static void cameraProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    static void cameraProcessMouseScroll(GLfloat yoffset);
    
    //
    static glm::vec3 getCameraDirection();
    
    static void resetCamera();

public:
    
    static bool useCameraSpotLight;
    static glm::vec3 ambient;
    static glm::vec3 diffuse;
    static glm::vec3 specular;
    static float constant;
    static float linear;
    static float quadratic;
    static float cutOff;
    static float outerCutOff;

    
    

    
};


#endif /* __App_H__ */
