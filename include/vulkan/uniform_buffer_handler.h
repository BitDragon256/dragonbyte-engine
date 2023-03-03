#pragma once

#include <vector>

#include "buffer.h"
#include "descriptor_set_handler.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class UniformBufferHandler
		{
		public:
			UniformBufferHandler();
			~UniformBufferHandler();

			std::vector<Buffer> m_buffers;
			std::vector<void*> m_mappedBuffers;

			void push_data(uint32_t frame, UniformBufferObject ubo);
		};

	} // namespace vulkan

} // namespace dragonbyte_engine