#include "game_object.h"

#include "component.h"

namespace dragonbyte_engine
{
    
    Position Transform::global_position()
    {   
        Transform* t = this;
        Position pos = position;
        while (t->parent)
        {
            t = t->parent;
            position += t->position;
        }
        return pos;
    }
    Scale Transform::global_scale()
    {
        Transform* t = this;
        Scale s = scale;
        while (t->parent)
        {
            t = t->parent;
            s += t->scale;
        }
        return s;
    }
    Rotation Transform::global_rotation()
    {
        Transform* t = this;
        Rotation rot = rotation;
        while (t->parent)
        {
            t = t->parent;
            rot += t->rotation;
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
