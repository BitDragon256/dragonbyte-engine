#pragma once

#include <vector>
#include <memory>

#include <vulkan/vulkan.h>

#include "object_info.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        enum CommandPoolQueueType {
            Graphics = 0, Compute = 1, Transfer = 2, TempBuffers = 3
        };
        #define CP_GRAPHICS CommandPoolQueueType::Graphics
        #define CP_COMPUTE CommandPoolQueueType::Compute
        #define CP_TRANSFER CommandPoolQueueType::Transfer
        #define CP_TEMP CommandPoolQueueType::TempBuffers;

        class CommandPool
        {
        public:

            CommandPool();
            ~CommandPool();
            
            void create(CommandPoolQueueType a_queueType);
            void destroy();

            VkCommandPool m_commandPool;
            
        private:
            
            CommandPoolQueueType m_queueType;
            std::weak_ptr<LogicalDevice> m_pLogicalDevice;

        };
        
        class CommandPoolHandler
        {
        public:
            
            CommandPoolHandler();
            ~CommandPoolHandler();
            
            CommandPool* get_command_pool(CommandPoolQueueType a_queueType);
            
        private:
        
            std::vector<CommandPool> m_commandPools;
            
        };

    }; // namespace vulkan

}; // namespace dragonbyte_engine