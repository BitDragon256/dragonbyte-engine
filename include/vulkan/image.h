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
            ~Image();
        
            VkImage m_image;
            VkImageView m_imageView;
            VkDeviceMemory m_memory;
            
            void create(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImageAspectFlags aspectFlags);
            void destruct();

        private:
            void create_image(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
            void create_image_view(VkFormat format, VkImageAspectFlags aspectFlags);
            
        };
        
    } // namespace vulkan
    
} // namespace dragonbyte_engine