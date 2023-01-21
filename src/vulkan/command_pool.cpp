#include "vulkan/command_pool.h"

#include <stdexcept>

#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        CommandPool::CommandPool(const ObjectInfo& a_krObjectInfo) :
            m_krLogicalDevice{ *a_krObjectInfo.pLogicalDevice }
        {
            QueueFamilyIndices queueFamilyIndices = find_queue_families(a_krObjectInfo.pPhysicalDevice->m_physicalDevice, *a_krObjectInfo.pSurface);

            VkCommandPoolCreateInfo cmdPoolInfo = {};
            cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            cmdPoolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
            
            VkResult res = vkCreateCommandPool(m_krLogicalDevice.m_device, &cmdPoolInfo, nullptr, &m_commandPool);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Command Pool");
        }

        CommandPool::~CommandPool()
        {
            vkDestroyCommandPool(m_krLogicalDevice.m_device, m_commandPool, nullptr);
        }

    }; // namespace vulkan

}; // namespace dragonbyte_engine