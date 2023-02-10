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
			uint32_t indexStart; // the starting index of the object in the index buffer (inclusive)
			uint32_t indexEnd; // the ending index of the object in the index buffer (exclusive)
			glm::mat4 model; // the model matrix of the object (scale, position, rotation)
		};

	} // namespace vulkan

} // namespace dragonbyte_engine