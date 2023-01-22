#pragma once

#include <memory>

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

			Surface();
			~Surface();

			VkSurfaceKHR m_surface;

		private:

			std::weak_ptr<Instance> m_pInstance;
			std::weak_ptr<Window> m_pWindow;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine