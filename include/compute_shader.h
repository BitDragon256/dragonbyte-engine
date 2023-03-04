#pragma once

#include <cstdlib>

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "vulkan/shader_module.h"

namespace dragonbyte_engine
{
    class Buffer;
    class Image;

    class ComputeShader
    {
    private:
        
    public:
        ComputeShader(/* args */);
        ~ComputeShader();
        
        static std::vector<ComputeShader> s_allShaders;
        std::string m_file;
        void create();
        void add_buffer(Buffer buffer);
        void add_image(Image image);

    private:
        void create_shader_module();
        void create_pipeline();
        VkPipelineLayout m_computePipelineLayout;
        VkPipeline m_computePipeline;

        vulkan::ShaderModule m_shaderModule;
    };
    
} // namespace dragonbyte_engine
