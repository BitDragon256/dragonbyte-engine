#include "vulkan/surface.h"

#include <GLFW/glfw3.h>

#include <stdexcept>

#include "vulkan/helper.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		Surface::Surface(const Instance& a_rInstance, Window& a_rWindow)
		{
			Helper::check_result(
				glfwCreateWindowSurface(a_rInstance.m_instance, a_rWindow.m_pGlfwWindow, nullptr, &m_surface),
				"Failed to create surface"
			);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine