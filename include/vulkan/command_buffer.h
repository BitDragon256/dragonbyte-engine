#pragma once

#include <vulkan/vulkan.h>

#include "object_info.h"
#include "command_pool.h"

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
            void end_recording();
            
            VkCommandBuffer m_commandBuffer;
            
        private:
            
            CommandPoolQueueType m_queueType;
            
        };
    
    }; // namespace vulkan

}; //nnamespace dragonbyte_engine