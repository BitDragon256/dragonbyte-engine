#include "vulkan/index_buffer.h"

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		IndexBuffer::IndexBuffer() :
            m_pLogicalDevice { oi.pLogicalDevice }
        {
            m_indices = kTest2SquareIndices;

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

	} // namespace vulkan

} // namespace dragonbyte_engine