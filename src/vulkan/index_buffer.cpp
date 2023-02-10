#include "vulkan/index_buffer.h"

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		IndexBuffer::IndexBuffer() :
            m_pLogicalDevice { oi.pLogicalDevice }
        {
            m_indices = kTestCubeIndices;

            m_buffer.create(
                static_cast<uint64_t>(m_indices.size()),
                sizeof(Index),
                false,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
            );

            m_stagingBuffer.create(
                static_cast<uint64_t>(m_indices.size()),
                sizeof(Index),
                false,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
            );

            m_stagingBuffer.copy_data(m_indices);
            m_buffer.copy_from(m_stagingBuffer);

            m_stagingBuffer.destruct();
		}
		IndexBuffer::~IndexBuffer()
		{

		}

        void IndexBuffer::bind()
        {
            vkCmdBindIndexBuffer(oi.pCommandBuffer->m_commandBuffer, m_buffer.m_buffer, 0, INDEX_TYPE_VK);
        }
        void IndexBuffer::reload()
        {
            m_stagingBuffer.copy_data(m_indices);
            m_buffer.copy_from(m_stagingBuffer);
        }

        std::vector<Index> kTestSquareIndices = {
                0, 1, 2, 2, 3, 0
        };
        std::vector<Index> kTest2SquareIndices = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 9, 10, 11,
            12, 13, 14, 13, 14, 15
        };
        std::vector<Index> kTestCubeIndices = {
            0, 1, 2, 1, 3, 2,
            4, 7, 5, 5, 7, 6,
            1, 5, 6, 1, 6, 3,
            4, 0, 2, 4, 2, 7,
            5, 1, 0, 5, 0, 4,
            3, 7, 2, 3, 6, 7
        };

	} // namespace vulkan

} // namespace dragonbyte_engine