#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/vulkan.h"

#include <string>

namespace dragonbyte_engine
{
	namespace vulkan
	{

		struct WindowConfig
		{
			uint32_t width;
			uint32_t height;

			std::string name;
		};

		class Window
		{
		public:

			Window(const WindowConfig& a_rWindowConfig);
			~Window();

			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			bool should_close();
			void tick();

			GLFWwindow* m_pGlfwWindow;

		private:

			const unsigned int m_kWidth;
			const unsigned int m_kHeight;

			const std::string m_kName;

		};

	} // namespace graphics
} // namespace dragonbyte_engine