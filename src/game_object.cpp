#include "game_object.h"

#include <algorithm>
#include <functional>

#include "component.h"
#include "mesh.h"

namespace dragonbyte_engine
{
    
    /* -----------------------------------------------------
    *                   Transform Node
    *  -----------------------------------------------------
    */

    bool has_child(TransformNode* a_pNode, TransformNode* a_pChild)
    {
        return std::find(a_pNode->children.begin(), a_pNode->children.end(), a_pChild) == a_pNode->children.end();
    }
    bool is_valid(TransformNode* a_pNode)
    {
        return  a_pNode != nullptr &&
                a_pNode->pTransform != nullptr;
    }

    TransformNode::TransformNode(Transform* pTransform) :
        pTransform{ pTransform }
    {

    }
    void TransformNode::add_child(TransformNode* a_pNode)
    {
        if (a_pNode == nullptr || has_child(this, a_pNode))
            return;
        children.push_back(a_pNode);
        a_pNode->set_parent(this);
    }
    void TransformNode::set_parent(TransformNode* a_pNode)
    {
        if (a_pNode == nullptr)
            return;
        pParent = a_pNode;
        pParent->add_child(this);
    }

    /* -----------------------------------------------------
    *                     Transform
    *  -----------------------------------------------------
    */
    Transform::Transform(const GameObject& a_krGameObject) :
        m_position{  }, m_scale{  }, m_rotation{  }, m_pGameObject{ &a_krGameObject }, m_node{ this }
    {

    }

    void Transform::add_child(Transform& a_rTransform)
    {
        m_node.add_child(&a_rTransform.m_node);
    }
    GameObject& Transform::add_child(GameObject& a_rGameObject)
    {
        add_child(a_rGameObject.m_transform);
        return a_rGameObject;
    }
    void Transform::set_parent(Transform& a_rTransform)
    {
        m_node.set_parent(&a_rTransform.m_node);
    }
    void Transform::set_parent(GameObject& a_rGameObject)
    {
        set_parent(a_rGameObject.m_transform);
    }
    Position Transform::global_position()
    {   
        auto it = &m_node;
        Position pos{ m_position };
        while (is_valid(it->pParent))
        {
            it = it->pParent;
            pos += it->pTransform->m_position;
        }
        return pos;
    }
    Scale Transform::global_scale()
    {
        auto it = &m_node;
        Scale scale{ m_scale };
        while (is_valid(it->pParent))
        {
            it = it->pParent;
            scale += it->pTransform->m_scale;
        }
        return scale;
    }
    Rotation Transform::global_rotation()
    {
        auto it = &m_node;
        Rotation rot{ m_rotation };
        while (is_valid(it->pParent))
        {
            it = it->pParent;
            rot += it->pTransform->m_rotation;
        }
        return rot;
    }

    /* -----------------------------------------------------
    *                       GameObject
    *  -----------------------------------------------------
    */
    GameObject::GameObject() :
        m_transform{ *this }
    {

    }
    GameObject::GameObject(GameObject& a_rParent) :
        m_transform{ *this }
    {
        m_transform.set_parent(a_rParent);
    }
    GameObject::GameObject(const GameObject& a_krCopy) :
        m_transform{ *this }
    {
        *this = a_krCopy;
    }
    GameObject& GameObject::operator=(const GameObject& a_krOther)
    {
        if (this == &a_krOther)
            return *this;

        m_transform = a_krOther.m_transform;
        m_components = a_krOther.m_components;
        m_boundingBox = a_krOther.m_boundingBox;
        m_rigidbodyIndex = a_krOther.m_rigidbodyIndex;
        m_meshIndex = a_krOther.m_meshIndex;

        return *this;
    }

    void GameObject::tick()
    {
        for (std::size_t i = 0; i < m_components.size(); i++)
        {
            m_components[i].tick();
        }
    }
    Mesh& GameObject::get_mesh()
    {
        return dynamic_cast<Mesh&>(m_components[m_meshIndex]);
    }
    
    
} // namespace dragonbyte_engine
