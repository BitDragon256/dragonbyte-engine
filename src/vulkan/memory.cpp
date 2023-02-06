#include "vulkan/memory.h"

#include "vulkan/object_info.h"

#include "vulkan/physical_device.h"
#include "vulkan/logical_device.h"

namespace dragonbyte_engine
{
	namespace vulkan
	{

        uint32_t find_memory_type(uint32_t a_typeFilter, VkMemoryPropertyFlags a_properties)
        {
            VkPhysicalDeviceMemoryProperties memProperties;
            vkGetPhysicalDeviceMemoryProperties(oi.pPhysicalDevice->m_physicalDevice, &memProperties);

            for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                if ((a_typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & a_properties) == a_properties) {
                    return i;
                }
            }

            throw std::runtime_error("Failed to find suitable memory type");
        }
        
        void allocate_memory(VkMemoryRequirements a_memoryRequirements, VkDeviceMemory* a_pDeviceMemory, VkMemoryPropertyFlags a_properties)
        {
            VkMemoryAllocateInfo allocInfo = {};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = a_memoryRequirements.size;
            allocInfo.memoryTypeIndex = find_memory_type(a_memoryRequirements.memoryTypeBits, a_properties);
            
            VkResult res = vkAllocateMemory(oi.pLogicalDevice->m_device, &allocInfo, nullptr, a_pDeviceMemory);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to allocate Image");
        }
        void allocate_buffer()
        {
            
        }
        void allocate_image(VkImage a_image, VkDeviceMemory* a_pMemory, VkMemoryPropertyFlags a_properties)
        {
            VkMemoryRequirements memReqs;
            vkGetImageMemoryRequirements(oi.pLogicalDevice->m_device, a_image, &memReqs);
            allocate_memory(memReqs, a_pMemory, a_properties);
        }

	} // namespace vulkan
} // namespace dragopnbyte_engine