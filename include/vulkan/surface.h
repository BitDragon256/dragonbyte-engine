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

			Surface(const Instance& a_rInstance, Window& a_rWindow);
			~Surface();

			VkSurfaceKHR m_surface;

		private:



		};

	} // namespace vulkan

} // namespace dragonbyte_engine