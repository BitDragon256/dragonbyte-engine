#pragma once

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        class Image
        {
        public:
            Image();
        
            VkImage m_image;
            VkImageView m_imageView;
            VkDeviceMemory m_memory;
            
            void create(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
        };
        
    } // namespace vulkan
    
} // namespace dragonbyte_engine