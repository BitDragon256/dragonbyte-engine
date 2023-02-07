#include "vulkan/depth_handler.h"

#include <vector>

#include "vulkan/object_info.h"

#include "vulkan/physical_device.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        DepthHandler::DepthHandler()
        {
            VkFormat format = find_depth_format();
            m_image.create(
                oi.pSwapChain->m_extent.width,
                oi.pSwapChain->m_extent.height,
                format,
                VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
            );
        }
        
        VkFormat find_supported_format(const std::vector<VkFormat>& a_krCandidates, VkImageTiling a_tiling, VkFormatFeatureFlags a_features)
        {
            for (VkFormat format : a_krCandidates) {
                VkFormatProperties props;
                vkGetPhysicalDeviceFormatProperties(oi.pPhysicalDevice->m_physicalDevice, format, &props);
                
                if (a_tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & a_features) == a_features) {
                    return format;
                } else if (a_tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & a_features) == a_features) {
                    return format;
                }
            }
            
            throw std::runtime_error("Failed to find supported format");
        }
        VkFormat find_depth_format()
        {
            return find_supported_format(
                { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
                VK_IMAGE_TILING_OPTIMAL,
                VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
            );
        }
        bool has_stencil_component(VkFormat a_format)
        {
            return a_format == VK_FORMAT_D32_SFLOAT_S8_UINT || a_format == VK_FORMAT_D24_UNORM_S8_UINT;
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
