
#include "SystemWindow.hpp"

//====================================================================================================
SystemWindow::SystemWindow():
_window(nullptr),
_windowName(),
_width(800),
_height(600)
{

}
//====================================================================================================
bool SystemWindow::createWindow(const std::string& windowName, int width, int height)
{
    if (_window)
    {
        return true;
    }
    
    //
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    //创建窗口对象
    _window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }
    
    glfwMakeContextCurrent(_window);
    
    //初始化GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    
    //设置窗口大小以及GL渲染位置
    glViewport(0, 0, width, height);
    
    //
    _windowName = windowName;
    _width = width;
    _height = height;

    return true;
}
//====================================================================================================
void SystemWindow::resetViewport()
{
    glViewport(0, 0, _width, _height);
}
//====================================================================================================
bool SystemWindow::isWindowShouldClose()
{
    if (_window)
    {
        return !glfwWindowShouldClose(_window);
    }
    
    return false;
}
//====================================================================================================
GLFWwindow* SystemWindow::getWindow() const
{
    return _window;
}
//====================================================================================================
