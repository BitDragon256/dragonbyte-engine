#include "vulkan/buffer.h"

#include <stdexcept>

#include "vulkan/object_info.h"
#include "vulkan/logical_device.h"

#include "vulkan/memory.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        Buffer::Buffer() : m_created{ false } {}
        Buffer::~Buffer() { destruct(); }

        VkBuffer m_buffer;
        VkDeviceMemory m_deviceMemory;

        void Buffer::create(uint64_t a_count, uint32_t a_stride, bool a_alwaysMapped, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties)
        {
            if (m_created)
                destruct();

            m_count = a_count;
            m_stride = a_stride;
            m_alwaysMapped = a_alwaysMapped;

            m_usage = a_usage;
            m_properties = a_properties;

            create_internal();
        }
        void Buffer::resize(uint64_t a_count)
        {
            if (m_created)
                destruct();

            m_count = a_count;
            create_internal();
        }
        void Buffer::copy_data(void* a_pData)
        {
            if (m_alwaysMapped)
            {
                memcpy(m_mappedMemory, a_pData, (size_t)m_totalSize);
            }
            else
            {
                void* pData;
                vkMapMemory(oi.pLogicalDevice->m_device, m_deviceMemory, 0, m_totalSize, 0, &pData);
                memcpy(pData, a_pData, (size_t)m_totalSize);
                vkUnmapMemory(oi.pLogicalDevice->m_device, m_deviceMemory);
            }
        }

        void Buffer::copy_from(Buffer& a_rSrcBuffer)
        {
            CommandBuffer commandBuffer{ CP_TRANSFER };
            commandBuffer.begin_recording(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

            VkBufferCopy copyRegion = {};
            copyRegion.srcOffset = 0;
            copyRegion.dstOffset = 0;
            copyRegion.size = a_rSrcBuffer.m_totalSize;

            vkCmdCopyBuffer(commandBuffer.m_commandBuffer, a_rSrcBuffer.m_buffer, m_buffer, 1, &copyRegion);

            commandBuffer.end_recording();

            VkSubmitInfo submitInfo = {};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &commandBuffer.m_commandBuffer;

            vkQueueSubmit(oi.pLogicalDevice->m_transferQueue, 1, &submitInfo, VK_NULL_HANDLE);
            vkQueueWaitIdle(oi.pLogicalDevice->m_transferQueue);
        }
        void Buffer::destruct()
        {
            if (m_created)
            {
                if (m_alwaysMapped)
                {
                    vkUnmapMemory(oi.pLogicalDevice->m_device, m_deviceMemory);
                }

                vkDestroyBuffer(oi.pLogicalDevice->m_device, m_buffer, nullptr);
                vkFreeMemory(oi.pLogicalDevice->m_device, m_deviceMemory, nullptr);

                m_created = false;
            }
        }
        void* Buffer::mapped_memory()
        {
            if (!m_alwaysMapped || !m_created)
                return nullptr;
            return m_mappedMemory;
        }

        void Buffer::create_buffer(VkBufferUsageFlags a_usage)
        {
            VkDeviceSize size = m_totalSize;

            VkBufferCreateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = size;
            bufferInfo.usage = a_usage;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

            VkResult res = vkCreateBuffer(oi.pLogicalDevice->m_device, &bufferInfo, nullptr, &m_buffer);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Buffer");

        }
        void Buffer::allocate_memory(VkMemoryPropertyFlags a_properties)
        {
            VkMemoryRequirements memReq;
            vkGetBufferMemoryRequirements(oi.pLogicalDevice->m_device, m_buffer, &memReq);

            VkMemoryAllocateInfo allocInfo = {};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memReq.size;
            allocInfo.memoryTypeIndex = find_memory_type(memReq.memoryTypeBits, a_properties);

            VkResult res = vkAllocateMemory(oi.pLogicalDevice->m_device, &allocInfo, nullptr, &m_deviceMemory);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to allocate Buffer Memory");

            vkBindBufferMemory(oi.pLogicalDevice->m_device, m_buffer, m_deviceMemory, 0);
        }
        void Buffer::create_internal()
        {
            m_totalSize = m_count * m_stride;

            create_buffer(m_usage);
            allocate_memory(m_properties);

            if (m_alwaysMapped)
            {
                vkMapMemory(oi.pLogicalDevice->m_device, m_deviceMemory, 0, m_totalSize, 0, &m_mappedMemory);
            }

            m_created = true;
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
