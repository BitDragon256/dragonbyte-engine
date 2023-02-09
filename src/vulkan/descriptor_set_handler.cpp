#include "vulkan/descriptor_set_handler.h"

#include <stdexcept>

#include "vulkan/object_info.h"

#include "vulkan/logical_device.h"
#include "vulkan/swapchain.h"
#include "vulkan/descriptor_pool.h"
#include "vulkan/uniform_buffer_handler.h"
#include "vulkan/graphics_pipeline.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        DescriptorSetHandler::DescriptorSetHandler()
        {
            
        }
        DescriptorSetHandler::~DescriptorSetHandler()
        {
            destruct();
        }
        
        void DescriptorSetHandler::create(std::vector<VkBuffer> a_buffers, VkDeviceSize a_elementSize)
        {
            const size_t imageCount = oi.pSwapChain->m_images.size();

            std::vector<VkDescriptorSetLayout> layouts(imageCount, m_descriptorSetLayout);
            VkDescriptorSetAllocateInfo allocInfo = {};
            allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            allocInfo.descriptorPool = oi.pDescriptorPool->m_descriptorPool;
            allocInfo.descriptorSetCount = static_cast<uint32_t>(imageCount);
            allocInfo.pSetLayouts = layouts.data();

            m_descriptorSets.resize(imageCount);

            VkResult res = vkAllocateDescriptorSets(oi.pLogicalDevice->m_device, &allocInfo, m_descriptorSets.data());
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to allocate Descriptor Sets");

            for (size_t i = 0; i < imageCount; i++) {
                VkDescriptorBufferInfo bufferInfo = {};
                //bufferInfo.buffer = oi.pUniformBufferHandler->m_buffers[i].m_buffer;
                bufferInfo.buffer = a_buffers[i];
                bufferInfo.offset = 0;
                //bufferInfo.range = sizeof(UniformBufferObject);
                bufferInfo.range = a_elementSize;

                VkWriteDescriptorSet descriptorWrite = {};
                descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrite.dstSet = m_descriptorSets[i];
                descriptorWrite.dstBinding = 0;
                descriptorWrite.dstArrayElement = 0;

                //descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                descriptorWrite.descriptorType = m_descriptorType;
                descriptorWrite.descriptorCount = 1;

                descriptorWrite.pBufferInfo = &bufferInfo;
                descriptorWrite.pImageInfo = nullptr; // Optional
                descriptorWrite.pTexelBufferView = nullptr; // Optional

                vkUpdateDescriptorSets(oi.pLogicalDevice->m_device, 1, &descriptorWrite, 0, nullptr);
            }
        }
        void DescriptorSetHandler::create_descriptor_set(VkDescriptorType a_descriptorType, VkShaderStageFlags a_stageFlags)
        {
            m_descriptorType = a_descriptorType;

            VkDescriptorSetLayoutBinding layoutBinding = {};
            layoutBinding.binding = 0;
            //layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            layoutBinding.descriptorType = a_descriptorType;
            layoutBinding.descriptorCount = 1;

            //layoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
            layoutBinding.stageFlags = a_stageFlags;

            layoutBinding.pImmutableSamplers = nullptr;

            VkDescriptorSetLayoutCreateInfo layoutInfo = {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = 1;
            layoutInfo.pBindings = &layoutBinding;

            VkResult res = vkCreateDescriptorSetLayout(oi.pLogicalDevice->m_device, &layoutInfo, nullptr, &m_descriptorSetLayout);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Descriptor Set Layout");
        }
        void DescriptorSetHandler::destruct()
        {
            vkDestroyDescriptorSetLayout(oi.pLogicalDevice->m_device, m_descriptorSetLayout, nullptr);
        }
        void DescriptorSetHandler::bind(uint32_t a_frame)
        {
            vkCmdBindDescriptorSets(
                vulkan::oi.pCommandBuffer->m_commandBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                vulkan::oi.pGraphicsPipeline->m_pipelineLayout,
                0,
                1,
                &m_descriptorSets[a_frame],
                0,
                nullptr
            );
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
