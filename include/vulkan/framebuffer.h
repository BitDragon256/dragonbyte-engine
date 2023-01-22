#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan.h>

#include "logical_device.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		struct ObjectInfo;

		class Framebuffer
		{
		public:

			Framebuffer();
			~Framebuffer();

			VkFramebuffer m_framebuffer;

			static size_t s_swapchainImageIndex;

		private:

			std::weak_ptr<LogicalDevice> m_pLogicalDevice;
		};

		class FramebufferHandler
		{
		public:

			FramebufferHandler();
			~FramebufferHandler();

			Framebuffer& get(size_t index);

		private:

			std::vector<Framebuffer*> m_swapChainFramebuffers;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine