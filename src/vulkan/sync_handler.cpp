#include "vulkan/sync_handler.h"

#include <stdexcept>
#include <vector>

#include <vulkan/vulkan.h>

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        
        SyncHandler::SyncHandler() :
            m_krLogicalDevice{ *oi.pLogicalDevice }
        {
            VkSemaphoreCreateInfo semInfo = {};
            semInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
            
            VkFenceCreateInfo fenceInfo = {};
            fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
            
            std::vector<VkResult> results;
            results.resize(3);
            results[0] = vkCreateSemaphore(m_krLogicalDevice.m_device, &semInfo, nullptr, &m_imageAvailableSemaphore);
            results[1] = vkCreateSemaphore(m_krLogicalDevice.m_device, &semInfo, nullptr, &m_renderFinishedSemaphore);
            results[2] = vkCreateFence(m_krLogicalDevice.m_device, &fenceInfo, nullptr, &m_inFlightFence);
            for (VkResult res : results)
                if (res != VK_SUCCESS)
                    throw std::runtime_error("Failed to create sync objects");
        }
        SyncHandler::~SyncHandler()
        {
            vkDestroySemaphore(m_krLogicalDevice.m_device, m_imageAvailableSemaphore, nullptr);
            vkDestroySemaphore(m_krLogicalDevice.m_device, m_renderFinishedSemaphore, nullptr);
            vkDestroyFence(m_krLogicalDevice.m_device, m_inFlightFence, nullptr);
        }
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine