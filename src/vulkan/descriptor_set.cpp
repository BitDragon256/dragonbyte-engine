#include "vulkan/descriptor_set.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        DescriptorSet::DescriptorSet()
        {
            
        }
        DescriptorSet::~DescriptorSet()
        {
        
        }
        
        void DescriptorSet::create()
        {
            VkDescriptorSetLayoutBinding uboLayoutBinding = {};
            uboLayoutBinding.binding = 0;
            uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            uboLayoutBinding.descriptorCount = 1;
            
            uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
            uboLayoutBinding.pImmutableSamplers = nullptr;
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
