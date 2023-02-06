#include "vulkan/image.h"

#include <stdexcept>

#include "vulkan/object_info.h"
#include "vulkan/logical_device.h"
#include "vulkan/memory.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        void Image::create(uint32_t a_width, uint32_t a_height, VkFormat a_format, VkImageTiling a_tiling, VkImageUsageFlags a_usage, VkMemoryPropertyFlags a_properties)
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
                
            allocate_image(m_image, &m_memory);
            
            vkBindImageMemory(oi.pLogicalDevice->m_device, m_image, m_memory, 0);
        }
        
    } // namespace vulkan
    
} // namespace dragonbyte_engine
