#pragma once

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        uint32_t find_memory_type(uint32_t a_typeFilter, VkMemoryPropertyFlags a_properties);
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
