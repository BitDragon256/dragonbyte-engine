#pragma once

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        template<typename T>
        class Buffer
        {
            Buffer(uint32_t a_count, uint32_t a_stride, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkDeviceMemory& a_rDeviceMemory);
            ~Buffer();
            
            VkBuffer m_buffer;
        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
