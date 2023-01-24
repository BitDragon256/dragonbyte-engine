#pragma once

#include <vulkan/vulkan.h>

#include "vulkan/logical_device.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        struct ObjectInfo;
        
        class SyncHandler
        {
            
        public:
        
            SyncHandler();
            ~SyncHandler();
            
            VkSemaphore m_imageAvailableSemaphore;
            VkSemaphore m_renderFinishedSemaphore;
            VkFence m_inFlightFence;
            
        private:
        
            const LogicalDevice& m_krLogicalDevice;
            
        };
        
    } // namespace vulkan
    

} // namespace dragonbyte_engine