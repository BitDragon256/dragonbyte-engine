#pragma once

#include <vulkan/vulkan.h>

#include "object_info.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
    
        class CommandBuffer
        {
        public:
            
            CommandBuffer(const ObjectInfo& a_krObjectInfo);
            ~CommandBuffer();
            
            void begin_recording(const uint32_t a_kImageIndex);
            
            VkCommandBuffer m_commandBuffer;
            
        private:
            
            
        };
    
    }; // namespace vulkan

}; //nnamespace dragonbyte_engine