#include "vulkan/surface.h"

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		Surface::Surface(Instance* a_pInstance, Window* a_pWindow) :
			m_pInstance(a_pInstance), m_pWindow(a_pWindow)
		{
			VkResult res = glfwCreateWindowSurface(a_pInstance->m_instance, a_pWindow->m_pGlfwWindow, nullptr, &m_surface);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create surface");
		}

		Surface::~Surface()
		{
			if (m_pInstance == nullptr)
				throw std::runtime_error("Destruction of Instance before Surface is forbidden");
			vkDestroySurfaceKHR(m_pInstance->m_instance, m_surface, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine