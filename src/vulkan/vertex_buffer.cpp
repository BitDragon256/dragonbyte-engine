#include "vulkan/vertex_buffer.h"

#include <cstring>

#include <stdexcept>

#include "vulkan/object_info.h"

#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"
#include "vulkan/command_buffer.h"

#include "vulkan/memory.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        VertexBuffer::VertexBuffer() :
            m_pLogicalDevice{ oi.pLogicalDevice }, m_bufferEnd{ 0 }
        {
            //m_vertices = kTestCubeVertices;
            m_vertices = std::vector<Vertex>(DGB_VERTEX_BUFFER_MAX_SIZE);
            
            m_buffer.create(
                static_cast<uint64_t>(m_vertices.size()),
                sizeof(Vertex),
                false,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
            );
            
            m_stagingBuffer.create(
                static_cast<uint64_t>(m_vertices.size()),
                sizeof(Vertex),
                false,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
            );

            reload();
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

        void VertexBuffer::reload()
        {
            m_stagingBuffer.copy_data(m_vertices);
            m_buffer.copy_from(m_stagingBuffer);
        }

        void VertexBuffer::insert(std::vector<Vertex> a_vertices)
        {
            if (a_vertices.size() + m_bufferEnd >= DGB_VERTEX_BUFFER_MAX_SIZE)
                throw std::runtime_error("Buffer size exceeded");

            m_vertices.insert(m_vertices.begin() + m_bufferEnd, a_vertices.begin(), a_vertices.end());
            m_bufferEnd += a_vertices.size();

            reload();
        }

        const std::vector<Vertex> VertexBuffer::kTestTriVertices = {
                { {  0.0f, -0.5f, 0.0f }, { 1.f, 0.f, 0.f } },
                { {  0.5f,  0.5f, 0.0f }, { 0.f, 1.f, 0.f } },
                { { -0.5f,  0.5f, 0.0f }, { 0.f, 0.f, 1.f } }
        };
        const std::vector<Vertex> VertexBuffer::kTestSquareVertices = {
            { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
            { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
            { {  0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
            { { -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f } }
        };
        const std::vector<Vertex> VertexBuffer::kTest2SquareVertices = {
            { { -0.5f, -0.5f, 0.3f }, { 1.0f, 0.0f, 0.0f }},
            { {  0.5f, -0.5f, 0.3f }, { 0.0f, 1.0f, 0.0f }},
            { {  0.5f,  0.5f, 0.3f }, { 0.0f, 0.0f, 1.0f }},
            { { -0.5f,  0.5f, 0.3f }, { 1.0f, 1.0f, 1.0f }},

            { { -0.5f, -0.5f, -0.4f }, { 1.0f, 0.0f, 0.0f }},
            { {  0.5f, -0.5f, -0.4f }, { 0.0f, 1.0f, 0.0f }},
            { {  0.5f,  0.5f, -0.4f }, { 0.0f, 0.0f, 1.0f }},
            { { -0.5f,  0.5f, -0.4f }, { 1.0f, 1.0f, 1.0f }},

            { { -1.0f, -0.5f,  0.3f }, { 1.0f, 0.0f, 0.0f }},
            { { -1.0f,  0.5f,  0.3f }, { 0.0f, 1.0f, 0.0f }},
            { { -1.0f, -0.5f, -0.4f }, { 0.0f, 0.0f, 1.0f }},
            { { -1.0f,  0.5f, -0.4f }, { 1.0f, 1.0f, 1.0f }},

            { { 1.0f, -0.5f,  0.3f }, { 1.0f, 0.0f, 0.0f }},
            { { 1.0f,  0.5f,  0.3f }, { 0.0f, 1.0f, 0.0f }},
            { { 1.0f, -0.5f, -0.4f }, { 0.0f, 0.0f, 1.0f }},
            { { 1.0f,  0.5f, -0.4f }, { 1.0f, 1.0f, 1.0f }}

        };
        const std::vector<Vertex> VertexBuffer::kTestCubeVertices = {
                { {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f } },
                { {  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f } },
                { {  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f } },
                { {  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f } },
                { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f } },
                { { -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f } },
                { { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f } },
                { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f } },
        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
