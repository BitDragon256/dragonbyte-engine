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

        private:

            std::weak_ptr<LogicalDevice> m_pLogicalDevice;

            const std::vector<Index> kTestSquareIndices = {
                0, 1, 2, 2, 3, 0
            };
            const std::vector<Index> kTest2SquareIndices = {
                0, 1, 2, 2, 3, 0,
                4, 5, 6, 6, 7, 4,
                8, 9, 10, 9, 10, 11,
                12, 13, 14, 13, 14, 15
            };
            const std::vector<Index> kTestCubeIndices = {
                0, 1, 2, 1, 3, 2,
                4, 7, 5, 5, 7, 6,
                1, 5, 6, 1, 6, 3,
                4, 0, 2, 4, 2, 7,
                5, 1, 0, 5, 0, 4,
                3, 7, 2, 3, 6, 7
            };

		};

	} // namespace vulkan

} // namespace dragonbyte_engine