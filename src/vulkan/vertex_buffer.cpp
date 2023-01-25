#include "vulkan/vertex_buffer.h"

#include <cstring>

#include <stdexcept>

#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"
#include "vulkan/command_buffer.h"

#include "vulkan/memory.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        VertexBuffer::VertexBuffer() :
            m_pLogicalDevice{ oi.pLogicalDevice }
        {
            m_vertices = kTestTriVertices;
            m_buffer.create(static_cast<uint64_t>(m_vertices.size()), sizeof(Vertex), static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT), static_cast<VkMemoryPropertyFlags>(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
            m_buffer.copy_data(m_vertices);
        }
        VertexBuffer::~VertexBuffer()
        {
            
        }
        
        void VertexBuffer::bind()
        {
            VkBuffer vertexBuffers[] = { m_buffer.m_buffer };
            VkDeviceSize offsets[] = { 0 };
            vkCmdBindVertexBuffers(oi.pCommandBuffer->m_commandBuffer, 0, 1, vertexBuffers, offsets);
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
