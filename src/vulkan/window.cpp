#include "vulkan/window.h"

#include <stdexcept>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		Window::Window(const WindowConfig& a_rWindowConfig) :
			m_kWidth(a_rWindowConfig.width), m_kHeight(a_rWindowConfig.height), m_kName(a_rWindowConfig.name)
		{
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			m_pGlfwWindow = glfwCreateWindow(m_kWidth, m_kHeight, m_kName.c_str(), nullptr, nullptr);
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::should_close()
		{
			return glfwWindowShouldClose(m_pGlfwWindow);
		}
		void Window::tick()
		{
			glfwPollEvents();
		}

	} // namespace vulkan

} // namespace dragonbyte_engine