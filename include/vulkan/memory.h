#pragma once

#include <vulkan/vulkan.h>

#include "physical_device.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        uint32_t findMemoryType(uint32_t a_typeFilter, VkMemoryPropertyFlags a_properties, const PhysicalDevice& a_krPhysicalDevice) {
            VkPhysicalDeviceMemoryProperties memProperties;
            vkGetPhysicalDeviceMemoryProperties(a_krPhysicalDevice.m_physicalDevice, &memProperties);
            
            for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                if ((a_typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & a_properties) == a_properties) {
                    return i;
                }
            }

            throw std::runtime_error("Failed to find suitable memory type");
        }
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
