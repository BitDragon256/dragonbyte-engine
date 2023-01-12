#include "vulkan/shader_module.h"

#include <stdexcept>

#include "file_engine.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		namespace default_shaders
		{

			std::string get_shader_filename(tShader a_shader, tShaderType a_shaderType)
			{
				if (a_shaderType == tShaderType::Vert)
					return kPathPrefix + kVertShaderFilenames[static_cast<size_t>(a_shader)] + kVertShaderPathPostfix;
				if (a_shaderType == tShaderType::Frag)
					return kPathPrefix + kFragShaderFilenames[static_cast<size_t>(a_shader)] + kFragShaderPathPostfix;
				return "";
			}

		} // namespace default_shaders

		ShaderModule::ShaderModule(std::string a_shaderFile, const LogicalDevice& a_krLogicalDevice) :
			m_krLogicalDevice{ a_krLogicalDevice }
		{
			// get the compiled shader
			m_shaderCode = FileEngine::read_file(a_shaderFile);

			// actually create the shader module
			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = m_shaderCode.size();
			createInfo.pCode = reinterpret_cast<const uint32_t*>(m_shaderCode.data());

			VkResult res = vkCreateShaderModule(a_krLogicalDevice.m_device, &createInfo, nullptr, &m_shaderModule);
			if (res != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create shader module");
			}
		}
		ShaderModule::~ShaderModule()
		{
			vkDestroyShaderModule(m_krLogicalDevice.m_device, m_shaderModule, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine