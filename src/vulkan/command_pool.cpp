#include "vulkan/command_pool.h"

#include "vulkan/"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        CommandPool::CommandPool(const ObjectInfo& a_krObjectInfo)
        {
            QueueFamilyIndices

            VkCommandPoolCreateInfo cmdPoolInfo = {};
            cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            cmdPoolInfo.queueFamilyIndex = 
        }

        CommandPool::~CommandPool()
        {

        }

    }; // namespace vulkan

}; // namespace dragonbyte_engine