#include "vulkan/command_pool.h"

#include <stdexcept>

#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        CommandPool::CommandPool(CommandPoolQueueType a_queueType) :
            m_pLogicalDevice{ oi.pLogicalDevice }, m_queueType(a_queueType)
        {
            QueueFamilyIndices queueFamilyIndices = find_queue_families(oi.pPhysicalDevice->m_physicalDevice, *oi.pSurface);

            VkCommandPoolCreateInfo cmdPoolInfo = {};
            cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            
            uint32_t queueFamilyIndex;
            
            switch (a_queueType)
            {
                case Graphics:
                    queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
                    break;
                case Compute:
                    queueFamilyIndex = queueFamilyIndices.computeFamily.value();
                    break;
                case Transfer:
                    queueFamilyIndex = queueFamilyIndices.transferFamily.value();
                    break;
                default:
                    throw std::runtime_error("No valid Queue Type for Command Pool");
            }
            cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
            
            VkResult res = vkCreateCommandPool(m_pLogicalDevice.lock()->m_device, &cmdPoolInfo, nullptr, &m_commandPool);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Command Pool");
        }
        CommandPool::~CommandPool()
        {
            vkDestroyCommandPool(m_pLogicalDevice.lock()->m_device, m_commandPool, nullptr);
        }

        CommandPoolHandler::CommandPoolHandler()
        {
        
        }

    }; // namespace vulkan

}; // namespace dragonbyte_engine