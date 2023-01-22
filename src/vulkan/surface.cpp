#include "vulkan/surface.h"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		Surface::Surface() :
			m_pInstance(oi.pInstance), m_pWindow(oi.pWindow)
		{
			VkResult res = glfwCreateWindowSurface(oi.pInstance->m_instance, oi.pWindow->m_pGlfwWindow, nullptr, &m_surface);
			if (res != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create surface");
			}
		}

		Surface::~Surface()
		{
			vkDestroySurfaceKHR(m_pInstance.lock()->m_instance, m_surface, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine