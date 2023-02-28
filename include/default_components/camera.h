#pragma once

#include <glm/glm.hpp>
#include "component.h"

namespace dragonbyte_engine
{
    
    class Camera : public Component
    {
    public:
        Camera();
        Camera(float fov, float nearPlane, float farPlane);
        
        glm::mat4 get_matrix();
        glm::mat4 get_view_matrix();
        glm::mat4 get_proj_matrix();
        void tick() override;
        void free_move();
        
        float m_fov;
        float m_nearPlane;
        float m_farPlane;

        bool m_freeMove;
        
    };
    
} // namespace dragonbyte_engine
