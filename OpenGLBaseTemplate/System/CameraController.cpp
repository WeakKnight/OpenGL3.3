
#include "CameraController.hpp"
#include "SystemWindow.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

//
bool CameraController::useCameraSpotLight = false;
glm::vec3 CameraController::ambient = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 CameraController::diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 CameraController::specular = glm::vec3(1.0f, 1.0f, 1.0f);
float CameraController::constant = 1.0f;
float CameraController::linear = 0.09f;
float CameraController::quadratic = 0.032f;
float CameraController::cutOff = 12.5f;
float CameraController::outerCutOff = 15.0f;

//====================================================================================================
glm::mat4 CameraController::getViewMatrix()
{
    return camera.GetViewMatrix();
}
//====================================================================================================
glm::mat4 CameraController::getProjectMatrix()
{
    const auto wh = (float)SystemWindow::getInstance().getWidth()/(float)SystemWindow::getInstance().getHeight();
    return glm::perspective(camera.Zoom,
                            wh,
                            0.1f,
                            1000.0f);
}
////====================================================================================================
void CameraController::setCameraPosition(glm::vec3 pos)
{
    camera.Position = pos;
    camera.updateCameraVectors();
}
////====================================================================================================
glm::vec3 CameraController::getCameraPosition()
{
    return camera.Position;
}
////====================================================================================================
void CameraController::cameraProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    camera.ProcessKeyboard(direction, deltaTime);
}
////====================================================================================================
void CameraController::cameraProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    camera.ProcessMouseMovement(xoffset, yoffset, constrainPitch);
}
////====================================================================================================
void CameraController::cameraProcessMouseScroll(GLfloat yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
////====================================================================================================
glm::vec3 CameraController::getCameraDirection()
{
    return camera.Front;
}
//====================================================================================================
void CameraController::resetCamera()
{
    camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));
}
//====================================================================================================





