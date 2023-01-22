#pragma once

#include <array>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include "object_info.h"
#include "vertex.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        class VertexBuffer
        {
        public:
        
            VertexBuffer();
            ~VertexBuffer();
        
            std::vector<Vertex> m_vertices;
            
            VkBuffer m_vertexBuffer;
            VkDeviceMemory m_deviceMemory;
            
            void bind();
            
        private:
        
            std::weak_ptr<LogicalDevice> m_pLogicalDevice;
        
            const std::vector<Vertex> kTestTriVertices = {
                { { 0.0f, -0.5f }, { 1.f, 0.f, 0.f } },
                { { 0.5f, 0.5f  }, { 0.f, 1.f, 0.f } },
                { { -0.5f, 0.5f }, { 0.f, 0.f, 1.f } }
            };
            
        };
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine