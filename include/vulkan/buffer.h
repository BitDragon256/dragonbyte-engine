#pragma once

#include <cstring>

#include <vector>

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

#include "object_info.h"
#include "logical_device.h"
#include "memory.h"
#include "command_buffer.h"
#include "command_pool.h"
#include "allocator.h"

// #define USE_VMA

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        template<typename T>
        class Buffer
        {
        public:

            Buffer() : m_created{ false } {}
            ~Buffer() { destruct(); }
            
            VkBuffer m_buffer;
            VkDeviceMemory m_deviceMemory;

            void create(uint64_t a_count, uint32_t a_stride, bool a_alwaysMapped, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties)
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
            void resize(uint64_t a_count)
            {
                if (m_created)
                    destruct();

                m_count = a_count;
                create_internal();
            }
            void copy_data(std::vector<T>& a_rData)
            {
                if (m_alwaysMapped)
                {
                    memcpy(m_mappedMemory, a_rData.data(), (size_t)m_totalSize);
                }
                else
                {
                    void* pData;
                    vkMapMemory(oi.pLogicalDevice->m_device, m_deviceMemory, 0, m_totalSize, 0, &pData);
                    memcpy(pData, a_rData.data(), (size_t)m_totalSize);
                    vkUnmapMemory(oi.pLogicalDevice->m_device, m_deviceMemory);
                }
            }
            
            void copy_from(Buffer<T>& a_rSrcBuffer)
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
            void destruct()
            {
                if (m_created)
                {
#ifdef USE_VMA
                    vmaDestroyBuffer(
                        oi.pAllocator->m_allocator,
                        m_buffer,
                        m_allocation
                    );
#else
                    if (m_alwaysMapped)
                    {
                        vkUnmapMemory(oi.pLogicalDevice->m_device, m_deviceMemory);
                    }

                    vkDestroyBuffer(oi.pLogicalDevice->m_device, m_buffer, nullptr);
                    vkFreeMemory(oi.pLogicalDevice->m_device, m_deviceMemory, nullptr);
#endif

                    m_created = false;
                }
            }

        private:

            uint32_t m_stride;
            uint64_t m_count;
            VkDeviceSize m_totalSize;
            VkBufferUsageFlags m_usage;
            VkMemoryPropertyFlags m_properties;

            bool m_created;
            bool m_alwaysMapped;
            void* m_mappedMemory;
            
            VmaAllocation m_allocation;

            void create_buffer(VkBufferUsageFlags a_usage)
            {
                VkDeviceSize size = m_totalSize;

                VkBufferCreateInfo bufferInfo = {};
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.size = size;
                bufferInfo.usage = a_usage;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

#ifdef USE_VMA
                
                VmaAllocationCreateInfo vmaAllocInfo = {};
                vmaAllocInfo.usage = VMA_MEMORY_USAGE_AUTO;
                VkResult res = vmaCreateBuffer(
                    oi.pAllocator->m_allocator,
                    &bufferInfo,
                    &vmaAllocInfo,
                    &m_buffer,
                    &m_allocation,
                    nullptr
                );
                
#else          
                VkResult res = vkCreateBuffer(oi.pLogicalDevice->m_device, &bufferInfo, nullptr, &m_buffer);
#endif
                if (res != VK_SUCCESS)
                    throw std::runtime_error("Failed to create Buffer");
                    
            }
            void allocate_memory(VkMemoryPropertyFlags a_properties)
            {
#ifdef USE_VMA

#else
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
#endif
            }
            void create_internal()
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

        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
