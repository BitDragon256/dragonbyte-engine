#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        typedef struct
        {
            glm::vec2 pos;
            glm::vec3 color;
            
            static VkVertexInputBindingDescription get_binding_desc();
        } Vertex;
        
        class VertexBuffer
        {
        public:
            std::vector<Vertex> vertices;
        };
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine