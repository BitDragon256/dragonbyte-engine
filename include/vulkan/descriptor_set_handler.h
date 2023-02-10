#pragma once

#include <vector>

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
        
        class DescriptorSetHandler
        {
            
        public:
            
            DescriptorSetHandler();
            ~DescriptorSetHandler();
            
            VkDescriptorSetLayout m_descriptorSetLayout;
            std::vector<VkDescriptorSet> m_descriptorSets;

            void create_sets(std::vector<VkBuffer> buffers, VkDeviceSize elementSize);
            void create_layout(VkDescriptorType descriptorType, VkShaderStageFlags stageFlags);
            void destruct();

            void bind(uint32_t frame);
            
            
        private:
            
            VkDescriptorType m_descriptorType;

        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
