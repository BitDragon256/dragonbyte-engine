#include "vulkan/command_pool.h"

#include <stdexcept>

#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        CommandPool::CommandPool()
        {
            
        }
        CommandPool::~CommandPool()
        {
            vkDestroyCommandPool(m_pLogicalDevice.lock()->m_device, m_commandPool, nullptr);
        }
    
        void CommandPool::create(CommandPoolQueueType a_queueType)
        {
            std::cout << "Create Command Pool" << std::endl;
        
            m_pLogicalDevice = oi.pLogicalDevice;
            m_queueType = a_queueType;
        
            QueueFamilyIndices queueFamilyIndices = find_queue_families(oi.pPhysicalDevice->m_physicalDevice, *oi.pSurface);

            VkCommandPoolCreateInfo cmdPoolInfo = {};
            cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            
            uint32_t queueFamilyIndex;
            std::string err = ", requested ";
            
            switch (a_queueType)
            {
                case Graphics:
                    if (queueFamilyIndices.graphicsFamily.has_value())
                    {
                        queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
                        break;
                    }
                    err.append("graphics");
                case Compute:
                    if (queueFamilyIndices.computeFamily.has_value())
                    {
                        queueFamilyIndex = queueFamilyIndices.computeFamily.value();
                        break;
                    }
                    err.append("compute");
                case Transfer:
                    if (queueFamilyIndices.transferFamily.has_value())
                    {
                        queueFamilyIndex = queueFamilyIndices.transferFamily.value();
                        break;
                    }
                    err.append("transfer");
                default:
                    throw std::runtime_error("No valid Queue for Command Pool" + err);
            }
            cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
            
            VkResult res = vkCreateCommandPool(m_pLogicalDevice.lock()->m_device, &cmdPoolInfo, nullptr, &m_commandPool);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create Command Pool");
        }

        CommandPoolHandler::CommandPoolHandler()
        {
            m_commandPools.resize(2);
            m_commandPools[0].create(CP_GRAPHICS);
            m_commandPools[1].create(CP_TRANSFER);
        }
        CommandPoolHandler::~CommandPoolHandler()
        {
            m_commandPools.clear();
        }
        
        CommandPool* CommandPoolHandler::get_command_pool(CommandPoolQueueType a_queueType)
        {
            switch (a_queueType)
            {
                case Graphics:
                    return &m_commandPools[0];
                case Transfer:
                    return &m_commandPools[1];
                default:
                    return nullptr;
            }
        }

    }; // namespace vulkan

}; // namespace dragonbyte_engine