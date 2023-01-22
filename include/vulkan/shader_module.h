#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "logical_device.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		namespace default_shaders
		{

			typedef enum eShader {
				Simple = 0
			} const tShader;

			typedef enum eShaderType {
				Vert = 0, Frag = 1
			} const tShaderType;

			const std::string kPathPrefix = "/home/BitDragon256/Dev/TestProgram/dragonbyte-engine/default_shaders/";
			const std::string kVertShaderPathPostfix = ".vert.spv";
			const std::string kFragShaderPathPostfix = ".frag.spv";

			const std::string kVertShaderFilenames[]{
				"simple"
			};
			const std::string kFragShaderFilenames[]{
				"simple"
			};

			std::string get_shader_filename(tShader a_shader, tShaderType a_shaderType);

		}; // namespace default_shaders

		class ShaderModule
		{

		public:

			ShaderModule(std::string a_shaderFile);
			~ShaderModule();

			VkShaderModule m_shaderModule;

		private:

			std::vector<char> m_shaderCode;
			const LogicalDevice& m_krLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine