#include "vulkan/graphics_pipeline.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		GraphicsPipeline::GraphicsPipeline(const LogicalDevice& a_krLogicalDevice)
		{
			// create the shader modules
			m_pVertShaderModule = new ShaderModule(default_shaders::get_vert_shader_filename(default_shaders::eVertShader::Simple), a_krLogicalDevice);
			m_pFragShaderModule = new ShaderModule(default_shaders::get_frag_shader_filename(default_shaders::eFragShader::Simple), a_krLogicalDevice);

			// create infos for later staging the shader modules
			VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
			vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
			vertShaderStageInfo.module = m_pVertShaderModule->m_shaderModule;
			vertShaderStageInfo.pName = "main";

			VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
			fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			fragShaderStageInfo.module = m_pFragShaderModule->m_shaderModule;
			fragShaderStageInfo.pName = "main";

			// combine both
			VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };
		}
		GraphicsPipeline::~GraphicsPipeline()
		{
			delete m_pFragShaderModule;
			delete m_pVertShaderModule;
		}

	} // namespace vulkan

} // namespace dragonbyte_engine