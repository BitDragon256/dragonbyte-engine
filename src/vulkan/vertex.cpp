#include "vulkan/vertex.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        VkVertexInputBindingDescription Vertex::get_binding_desc()
        {
            VkVertexInputBindingDescription bindingDesc = {};
            bindingDesc.binding = 0;
            bindingDesc.stride = sizeof(Vertex);
            bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            
            return bindingDesc;
        }
        
        std::array<VkVertexInputAttributeDescription, 2> Vertex::get_attribute_desc()
        {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions;
            
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);
            
            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);
            
            return attributeDescriptions;
        }
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine