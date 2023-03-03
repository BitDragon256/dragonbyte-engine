#pragma once

#include <cstdlib>

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "vulkan/shader_module.h"

namespace dragonbyte_engine
{
    class DescriptorSet;

    class ComputeShader
    {
    private:
        
    public:
        ComputeShader(/* args */);
        ~ComputeShader();
        
        static std::vector<ComputeShader> s_allShaders;
        std::string m_file;

        vulkan::ShaderModule m_shaderModule;

        void create();
        void add_descriptor_set(DescriptorSet set);

    private:
        void create_shader_module();
        void create_pipeline();
        VkPipelineLayout m_computePipelineLayout;
        VkPipeline m_computePipeline;
    };
    
} // namespace dragonbyte_engine
