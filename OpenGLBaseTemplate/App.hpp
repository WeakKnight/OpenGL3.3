
#ifndef __App_H__
#define __App_H__

#include "SupportHeader.h"

class Node;

class App
{
public:
    
    App();
    ~App();
    
    //
    bool start();
    void run();
    void end();
    
    //
    static Node* getRootNode() { return _rootNode; }
    
private:
    
    void beforeDraw();
    void draw();
    void afterDraw();
    void update(float dt);
    
private:

    float _deltaTime;	
    float _lastFrame;
    static Node* _rootNode;
};

#endif /* __App_H__ */
