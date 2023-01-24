#include "vulkan/buffer.h"

#include <stdexcept>

#include "vulkan/object_info.h"
#include "vulkan/logical_device.h"

#include "vulkan/memory.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        template<typename T> Buffer<T>::Buffer() :
            m_created{ false }
        {

        }
        template<typename T> Buffer<T>::~Buffer()
        {
            destruct();
        }

        template<typename T>
        void Buffer<T>::create(uint32_t a_count, uint32_t a_stride, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties)
        {
            if (m_created)
                destruct();

            m_count = a_count;
            m_stride = a_stride;
            m_totalSize = a_count * a_stride;

            create_buffer(a_usage);
            allocate_memory(a_properties);

            m_created = true;
        }
        template<typename T>
        void Buffer<T>::create_buffer(VkBufferUsageFlags a_usage)
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
        template<typename T>
        void Buffer<T>::allocate_memory(VkMemoryPropertyFlags a_properties)
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
        template<typename T>
        void Buffer<T>::copy_data(std::vector<T>& a_rData)
        {
            void* pData;
            vkMapMemory(oi.pLogicalDevice->m_device, m_deviceMemory, 0, m_totalSize, 0, &pData);
            memcpy(pData, a_rData.data(), (size_t) m_totalSize);
            vkUnmapMemory(oi.pLogicalDevice->m_device, m_deviceMemory);
        }
        template<typename T>
        void Buffer<T>::destruct()
        {
            vkDestroyBuffer(oi.pLogicalDevice->m_device, m_buffer, nullptr);
            vkFreeMemory(oi.pLogicalDevice->m_device, m_deviceMemory, nullptr);

            m_created = false;
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
