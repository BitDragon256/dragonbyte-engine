#include "vulkan/buffer.h"

#include <stdexcept>

#include "object_info.h"
#include "logical_device.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        template<typename T> Buffer<T>::Buffer(uint32_t a_count, uint32_t a_stride, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkDeviceMemory& a_rDeviceMemory)
        {
            VkDeviceSize size = a_count * a_stride;
            
            VkBufferCreateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = size;
            bufferInfo.usage = a_usage;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            
            VkResult res = vkCreateBuffer(oi.pLogicalDevice->m_device, &bufferInfo, nullptr, &m_buffer);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Buffer");
            
            VkMemoryRequirements memReq;
            vkGetBufferMemoryRequirements(oi.pLogicalDevice->m_device, m_buffer, &memReq);
            
            VkMemoryAllocateInfo allocInfo = {};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memReq.size;
            allocInfo.memoryTypeIndex = 
        }
        template<typename T> Buffer<T>::~Buffer()
        {
        
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
