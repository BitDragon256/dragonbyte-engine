#pragma once

#include <array>
#include <vector>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include "vulkan/vertex.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        class VertexBuffer
        {
        public:
            std::vector<Vertex> vertices;
        };
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine