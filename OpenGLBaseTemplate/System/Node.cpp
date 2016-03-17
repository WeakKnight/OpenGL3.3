
#include "Node.hpp"
#include "MatrixStack.hpp"


//===================================================================================
Node::Node()
{
    cleanUp();
}
//===================================================================================
Node::~Node()
{
    cleanUp();
}
//===================================================================================
void Node::cleanUp()
{
    _name.clear();
    _tag = -1;
    _children.clear();
    _parent = nullptr;
    _nodeUpdateStarted = false;
    _visible = true;
    _dirty = true;
    _isRootNode = false;
    _position = glm::vec3(0.0f, 0.0f, 0.0f);
    _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    _zorderDirty = false;
}
//===================================================================================
void Node::render(float dt)
{
    //
    nodeUpdate(dt);
    
    if (!_visible)
    {
        return;
    }
    
    if (_dirty)
    {
        _dirty = false;
    }

    if (_zorderDirty)
    {
        _zorderDirty = false;
        sortChildren();
    }
    
    //
    MatrixStack::pushMatrix();
    
    //
    transformSelf();
    
    //
    if (!_isRootNode)
    {
        //
        beforeRenderSelf();
        
        //
        renderSelf();
        
        //
        afterRenderSelf();
    }
    
    //
    for (auto& n : _children)
    {
        n->render(dt);
    }
    
    MatrixStack::popMatrix();
}
//===================================================================================
void Node::addChildNode(Node* node)
{
    if (!node)
    {
        return;
    }
    
    for (auto& n : _children)
    {
        if (n == node)
        {
            return;
        }
    }
    
    //
    _children.push_back(node);
    node->setParent(node);
    _zorderDirty = true;
}
//===================================================================================
void Node::setPosition(float x, float y, float z)
{
    _position = glm::vec3(x, y, z);
    markDirty();
}
//===================================================================================
void Node::setPosition(glm::vec3 pos)
{
    _position = pos;
    markDirty();
}
//===================================================================================
const glm::vec3& Node::getPosition() const
{
    return _position;
}
//===================================================================================
void Node::setTag(int tag)
{
    _tag = tag;
}
//===================================================================================
void Node::setScale(float s)
{
    _scale = glm::vec3(s, s, s);
    markDirty();
}
//===================================================================================
void Node::nodeUpdate(float dt)
{
    if (!_nodeUpdateStarted)
    {
        _nodeUpdateStarted = true;
        nodeStart();
    }
}
//===================================================================================
void Node::transformSelf()
{
    //
    _transformMatrix = MatrixStack::getLastMatrix();
    
    //本地空间旋转???
    _transformMatrix = glm::scale(_transformMatrix, _scale);
    _transformMatrix = glm::translate(_transformMatrix, glm::vec3(_position.x/_scale.x, _position.y/_scale.y, _position.z/_scale.z));
    
    //自转
    //m4 = glm::rotate(m4, 100.0f * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    MatrixStack::setLastMatrix(_transformMatrix);
}
//===================================================================================
void Node::renderSelf()
{
    
}
//===================================================================================
void Node::beforeRenderSelf()
{

}
//===================================================================================
void Node::afterRenderSelf()
{

}
//===================================================================================
bool Node::init()
{
    cleanUp();
    return true;
}
//===================================================================================
Node* Node::create()
{
    auto nd = new Node();
    if (!nd->init())
    {
        delete nd;
        return nullptr;
    }

    return nd;
}
//===================================================================================
Node* Node::createRootNode()
{
    auto nd = new Node();
    if (!nd->init())
    {
        delete nd;
        return nullptr;
    }
    
    nd->_isRootNode = true;
    return nd;
}
//===================================================================================
 void Node::setParent(Node* p)
{
    _parent = p;
    markDirty();
}
//===================================================================================
void Node::nodeStart()
{
    //
    _nodeUpdateStarted = true;
}
//===================================================================================
void Node::setVisible(bool vis)
{
    _visible = vis;
    markDirty();
}
//===================================================================================
Node* Node::getChildNode(int tag) const
{
    for (auto& node : _children)
    {
        if (node->getTag() == tag)
        {
            return node;
        }
    }
    
    return nullptr;
}
//===================================================================================
void Node::sortChildren()
{
    auto sortFunc = [](const Node* l, const Node* r)
    {
        return l->getZOrder() < r->getZOrder();
    };

    std::stable_sort(_children.begin(), _children.end(), sortFunc);
}
//===================================================================================








