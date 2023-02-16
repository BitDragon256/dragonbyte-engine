#pragma once

#include <glm/glm.hpp>
#include "component.h"

namespace dragonbyte_engine
{
    
    class Camera : Component
    {
    public:
        Camera(GameObject& gameObject, GameClock& gameClock);
        Camera(GameObject& gameObject, GameClock& gameClock, float fov, float nearPlane, float farPlane);
        
        glm::mat4 get_matrix();
        
        float m_fov;
        float m_nearPlane;
        float m_farPlane;
        
    };
    
} // namespace dragonbyte_engine
