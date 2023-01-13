#pragma once

#include <vulkan/vulkan.h>

#include "logical_device.h"
#include "swapchain.h"
#include "render_pass.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class Framebuffer
		{
		public:

			Framebuffer(const LogicalDevice& a_krLogicalDevice, const SwapChain& a_krSwapChain, const RenderPass& a_krRenderPass);
			~Framebuffer();
		};

		class FramebufferHandler
		{
		public:

			FramebufferHandler(const LogicalDevice& a_krLogicalDevice, const SwapChain& a_krSwapChain, const RenderPass& a_krRenderPass);
			~FramebufferHandler();
		};

	} // namespace vulkan

} // namespace dragonbyte_engine