#pragma once

#include <cstdint>

#include <glm/glm.hpp>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		// the used struct for passing necessary object info to the vertex shader
		struct ObjectData
		{
			glm::mat4 model; // the model matrix of the object (scale, position, rotation)
		};

	} // namespace vulkan

} // namespace dragonbyte_engine