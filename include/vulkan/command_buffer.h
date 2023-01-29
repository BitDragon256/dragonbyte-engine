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
            
            CommandBuffer(CommandPoolQueueType a_queueType);
            ~CommandBuffer();
            
            void begin_recording(VkCommandBufferUsageFlags a_usage);
            
            VkCommandBuffer m_commandBuffer;
            
        private:
            
            
        };
    
    }; // namespace vulkan

}; //nnamespace dragonbyte_engine