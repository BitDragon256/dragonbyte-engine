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
				Simple = 0, SimpleMultimodel = 1, Pixel = 1
			} const tShader;

			typedef enum eShaderType {
				Vert = 0, Frag = 1
			} const tShaderType;

#ifdef _WIN32
			const std::string kPathPrefix = "X:/Dev/CurvedSpaceGame/dragonbyte-engine/default_shaders/";
#else
			const std::string kPathPrefix = "/home/BitDragon256/Dev/TestProgram/dragonbyte-engine/default_shaders/";
#endif
			const std::string kVertShaderPathPostfix = ".vert.spv";
			const std::string kFragShaderPathPostfix = ".frag.spv";

			const std::string kVertShaderFilenames[]{
				"simple", "simple_multimodel"
			};
			const std::string kFragShaderFilenames[]{
				"simple", "pixel"
			};

			std::string get_shader_filename(tShader a_shader, tShaderType a_shaderType);

		}; // namespace default_shaders

		class ShaderModule
		{

		public:

			ShaderModule();
			ShaderModule(std::string a_shaderFile);
			~ShaderModule();

			VkShaderModule m_shaderModule;

			void create(std::string a_shaderFile);

		private:

			std::vector<char> m_shaderCode;
			bool m_created;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine