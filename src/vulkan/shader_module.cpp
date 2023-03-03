#include "vulkan/shader_module.h"

#include <stdexcept>

#include "file_engine.h"

#include "vulkan/logical_device.h"

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		namespace default_shaders
		{

			std::string get_shader_filename(tShader a_shader, tShaderType a_shaderType)
			{
				std::string filepath = "";
				if (a_shaderType == tShaderType::Vert)
					filepath = kPathPrefix + kVertShaderFilenames[static_cast<size_t>(a_shader)] + kVertShaderPathPostfix;
				else if (a_shaderType == tShaderType::Frag)
					filepath = kPathPrefix + kFragShaderFilenames[static_cast<size_t>(a_shader)] + kFragShaderPathPostfix;
				
				std::cout << "Loading shader from " << filepath << '\n';

				return filepath;
			}

		} // namespace default_shaders

		ShaderModule::ShaderModule() : m_created{ false } {}
		ShaderModule::ShaderModule(std::string a_shaderFile) :
			m_created{ false }
		{
			create(a_shaderFile);
		}
		ShaderModule::~ShaderModule()
		{
			vkDestroyShaderModule(oi.pLogicalDevice->m_device, m_shaderModule, nullptr);
		}

		void ShaderModule::create(std::string a_shaderFile)
		{
			if (m_created)
				return;

			// get the compiled shader
			m_shaderCode = FileEngine::read_file(a_shaderFile);

			// actually create the shader module
			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = m_shaderCode.size();
			createInfo.pCode = reinterpret_cast<const uint32_t*>(m_shaderCode.data());

			VkResult res = vkCreateShaderModule(oi.pLogicalDevice->m_device, &createInfo, nullptr, &m_shaderModule);
			if (res != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create shader module");
			}

			m_created = true;
		}

	} // namespace vulkan

} // namespace dragonbyte_engine