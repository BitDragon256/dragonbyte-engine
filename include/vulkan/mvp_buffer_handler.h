#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "buffer.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		struct MVP
		{
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 proj;
		};

		class MVPBufferHandler
		{
		public:

			MVPBufferHandler();
			~MVPBufferHandler();

			std::vector<Buffer<MVP>> m_buffers;
			std::vector<void*> m_mappedBuffers;

			std::vector<MVP> m_mvps;

			void push_data(uint32_t frame);
			std::vector<VkBuffer> get_buffers();

		};

	} // namespace vulkan

} // namespace dragonbyte_engine