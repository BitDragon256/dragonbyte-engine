#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "buffer.h"
#include "object_data.h"

#define OBJECT_BUFFER_HANDLER_DEFAULT_SIZE 128
#define OBJECT_BUFFER_HANDLER_SIZE_STEP 64

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class ObjectBufferHandler
		{
		public:

			ObjectBufferHandler();
			~ObjectBufferHandler();

			std::vector<Buffer<ObjectData>> m_buffers;

			std::vector<ObjectData> m_data;

			void create();
			void destruct();
			void set_data(const std::vector<ObjectData>& rData);
			void push_data(uint32_t frame);
			std::vector<VkBuffer> get_buffers();

		private:
			void resize_buffers(size_t size);
		};

	} // namespace vulkan

} // namespace dragonbyte_engine