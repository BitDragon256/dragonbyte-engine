#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        template<typename T>
        class Buffer
        {
        public:

            Buffer();
            ~Buffer();
            
            VkBuffer m_buffer;
            VkDeviceMemory m_deviceMemory;

            void create(uint32_t a_count, uint32_t a_stride, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties);
            void copy_data(std::vector<T>& a_rData);

        private:

            uint32_t m_stride;
            uint32_t m_count;
            VkDeviceSize m_totalSize;

            bool m_created;

            void create_buffer(VkBufferUsageFlags a_usage);
            void allocate_memory(VkMemoryPropertyFlags a_properties);
            void destruct();

        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
