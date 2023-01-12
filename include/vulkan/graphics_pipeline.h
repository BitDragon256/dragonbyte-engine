#pragma once

#include <vulkan/vulkan.h>

#include "logical_device.h"
#include "shader_module.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class GraphicsPipeline
		{
		public:

			GraphicsPipeline(const LogicalDevice& a_krLogicalDevice);
			~GraphicsPipeline();



		private:

			ShaderModule* m_pFragShaderModule;
			ShaderModule* m_pVertShaderModule;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine