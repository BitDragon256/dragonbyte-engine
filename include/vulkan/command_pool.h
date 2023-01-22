#pragma once

#include <memory>

#include <vulkan/vulkan.h>

#include "object_info.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        enum CommandPoolQueueType {
            Graphics = 0, Compute = 1, Transfer = 2
        };

        class CommandPool
        {
        public:

            CommandPool(CommandPoolQueueType a_queueType);
            ~CommandPool();

            VkCommandPool m_commandPool;
            
        private:
            
            const CommandPoolQueueType m_queueType;
            std::weak_ptr<LogicalDevice> m_pLogicalDevice;

        };
        
        class CommandPoolHandler
        {
        public:
            
            CommandPoolHandler();
            ~CommandPoolHandler();
            
            CommandPool* get_command_pool(CommandPoolQueueType a_queueType);
            
            
        private:
            
        };

    }; // namespace vulkan

}; // namespace dragonbyte_engine