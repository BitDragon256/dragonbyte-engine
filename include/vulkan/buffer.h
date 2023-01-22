#pragma once

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        class Buffer
        {
            Buffer();
            ~Buffer();
            
            VkBuffer m_buffer;
        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
