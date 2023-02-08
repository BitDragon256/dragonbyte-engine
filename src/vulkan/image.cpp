#include "vulkan/image.h"

#include <stdexcept>

#include "vulkan/object_info.h"
#include "vulkan/logical_device.h"
#include "vulkan/memory.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        Image::Image()
        {

        }
        Image::~Image()
        {
            destruct();
        }
        void Image::create(uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkImageAspectFlags a_aspectFlags)
        {
            create_image(a_width, a_height, a_format, a_tiling, a_usage, a_properties);
            create_image_view(a_format, a_aspectFlags);
        }
        void Image::destruct()
        {
            vkDestroyImageView(oi.pLogicalDevice->m_device, m_imageView, nullptr);
            vkDestroyImage(oi.pLogicalDevice->m_device, m_image, nullptr);
            vkFreeMemory(oi.pLogicalDevice->m_device, m_memory, nullptr);
        }
        
        void Image::create_image(uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkMemoryPropertyFlags a_properties)
        {
            VkImageCreateInfo imageInfo = {};
            imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            
            imageInfo.extent.width = a_width;
            imageInfo.extent.height = a_height;
            imageInfo.extent.depth = 1;
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.format = a_format;
            imageInfo.tiling = a_tiling;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            imageInfo.usage = a_usage;
            imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            
            VkResult res = vkCreateImage(oi.pLogicalDevice->m_device, &imageInfo, nullptr, &m_image);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Image");
                
            allocate_image(m_image, &m_memory, a_properties);
            
            vkBindImageMemory(oi.pLogicalDevice->m_device, m_image, m_memory, 0);
        }
        
        void Image::create_image_view(VkFormat a_format, VkImageAspectFlags a_aspectFlags)
        {
            VkImageViewCreateInfo viewInfo = {};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = m_image;
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = a_format;
            viewInfo.subresourceRange.aspectMask = a_aspectFlags;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;
            
            VkResult res = vkCreateImageView(oi.pLogicalDevice->m_device, &viewInfo, nullptr, &m_imageView);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Image View");
        }
        
    } // namespace vulkan
    
} // namespace dragonbyte_engine
