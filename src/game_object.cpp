#include "game_object.h"

#include "component.h"
#include "mesh.h"

namespace dragonbyte_engine
{
    
    /* -----------------------------------------------------
    *                       Transform
    *  -----------------------------------------------------
    */
    Transform::Transform(const GameObject& a_krGameObject) :
        m_position{  }, m_scale{  }, m_rotation{  }, m_children{  }, m_parent{ nullptr }, m_pGameObject{ &a_krGameObject }
    {

    }

    void Transform::add_child(Transform& a_rTransform)
    {
        m_children.push_back(&a_rTransform);
    }
    GameObject& Transform::add_child(GameObject& a_rGameObject)
    {
        add_child(a_rGameObject.m_transform);
        return a_rGameObject;
    }
    void Transform::set_parent(Transform& a_rTransform)
    {
        m_parent = &a_rTransform;
        a_rTransform.add_child(*this);
    }
    void Transform::set_parent(GameObject& a_rGameObject)
    {
        set_parent(a_rGameObject.m_transform);
    }
    Position Transform::global_position()
    {   
        auto t = this;
        Position pos = m_position;
        while (t->m_parent)
        {
            t = t->m_parent;
            m_position += t->m_position;
        }
        return pos;
    }
    Scale Transform::global_scale()
    {
        auto t = this;
        Scale s = m_scale;
        while (t->m_parent)
        {
            t = t->m_parent;
            s += t->m_scale;
        }
        return s;
    }
    Rotation Transform::global_rotation()
    {
        Transform* t = this;
        Rotation rot = m_rotation;
        while (t->m_parent)
        {
            t = t->m_parent;
            rot += t->m_rotation;
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
