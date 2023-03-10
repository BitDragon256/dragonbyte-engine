#include "vulkan/logical_device.h"

#include <set>
#include <stdexcept>
#include <vector>

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		LogicalDevice::LogicalDevice()
		{
			QueueFamilyIndices indices = find_queue_families(oi.pPhysicalDevice->m_physicalDevice, *oi.pSurface);

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			
			if (!indices.graphicsFamily.has_value() || !indices.presentFamily.has_value())
				throw std::runtime_error("No Queue Families found for graphics and / or presentation");
				
			std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
			if (indices.computeFamily.has_value())
				uniqueQueueFamilies.insert(indices.computeFamily.value());
			if (indices.transferFamily.has_value())
				uniqueQueueFamilies.insert(indices.transferFamily.value());

			float queuePriority = 1.f;

			for (uint32_t queueFamily : uniqueQueueFamilies)
			{
				VkDeviceQueueCreateInfo queueCreateInfo = {};
				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.queueFamilyIndex = queueFamily;
				queueCreateInfo.queueCount = 1;
				queueCreateInfo.pQueuePriorities = &queuePriority;

				queueCreateInfos.push_back(queueCreateInfo);
			}

			VkDeviceCreateInfo deviceCreateInfo = {};
			deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
			deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
			deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(oi.pPhysicalDevice->s_kDeviceExtensions.size());
			deviceCreateInfo.ppEnabledExtensionNames = oi.pPhysicalDevice->s_kDeviceExtensions.data();

			VkPhysicalDeviceFeatures enabledPhysicalDeviceFeatures{}; // all to VK_FALSE
			deviceCreateInfo.pEnabledFeatures = &enabledPhysicalDeviceFeatures;
			// deviceCreateInfo.pEnabledFeatures = &a_rPhysicalDevice.m_physicalDeviceFeatures; // all supported features enabled
			
			VkResult res = vkCreateDevice(oi.pPhysicalDevice->m_physicalDevice, &deviceCreateInfo, nullptr, &m_device);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create logical device");

			vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
			vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);
			vkGetDeviceQueue(m_device, indices.transferFamily.value(), 0, &m_transferQueue);
		}

		LogicalDevice::~LogicalDevice()
		{
			vkDestroyDevice(m_device, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine