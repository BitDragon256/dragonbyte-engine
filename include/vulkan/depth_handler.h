#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "image.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        class DepthHandler
        {
        public:
            DepthHandler();
            ~DepthHandler();
        
            Image m_image;
        };
        
        VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat find_depth_format();
        bool has_stencil_component(VkFormat format);
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
