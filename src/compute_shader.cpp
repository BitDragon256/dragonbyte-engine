#include "include/compute_shader.h"

namespace dragonbyte_engine
{
    void ComputeShader::create_shader_module()
    {
        m_shaderModule.create(m_file);
    }
    void ComputeShader::create_pipeline()
    {
        create_shader_module();

        VkPipelineShaderStageCreateInfo computeShaderStageInfo = {};
        computeShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        computeShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        computeShaderStageInfo.module = shader.m_shaderModule.m_shaderModule;
        computeShaderStageInfo.pName = "main";

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &computeDescriptorSetLayout;

        auto res = vkCreatePipelineLayout(oi.pLogicalDevice->m_device, &pipelineLayoutInfo, nullptr, &computePipelineLayout);
        if (res != VK_SUCCESS)
            throw std::runtime_error("Failed to create Compute Pipeline Layout");

        VkComputePipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        pipelineInfo.layout = m_computePipelineLayout;
        pipelineInfo.stage = computeShaderStageInfo;

        res = vkCreateComputePipelines(oi.pLogicalDevice->m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_computePipeline);
        if (res != VK_SUCCESS)
            throw std::runtime_error("Failed to create Compute Pipeline");
    }
}