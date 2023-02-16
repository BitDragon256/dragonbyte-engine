#include "default_components/camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{
    
    Camera::Camera(GameObject& a_rGameObject, GameClock& a_rGameClock) :
        Component(a_rGameObject, a_rGameClock), m_fov{ 90.f }, m_nearPlane{ 0.01f }, m_farPlane{ 20.f }
    {}
    Camera::Camera(GameObject& a_rGameObject, GameClock& a_rGameClock, float a_fov, float a_nearPlane, float a_farPlane) :
        Component(a_rGameObject, a_rGameClock), m_fov{ a_fov }, m_nearPlane{ a_nearPlane }, m_farPlane{ a_farPlane }
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
    
} // namespace dragonbyte_engine
