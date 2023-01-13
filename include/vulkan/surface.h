#pragma once

#include <vulkan/vulkan.h>

#include "instance.h"
#include "window.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		class Surface
		{
		public:

			Surface(const ObjectInfo& a_krObjectInfo);
			~Surface();

			Surface(const Surface&) = delete;
			const Surface& operator=(const Surface&) = delete;

			VkSurfaceKHR m_surface;

		private:

			const Instance& m_krInstance;
			const Window& m_krWindow;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine