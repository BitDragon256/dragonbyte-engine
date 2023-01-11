#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "logical_device.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		namespace default_shaders
		{

			typedef enum {
				Simple = 0
			} const eVertShader;

			typedef enum {
				Simple = 0
			} const eFragShader;

			const std::string kPathPrefix = "shaders/";
			const std::string kVertShaderPathPostfix = ".vert.spv";
			const std::string kFragShaderPathPostfix = ".frag.spv";

			const std::string kVertShaderFilenames[]{
				"simple"
			};
			const std::string kFragShaderFilenames[]{
				"simple"
			};

			std::string get_vert_shader_filename(eVertShader a_vertShader);
			std::string get_frag_shader_filename(eFragShader a_fragShader);

		};

		class ShaderModule
		{

		public:

			ShaderModule(std::string a_shaderFile, const LogicalDevice& a_krLogicalDevice);
			~ShaderModule();

			VkShaderModule m_shaderModule;

		private:

			std::vector<char> m_shaderCode;
			const LogicalDevice& m_krLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine