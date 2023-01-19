#include "vulkan/command_pool.h"

#include "vulkan/physical_device.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        CommandPool::CommandPool(const ObjectInfo& a_krObjectInfo)
        {
            QueueFamilyIndices queueFamilyIndices = find_queue_families(a_krObjectInfo.pPhysicalDevice->m_physicalDevice, *a_krObjectInfo.pSurface);

            VkCommandPoolCreateInfo cmdPoolInfo = {};
            cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            cmdPoolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
        }

        CommandPool::~CommandPool()
        {

        }

    }; // namespace vulkan

}; // namespace dragonbyte_engine