#include "default_components/camera.h"

#include <math.h>
#include <vector>

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
        return get_proj_matrix() * get_view_matrix();
    }
    glm::mat4 Camera::get_view_matrix()
    {
        return {
            glm::lookAt(
                TRANSFORM.m_position.to_glm(),
                TRANSFORM.m_position.to_glm()
                    + glm::vec3{
                        sin(TRANSFORM.m_rotation.z),
                        cos(TRANSFORM.m_rotation.z),
                        sin(TRANSFORM.m_rotation.y)
                    },
                glm::vec3(0.f, 0.f, 1.f)
            )
        };
    }
    glm::mat4 Camera::get_proj_matrix()
    {
        glm::mat4 proj = glm::perspective(
            glm::radians(45.0f),//m_fov),
            vulkan::oi.pSwapChain->m_extent.width / (float)vulkan::oi.pSwapChain->m_extent.height,
            0.01f,//m_nearPlane,
            100.f//m_farPlane
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
        TRANSFORM.m_position += TRANSFORM.right() * INPUT.get_axis("Horizontal") * GAME_CLOCK.m_deltaTime * 3;
        TRANSFORM.m_position += TRANSFORM.forward() * INPUT.get_axis("Vertical") * GAME_CLOCK.m_deltaTime * 3;
        TRANSFORM.m_position += TRANSFORM.up() * INPUT.get_axis("FlyControl") * GAME_CLOCK.m_deltaTime * 3;
        
        TRANSFORM.m_rotation.z += -INPUT.get_delta_mouse_pos().x * GAME_CLOCK.m_deltaTime;
        if (TRANSFORM.m_rotation.z >= 7)
            TRANSFORM.m_rotation.z -= 3.14159265f * 2.f;
        if (TRANSFORM.m_rotation.z <= 7)
            TRANSFORM.m_rotation.z += 3.14159265f * 2.f;
        
        TRANSFORM.m_rotation.y = fmaxf( fminf(
            static_cast<float>(
                  TRANSFORM.m_rotation.y
                + INPUT.get_delta_mouse_pos().y
                * GAME_CLOCK.m_deltaTime
            ),
            3.14159265f / 2), -3.14159265f / 2
        );
    }
    void Camera::set_active()
    {
        RENDER_ENGINE.set_camera(this);
    }
    
} // namespace dragonbyte_engine
