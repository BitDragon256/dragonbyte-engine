#include "vulkan/vertex_buffer.h"

#include <cstring>

#include <stdexcept>

#include "vulkan/logical_device.h"
#include "vulkan/command_buffer.h"

#include "vulkan/memory.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        VertexBuffer::VertexBuffer(ObjectInfo a_krObjectInfo) :
            m_pLogicalDevice{ a_krObjectInfo.pLogicalDevice }
        {
            m_vertices = kTestTriVertices;
        
            VkDevice device = a_krObjectInfo.pLogicalDevice->m_device;
        
            VkBufferCreateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = sizeof(m_vertices[0]) * m_vertices.size();
            bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            
            VkResult res = vkCreateBuffer(device, &bufferInfo, nullptr, &m_vertexBuffer);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Vertex Buffer");
            
            // allocate memory
            VkMemoryRequirements memRequirements;
            vkGetBufferMemoryRequirements(device, m_vertexBuffer, &memRequirements);
            
            VkMemoryAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memRequirements.size;
            allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, *a_krObjectInfo.pPhysicalDevice);
        
            res = vkAllocateMemory(device, &allocInfo, nullptr, &m_deviceMemory);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to allocate Device Memory");
        
            vkBindBufferMemory(device, m_vertexBuffer, m_deviceMemory, 0);
            
            // map the memory to host-readable memory
            void* data;
            vkMapMemory(device, m_deviceMemory, 0, bufferInfo.size, 0, &data);
                memcpy(data, m_vertices.data(), (size_t) bufferInfo.size);
            vkUnmapMemory(device, m_deviceMemory);
        }
        VertexBuffer::~VertexBuffer()
        {
            vkDestroyBuffer(m_pLogicalDevice.lock()->m_device, m_vertexBuffer, nullptr);
            vkFreeMemory(m_pLogicalDevice.lock()->m_device, m_deviceMemory, nullptr);
        }
        
        void VertexBuffer::bind(const ObjectInfo& a_krObjectInfo)
        {
            VkBuffer vertexBuffers[] = { m_vertexBuffer };
            VkDeviceSize offsets[] = { 0 };
            vkCmdBindVertexBuffers(a_krObjectInfo.pCommandBuffer->m_commandBuffer, 0, 1, vertexBuffers, offsets);
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
