#include "vulkan/surface.h"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		Surface::Surface(const ObjectInfo& a_krObjectInfo) :
			m_krInstance(*a_krObjectInfo.pInstance), m_krWindow(*a_krObjectInfo.pWindow)
		{
			VkResult res = glfwCreateWindowSurface(a_krObjectInfo.pInstance->m_instance, a_krObjectInfo.pWindow->m_pGlfwWindow, nullptr, &m_surface);
			if (res != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create surface");
			}
		}

		Surface::~Surface()
		{
			vkDestroySurfaceKHR(m_krInstance.m_instance, m_surface, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine