#include "default_components/camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"

#include "transform.h"
#include "game_object.h"
#include "overseer.h"
#include "input_engine.h"

using namespace dragonbyte_engine;

namespace dragonbyte_engine
{
    
    Camera::Camera() :
        m_fov{ 90.f }, m_nearPlane{ 0.01f }, m_farPlane{ 20.f }
    {}
    Camera::Camera(float a_fov, float a_nearPlane, float a_farPlane) :
        m_fov{ a_fov }, m_nearPlane{ a_nearPlane }, m_farPlane{ a_farPlane }
    {}
    
    glm::mat4 Camera::get_matrix()
    {
        glm::mat4 view {
            glm::lookAt(
                glm::vec3(0.f, 3.f, 0.f),
                glm::vec3(0.f),
                glm::vec3(0.f, 1.f, 0.f)
            )
        };
        glm::mat4 proj {
            glm::perspective(
                glm::radians(m_fov),
                vulkan::oi.pSwapChain->m_extent.width / (float)vulkan::oi.pSwapChain->m_extent.height,
                m_nearPlane,
                m_farPlane
            )
        };
        
        return proj * view;
    }
    void Camera::tick()
    {
        if (m_freeMove)
            free_move();
    }
    void Camera::free_move()
    {
        TRANSFORM.m_position.x += INPUT.get_axis("Horizontal");
        TRANSFORM.m_position.y += INPUT.get_axis("Vertical");
    }
    
} // namespace dragonbyte_engine
