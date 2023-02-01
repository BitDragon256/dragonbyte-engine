#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
    
        struct UniformBufferObject
        {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 proj;
        };
        
        class DescriptorSet
        {
            
        public:
            
            DescriptorSet();
            ~DescriptorSet();
            
            void create();
            void destruct();
            
            VkDescriptorSetLayout m_descriptorSetLayout;
            
        private:
            
        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
