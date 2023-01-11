#pragma once

#include <vulkan/vulkan.h>

#include "instance.h"
#include "window.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class Surface
		{
		public:

			Surface(Instance* a_pInstance, Window* a_pWindow);
			~Surface();

			Surface(const Surface&) = delete;
			const Surface& operator=(const Surface&) = delete;

			VkSurfaceKHR m_surface;

		private:

			Instance* m_pInstance;
			Window* m_pWindow;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine