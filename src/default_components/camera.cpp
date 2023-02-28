#include "default_components/camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

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
        return get_proj_matrix() * get_view_matrix();
    }
    glm::mat4 Camera::get_view_matrix()
    {
        return {
            glm::lookAt(
                TRANSFORM.m_position.to_glm(),
                TRANSFORM.m_position.to_glm() + glm::vec3{0.f, 1.f, 0.f},
                //glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.f, 0.f, 1.f)
            )
        };
    }
    glm::mat4 Camera::get_proj_matrix()
    {
        glm::mat4 proj = glm::perspective(
            glm::radians(45.0f),//m_fov),
            vulkan::oi.pSwapChain->m_extent.width / (float)vulkan::oi.pSwapChain->m_extent.height,
            0.1f,//m_nearPlane,
            10.f//m_farPlane
        );
        proj[1][1] *= -1;
        return proj;
    }
    void Camera::tick()
    {
        if (m_freeMove)
            free_move();
    }
    void Camera::free_move()
    {
        TRANSFORM.m_position.x += INPUT.get_axis("Horizontal") * GAME_CLOCK.m_deltaTime;
        TRANSFORM.m_position.y += INPUT.get_axis("Vertical") * GAME_CLOCK.m_deltaTime;
        TRANSFORM.m_position.z += INPUT.get_axis("FlyControl") * GAME_CLOCK.m_deltaTime;
        
        TRANSFORM.m_rotation.z += INPUT.get_axis("ArrowHorizontal") * GAME_CLOCK.m_deltaTime * 40.f;
    }
    void Camera::set_active()
    {
        RENDER_ENGINE.set_camera(this);
    }
    
} // namespace dragonbyte_engine
