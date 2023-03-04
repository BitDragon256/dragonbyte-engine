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
        
        void DescriptorSetHandler::create_sets(std::vector<VkBuffer> a_buffers, VkDeviceSize a_elementSize)
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
                VkWriteDescriptorSet descriptorWrite = {};
                bufferInfo.buffer = a_buffers[i];
                bufferInfo.offset = 0;
                bufferInfo.range = VK_WHOLE_SIZE;

                descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrite.dstSet = m_descriptorSets[i];
                descriptorWrite.dstBinding = 0;
                descriptorWrite.dstArrayElement = 0;

                descriptorWrite.descriptorType = m_descriptorTypes[0];
                descriptorWrite.descriptorCount = 1;

                descriptorWrite.pBufferInfo = &bufferInfo;
                descriptorWrite.pImageInfo = nullptr; // Optional
                descriptorWrite.pTexelBufferView = nullptr; // Optional

                vkUpdateDescriptorSets(oi.pLogicalDevice->m_device, 1, &descriptorWrite, 0, nullptr);
            }
        }
        void DescriptorSetHandler::create_sets(std::vector<std::vector<VkBuffer>> a_buffers, std::vector<VkDeviceSize> a_bufferRanges)
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
                std::vector<VkDescriptorBufferInfo> bufferInfos{ a_buffers.size() };
                std::vector<VkWriteDescriptorSet> descriptorWrites{ a_buffers.size() };

                for (size_t j = 0; j < bufferInfos.size(); j++)
                {
                    bufferInfos[j].buffer = a_buffers[i][j];
                    bufferInfos[j].offset = 0;
                    bufferInfos[j].range = a_bufferRanges[j];

                    descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrites[j].dstSet = m_descriptorSets[i];
                    descriptorWrites[j].dstBinding = static_cast<uint32_t>(j);
                    descriptorWrites[j].dstArrayElement = 0;

                    descriptorWrites[j].descriptorType = m_descriptorTypes[j];
                    descriptorWrites[j].descriptorCount = 1;

                    descriptorWrites[j].pBufferInfo = &bufferInfos[j];
                    descriptorWrites[j].pImageInfo = nullptr; // Optional
                    descriptorWrites[j].pTexelBufferView = nullptr; // Optional
                }

                vkUpdateDescriptorSets(oi.pLogicalDevice->m_device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
            }
        }
        void DescriptorSetHandler::create_layout(VkDescriptorType a_descriptorType, VkShaderStageFlags a_stageFlags)
        {
            if (m_descriptorTypes.size() == 0)
                m_descriptorTypes.push_back({  });
            m_descriptorTypes[0] = a_descriptorType;

            VkDescriptorSetLayoutBinding layoutBinding = {};
            layoutBinding.binding = 0;
            layoutBinding.descriptorType = a_descriptorType;
            layoutBinding.descriptorCount = 1;

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
        void DescriptorSetHandler::create_layout(std::vector<VkDescriptorType> a_descriptorTypes, std::vector<VkShaderStageFlags> a_stagesFlags)
        {
            m_descriptorTypes = a_descriptorTypes;

            size_t bindingCount = a_descriptorTypes.size();
            std::vector<VkDescriptorSetLayoutBinding> layoutBindings{ bindingCount };
            for (size_t i = 0; i < bindingCount; i++)
            {
                layoutBindings[i].binding = static_cast<uint32_t>(i);
                layoutBindings[i].descriptorCount = 1;
                layoutBindings[i].descriptorType = m_descriptorTypes[i];
                layoutBindings[i].pImmutableSamplers = nullptr;
                layoutBindings[i].stageFlags = a_stagesFlags[i];
            }

            VkDescriptorSetLayoutCreateInfo layoutInfo = {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = static_cast<uint32_t>(bindingCount);
            layoutInfo.pBindings = layoutBindings.data();

            auto res = vkCreateDescriptorSetLayout(oi.pLogicalDevice->m_device, &layoutInfo, nullptr, &m_descriptorSetLayout);
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
                static_cast<uint32_t>(m_descriptorSets.size()),
                &m_descriptorSets[a_frame],
                0,
                nullptr
            );
        }
        void DescriptorSetHandler::bind(uint32_t a_frame, VkPipelineLayout a_pipelineLayout, VkPipelineBindPoint a_bindPoint)
        {
            vkCmdBindDescriptorSets(
                vulkan::oi.pCommandBuffer->m_commandBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                a_pipelineLayout,
                0,
                static_cast<uint32_t>(m_descriptorSets.size()),
                &m_descriptorSets[a_frame],
                0,
                nullptr
            );
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
