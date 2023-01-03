#pragma once

#define GLFW_INCLUDE_VULKAN
#include <external/glfw/include/GLFW/glfw3.h>

#include "vulkan/vulkan.h"

#include <string>

namespace dragonbyte_engine
{
	namespace graphics
	{

		class Window
		{
		public:
			Window(const unsigned int width, const unsigned int height, std::string name);
			~Window();

			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			bool should_close();

		private:

			const unsigned int m_kWidth;
			const unsigned int m_kHeight;

			const std::string m_kName;

			GLFWwindow* m_glfwWindow;

			void create_window();
			void get_surface(VkInstance& instance, VkSurfaceKHR* surface);

		};

	} // namespace graphics
} // namespace dragonbyte_engine