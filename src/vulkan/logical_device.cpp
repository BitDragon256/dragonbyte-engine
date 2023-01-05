#include "vulkan/logical_device.h"

#include <stdexcept>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		LogicalDevice::LogicalDevice(PhysicalDevice& a_rPhysicalDevice)
		{
			QueueFamilyIndices indices = find_queue_families(a_rPhysicalDevice.m_physicalDevice);
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
			queueCreateInfo.queueCount = 1;
			float queuePriority = 1.f;
			queueCreateInfo.pQueuePriorities = &queuePriority;

			VkDeviceCreateInfo deviceCreateInfo = {};
			deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
			deviceCreateInfo.queueCreateInfoCount = 1;

			VkPhysicalDeviceFeatures enabledPhysicalDeviceFeatures{}; // all to VK_FALSE
			deviceCreateInfo.pEnabledFeatures = &enabledPhysicalDeviceFeatures;
			// deviceCreateInfo.pEnabledFeatures = &a_rPhysicalDevice.m_physicalDeviceFeatures; // all supported features enabled
			
			VkResult res = vkCreateDevice(a_rPhysicalDevice.m_physicalDevice, &deviceCreateInfo, nullptr, &m_device);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create logical device");
		}

		LogicalDevice::~LogicalDevice()
		{
			vkDestroyDevice(m_device, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine