#include "graphics/window.h"

#include <stdexcept>

namespace dragonbyte_engine
{

	namespace graphics
	{

		void Window::create_window()
		{
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			m_glfwWindow = glfwCreateWindow(m_kWidth, m_kHeight, m_kName.c_str(), nullptr, nullptr);
		}

		void Window::get_surface(VkInstance& instance, VkSurfaceKHR* surface)
		{
			VkResult res = glfwCreateWindowSurface(instance, m_glfwWindow, nullptr, surface);

			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create surface");
		}

	} // namespace rendering

} // namespace dragonbyte_engine