#include "vulkan/allocator.h"

#include <stdexcept>

#include "vulkan/object_info.h"
#include "vulkan/physical_device.h"
#include "vulkan/logical_device.h"
#include "vulkan/instance.h"

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        Allocator::Allocator()
        {
        
        }
        Allocator::~Allocator()
        {
        
        }
        
        void Allocator::create()
        {
            VmaAllocatorCreateInfo allocatorInfo = {};
            allocatorInfo.physicalDevice = oi.pPhysicalDevice->m_physicalDevice;
            allocatorInfo.device = oi.pLogicalDevice->m_device;
            allocatorInfo.instance = oi.pInstance->m_instance;
            VkResult res = vmaCreateAllocator(&allocatorInfo, &m_allocator);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to create VMA Allocator");
        }
        void Allocator::destruct()
        {
        
        }
        
    } // namespace vulkan
    
} // namespace dragonbyte_engine
