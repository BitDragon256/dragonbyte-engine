#pragma once

#include <array>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        typedef struct Vertex
        {
            glm::vec2 pos;
            glm::vec3 color;
            
            static VkVertexInputBindingDescription get_binding_desc();
            static std::array<VkVertexInputAttributeDescription, 2> get_attribute_desc();
        } Vertex;

        typedef uint16_t Index;
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine