#pragma once

#include <vulkan/vulkan.h>

#include "logical_device.h"
#include "shader_module.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		class GraphicsPipeline
		{
		public:

			GraphicsPipeline(const ObjectInfo& a_krObjectInfo);
			~GraphicsPipeline();

			VkPipelineLayout m_pipelineLayout;
			VkPipeline m_pipeline;

		private:

			ShaderModule* m_pFragShaderModule;
			ShaderModule* m_pVertShaderModule;

			const LogicalDevice& m_krLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine