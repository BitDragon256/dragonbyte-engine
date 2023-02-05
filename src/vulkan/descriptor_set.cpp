#include "vulkan/descriptor_set.h"

#include <stdexcept>

#include "vulkan/object_info.h"

#include "vulkan/logical_device.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        DescriptorSet::DescriptorSet()
        {
            
        }
        DescriptorSet::~DescriptorSet()
        {
            vkDestroyDescriptorSetLayout(oi.pLogicalDevice->m_device, m_descriptorSetLayout, nullptr);
        }
        
        void DescriptorSet::create()
        {
            VkDescriptorSetLayoutBinding uboLayoutBinding = {};
            uboLayoutBinding.binding = 0;
            uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            uboLayoutBinding.descriptorCount = 1;
            
            uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
            uboLayoutBinding.pImmutableSamplers = nullptr;

            VkDescriptorSetLayoutCreateInfo layoutInfo = {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = 1;
            layoutInfo.pBindings = &uboLayoutBinding;

            VkResult res = vkCreateDescriptorSetLayout(oi.pLogicalDevice->m_device, &layoutInfo, nullptr, &m_descriptorSetLayout);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Descriptor set layout");
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
