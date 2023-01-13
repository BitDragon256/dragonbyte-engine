#pragma once

#include <vulkan/vulkan.h>

#include "logical_device.h"
#include "swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class RenderPass
		{

		public:

			RenderPass(const LogicalDevice& a_krLogicalDevice, const SwapChain& a_krSwapChain);
			~RenderPass();

			VkRenderPass m_renderPass;

		private:

			const LogicalDevice& m_krLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine