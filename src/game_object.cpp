#include "game_object.h"

#include "component.h"

namespace dragonbyte_engine
{
    
    Position Transform::global_position()
    {   
        Transform* t = this;
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
        Transform* t = this;
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
    
    void GameObject::tick()
    {
        for (std::size_t i = 0; i < m_components.size(); i++)
        {
            m_components[i].tick();
        }
    }
    
} // namespace dragonbyte_engine
