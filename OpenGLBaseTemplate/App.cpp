
#include "App.hpp"
#include "SystemWindow.hpp"
#include "SystemSimpleDraw.hpp"
#include "Shader.hpp"
#include "SystemShader.hpp"
#include "SystemTexture.hpp"
#include "CameraController.hpp"
#include "Node.hpp"
#include "Sprite.hpp"
#include "Light.hpp"
#include "ScreenShader.hpp"
#include "SystemFrameBuffer.hpp"
#include "SkyBoxNode.hpp"
#include "SystemShadow.hpp"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
const GLuint WIDTH = 1024, HEIGHT = 768;
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool keys[1024];

std::vector<int> keyBoardClickList;
GLuint uboMatrices = 0;

//====================================================================================================
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //cout << key << endl;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
            
            keyBoardClickList.push_back(key);
        }
    }
}
//====================================================================================================
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xpos;
    lastY = ypos;
    
    CameraController::cameraProcessMouseMovement(xoffset, yoffset);
}
//====================================================================================================
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    CameraController::cameraProcessMouseScroll(yoffset);
}
//====================================================================================================
void mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
    
}
//====================================================================================================





//====================================================================================================
Node* App::_rootNode = nullptr;
//====================================================================================================
App::App():
_deltaTime(0.0f),
_lastFrame(0.0f)
{

}
//====================================================================================================
App::~App()
{
    if (_rootNode)
    {
        delete _rootNode;
        _rootNode = nullptr;
    }
}
//====================================================================================================
bool App::start()
{
    if (!SystemWindow::getInstance().createWindow("OpenGL3.3", WIDTH, HEIGHT))
    {
        //释放窗口资源
        return false;
    }
    
    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    //
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    //
    glEnable(GL_MULTISAMPLE);
    
    
    // Set the required callback functions
    glfwSetKeyCallback(SystemWindow::getInstance().getWindow(), key_callback);
    glfwSetCursorPosCallback(SystemWindow::getInstance().getWindow(), mouse_callback);
    glfwSetMouseButtonCallback(SystemWindow::getInstance().getWindow(), mouseButton_callback);
    glfwSetScrollCallback(SystemWindow::getInstance().getWindow(), scroll_callback);
    
    // GLFW Options
    //glfwSetInputMode(SystemWindow::getInstance().getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //
    SystemShader::getInstance().build();
    
    //
    SystemSimpleDraw::getInstance().build();
    
    //
    SystemFrameBuffer::getInstance().build();
    
    //
    SystemShadow::getInstance().build();

    //
    _rootNode = Node::createRootNode();
    _rootNode->setPosition(0, 0, 0);
    
    //
    const auto radius = 2.0f;
    const auto sz = 6;
    glm::vec3 pos[sz] = {
        glm::vec3(1 * radius, 0, 0), glm::vec3(-1 * radius, 0, 0),
        glm::vec3(0, 1 * radius, 0), glm::vec3(0, -1 * radius, 0),
        glm::vec3(0, 0, 1 * radius), glm::vec3(0, 0, -1 * radius)
    };
    
    for (auto index = 0; index < sz; ++index)
    {
        auto sp1 = Sprite::create(MODEL::CUBE, "TestShader");
        _rootNode->addChildNode(sp1);
        sp1->setPosition(pos[index]);
        
        if (index == 4)
        {
            //反射
            sp1->setTag(4);
            //sp1->setShader(SystemShader::getInstance().getShader("ReflectionShader"));
        }
        else if (index == 1)
        {
            //折射
            sp1->setTag(1);
            //sp1->setShader(SystemShader::getInstance().getShader("RefractionShader"));
        }
        else if (index == 2)
        {
            sp1->setTag(2);
            //sp1->setDrawNormal(true);
        }
    }
    
    //
//    auto sp2 = Sprite::create(MODEL::CUBE, "DepthTestShader");
//    _rootNode->addChildNode(sp2);
//    sp2->setDrawBorder(true);
    
    //
    auto dirLight = Light::createDirectLight(glm::vec3(-0.2f, -1.0f, -0.3f),
                                             glm::vec3(0.05f, 0.05f, 0.05f),
                                             glm::vec3(0.4f, 0.4f, 0.4f),
                                             glm::vec3(0.5f, 0.5f, 0.5f));
    
    _rootNode->addChildNode(dirLight);
    dirLight->setPosition(3.0f, 0.0f, 0.0f);
    
    //
    const auto pointLightSz = 1;
    glm::vec3 pointLightPositions[pointLightSz] = {
//        glm::vec3( 1.7f,  0.2f,  2.0f),
//        glm::vec3( 2.3f, -3.3f, -4.0f),
//        glm::vec3(-4.0f,  -2.0f, -10.0f),
//        glm::vec3( 0.0f,  1.5f, -6.0f)
        
        //glm::vec3(0.5f,  4.0f, -2.0f)
        glm::vec3(-2.0f, 4.0f, -1.0f)
    };
    
    for (auto index = 0; index < pointLightSz; ++index)
    {
        auto pointLight = Light::createPointLight(pointLightPositions[index],
                                                glm::vec3(0.05f, 0.05f, 0.05f),
                                                glm::vec3(0.8f, 0.8f, 0.8f),
                                                glm::vec3(1.0f, 1.0f, 1.0f),
                                                1.0f,
                                                0.09f,
                                                0.032f);
        
        //
        _rootNode->addChildNode(pointLight);
        pointLight->setScale(0.5f);
    }
    
    
    //
    auto sp3 = Sprite::create(MODEL::PLANE, "PlaneShader");
    _rootNode->addChildNode(sp3);
    sp3->setPosition(0.0f, -3.0f, 0.0f);
    
    //
    auto skyBoxNode = SkyBoxNode::create("res/skybox/right.jpg",
                                         "res/skybox/left.jpg",
                                         "res/skybox/top.jpg",
                                         "res/skybox/bottom.jpg",
                                         "res/skybox/back.jpg",
                                         "res/skybox/front.jpg");
    
    //保证最后画!
    _rootNode->addChildNode(skyBoxNode);
    skyBoxNode->setPosition(0, 0, 1000);
    skyBoxNode->setTag(10000);
    
    //GLuint uboMatrices;
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // Define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    
    // Store the projection matrix (we only have to do this once) (note: we're not using zoom anymore by changing the FoV. We only create the projection matrix once now)
    glm::mat4 projection = glm::perspective(45.0f,
                                            (float)SystemWindow::getInstance().getWidth()/(float)SystemWindow::getInstance().getHeight(),
                                            0.1f,
                                            100.0f);
    
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    //
    return true;
}
//====================================================================================================
void App::run()
{
    //如果不退出，则进行游戏循环以及双重缓冲
    while (SystemWindow::getInstance().isWindowShouldClose())
    {
        //
        beforeDraw();
        
        //
        draw();
        
        //
        afterDraw();
    }
}
//====================================================================================================
void App::beforeDraw()
{
    // Calculate deltatime of current frame
    GLfloat currentFrame = glfwGetTime();
    _deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
    
    //
    glfwPollEvents();
    
    //
    update(_deltaTime);
    
    //在这里执行各种渲染操作
    //指定用什么颜色来清理缓冲区
    //清理缓冲区操作，参数为颜色缓冲区
    
    SystemFrameBuffer::getInstance().useBeforeDrawScene();
    
    //
    SystemShadow::getInstance().generateShadowMap();
    
    glViewport(0, 0, SystemWindow::getInstance().getWidth(), SystemWindow::getInstance().getHeight());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    
    //
    glm::mat4 view = CameraController::getViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
//====================================================================================================
void App::draw()
{
    if (_rootNode)
    {
        _rootNode->render(_deltaTime);
    }
}
//====================================================================================================
void App::afterDraw()
{
    SystemFrameBuffer::getInstance().useAfterDrawScene();
    glfwSwapBuffers(SystemWindow::getInstance().getWindow());
}
//====================================================================================================
void App::end()
{
    //释放窗口资源
    glfwTerminate();
}
//====================================================================================================
void App::update(float dt)
{
    if(keys[GLFW_KEY_W])
    {
        CameraController::cameraProcessKeyboard(FORWARD, dt);
    }
    else if(keys[GLFW_KEY_S])
    {
        CameraController::cameraProcessKeyboard(BACKWARD, dt);
    }
    else if(keys[GLFW_KEY_A])
    {
        CameraController::cameraProcessKeyboard(LEFT, dt);
    }
    else if(keys[GLFW_KEY_D])
    {
        CameraController::cameraProcessKeyboard(RIGHT, dt);
    }
    else if(keys[GLFW_KEY_Q])
    {
        CameraController::cameraProcessKeyboard(UP, dt);
    }
    else if(keys[GLFW_KEY_E])
    {
        CameraController::cameraProcessKeyboard(DOWN, dt);
    }
    else if (keys[GLFW_KEY_R])
    {
        CameraController::resetCamera();
    }
    else if(keys[GLFW_KEY_EQUAL])
    {
        //
        CameraController::cutOff += 0.1f;
        CameraController::cutOff = std::min(12.5f, CameraController::cutOff);
        
        //
        CameraController::outerCutOff += 0.1f;
        CameraController::outerCutOff = std::min(15.0f, CameraController::outerCutOff);
    }
    else if (keys[GLFW_KEY_MINUS])
    {
        //
        CameraController::cutOff -= 0.1f;
        CameraController::cutOff = std::max(2.5f, CameraController::cutOff);
        
        //
        CameraController::outerCutOff -= 0.1f;
        CameraController::outerCutOff = std::max(5.0f, CameraController::outerCutOff);
    }
    
    for (auto& k : keyBoardClickList)
    {
        if (k == GLFW_KEY_R)
        {
            CameraController::resetCamera();
        }
        else if (k == GLFW_KEY_F)
        {
            CameraController::useCameraSpotLight = !CameraController::useCameraSpotLight;
        }
    }
    
    keyBoardClickList.clear();
}
//====================================================================================================
