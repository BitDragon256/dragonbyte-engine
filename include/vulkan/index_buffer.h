#pragma once

#include <memory>
#include <vector>

#include "buffer.h"
#include "vertex.h"

namespace dragonbyte_engine
{
	
	namespace vulkan
	{

		class IndexBuffer
		{

        public:

            IndexBuffer();
            ~IndexBuffer();

            std::vector<Index> m_indices;

            Buffer<Index> m_buffer;
            Buffer<Index> m_stagingBuffer;

            void bind();

        private:

            std::weak_ptr<LogicalDevice> m_pLogicalDevice;

            const std::vector<Index> kTestSquareIndices = {
                0, 1, 2, 2, 3, 0
            };

		};

	} // namespace vulkan

} // namespace dragonbyte_engine