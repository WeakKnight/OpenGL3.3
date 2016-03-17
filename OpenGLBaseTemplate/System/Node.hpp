
#ifndef ___Node_H___
#define ___Node_H___

#include "SupportHeader.h"

class Node
{
public:
    
    Node();
    ~Node();
    
public:
    
    virtual void cleanUp();
    
    void render(float dt);
    
    void addChildNode(Node* node);
    
    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 pos);
    const glm::vec3& getPosition() const;
    
    void setTag(int tag);
    long getTag() const { return _tag; }
    
    //
    void setScale(float s);
    
    //
    void setParent(Node* p);
    
    //
    void nodeUpdate(float dt);
    
    //
    void setVisible(bool vis);
    
    //
    Node* getChildNode(int tag) const;
    
    //
    float getZOrder() const { return _position.z; }
    
public:
    
    static Node* create();
    static Node* createRootNode();

protected:
 
    bool init();
    
    void markDirty() { _dirty = true; }
    
    //
    virtual void nodeStart();
    
    //
    virtual void transformSelf();

    //
    virtual void renderSelf();
    virtual void beforeRenderSelf();
    virtual void afterRenderSelf();
    
    virtual void sortChildren();

protected:
    
    std::string             _name;
    long                    _tag;
    std::vector<Node*>      _children;
    Node*                   _parent;
    bool                    _nodeUpdateStarted;
    bool                    _visible;
    bool                    _dirty;
    bool                    _isRootNode;
    glm::vec3               _position;
    glm::vec3               _scale;
    glm::mat4               _transformMatrix;
    bool                    _zorderDirty;
};

#endif /* ___Node_H___ */
