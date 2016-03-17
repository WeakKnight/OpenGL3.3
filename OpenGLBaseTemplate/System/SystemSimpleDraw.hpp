
#ifndef __SystemSimpleDraw_H__
#define __SystemSimpleDraw_H__

#include "SupportHeader.h"

class Texture;


class SimpleDrawBatch
{
public:
    
    SimpleDrawBatch():
    _VBO(0),
    _EBO(0),
    _VAO(0)
    {
    
    }
    
    ~SimpleDrawBatch()
    {
    
    }
    
    virtual void make()
    {
        
    }
    
    virtual void draw()
    {
        
    }
    
public:
    
    GLuint      _VBO;
    GLuint      _EBO;
    GLuint      _VAO;
};


//
class DrawBatchFloor : public SimpleDrawBatch
{
public:

    void make() override;
    void draw() override;
};

//
class DrawBatchTriangle : public SimpleDrawBatch
{
public:
    
    void make() override;
    void draw() override;
};

//
class DrawBatchCube : public SimpleDrawBatch
{
public:
    
    void make() override;
    void draw() override;
};

//
class DrawBatchPlane : public SimpleDrawBatch
{
public:
    
    void make() override;
    void draw() override;
};

//
class SystemSimpleDraw : public Singleton<SystemSimpleDraw>
{
public:
    
    SystemSimpleDraw();
    ~SystemSimpleDraw();
    
    void build();
    
    //
    void drawPlane();
    void drawTriangle();
    void drawCube();

private:
    
    DrawBatchPlane*     _plane;
    DrawBatchTriangle*  _triangle;
    DrawBatchCube*      _cube;
};


#endif /* __SystemSimpleDraw_H__ */
