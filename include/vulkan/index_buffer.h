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
            void reload();

            bool m_hasChanged;

            static const std::vector<Index> kTestSquareIndices;
            static const std::vector<Index> kTest2SquareIndices;
            static const std::vector<Index> kTestCubeIndices;

        private:

            std::weak_ptr<LogicalDevice> m_pLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine