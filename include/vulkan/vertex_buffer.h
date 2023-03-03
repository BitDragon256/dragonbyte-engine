#pragma once

#include <array>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include "vertex.h"

#include "buffer.h"

#define DGB_VERTEX_BUFFER_MAX_SIZE 30000

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
            
            Buffer m_buffer;
            Buffer m_stagingBuffer;
            
            void bind();
            void reload();

            void insert(std::vector<Vertex> vertices);

            bool m_hasChanged;
            
            static const std::vector<Vertex> kTestTriVertices;
            static const std::vector<Vertex> kTestSquareVertices;
            static const std::vector<Vertex> kTest2SquareVertices;
            static const std::vector<Vertex> kTestCubeVertices;

            size_t m_bufferEnd;

        private:

            std::weak_ptr<LogicalDevice> m_pLogicalDevice;
        
        };

        
    } // namespace vulkan
    

} // namespace dragonbyte_engine