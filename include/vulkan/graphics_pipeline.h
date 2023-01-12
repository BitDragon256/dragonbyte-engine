#pragma once

#include <vulkan/vulkan.h>

#include "logical_device.h"
#include "shader_module.h"
#include "swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class GraphicsPipeline
		{
		public:

			GraphicsPipeline(const LogicalDevice& a_krLogicalDevice, const SwapChain& a_krSwapChain);
			~GraphicsPipeline();

			VkPipelineLayout m_pipelineLayout;

		private:

			ShaderModule* m_pFragShaderModule;
			ShaderModule* m_pVertShaderModule;

			const LogicalDevice& m_krLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine