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
            Vertex() : pos{  }, color{  } {}
            Vertex(float x, float y, float z) : pos{ x, y, z }, color{ 1, 1, 1 } {}
            Vertex(glm::vec3 pos, glm::vec3 color) : pos{ pos }, color{ color } {}

            glm::vec3 pos;
            glm::vec3 color;
            
            static VkVertexInputBindingDescription get_binding_desc();
            static std::array<VkVertexInputAttributeDescription, 2> get_attribute_desc();
        } Vertex;

        typedef uint32_t Index;
#define INDEX_TYPE_VK VK_INDEX_TYPE_UINT32
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine