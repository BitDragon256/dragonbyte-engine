#include "vulkan/memory.h"

#include "vulkan/object_info.h"
#include "vulkan/physical_device.h"

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

	} // namespace vulkan
} // namespace dragopnbyte_engine