#pragma once

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

			Framebuffer(const ObjectInfo& a_krObjectInfo);
			~Framebuffer();

			VkFramebuffer m_framebuffer;

			static size_t s_swapchainImageIndex;

		private:

			const LogicalDevice& m_krLogicalDevice;

		};

		class FramebufferHandler
		{
		public:

			FramebufferHandler(const ObjectInfo& a_krObjectInfo);
			~FramebufferHandler();

			std::vector<Framebuffer> m_swapChainFramebuffers;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine