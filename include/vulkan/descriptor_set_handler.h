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

            void create_sets(std::vector<std::vector<VkBuffer>> buffers, std::vector<VkDeviceSize> bufferRanges);
            void create_layout(std::vector<VkDescriptorType> descriptorTypes, std::vector<VkShaderStageFlags> stagesFlags);
            
            void destruct();

            void bind(uint32_t frame); // binding for the graphics pipeline
            void bind(uint32_t frame, VkPipelineLayout pipelineLayout, VkPipelineBindPoint a_bindPoint); // bind for all-purpose pipelines
            
        private:
            
            std::vector<VkDescriptorType> m_descriptorTypes;

        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
