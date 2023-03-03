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
        
        class Buffer
        {
        public:

            Buffer();
            ~Buffer();
            
            VkBuffer m_buffer;
            VkDeviceMemory m_deviceMemory;

            void create(uint64_t count, uint32_t stride, bool alwaysMapped, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
            void resize(uint64_t count);
            void copy_data(void* pData);
            
            void copy_from(Buffer& rSrcBuffer);
            void destruct();
            void* mapped_memory();

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

            void create_buffer(VkBufferUsageFlags usage);
            void allocate_memory(VkMemoryPropertyFlags properties);
            void create_internal();

        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
