
#ifndef __SystemWindow_H__
#define __SystemWindow_H__

#include "SupportHeader.h"

class GLFWwindow;

class SystemWindow : public Singleton<SystemWindow>
{
public:
    
    SystemWindow();
    
    bool createWindow(const std::string& windowName, int width, int height);
    
    bool isWindowShouldClose();
    
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    
    GLFWwindow* getWindow() const;
    
    void resetViewport();

private:
    
    GLFWwindow* _window;
    std::string _windowName;
    int         _width;
    int         _height;
};


#endif /* SystemWindow_hpp */
