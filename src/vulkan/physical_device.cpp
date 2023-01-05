#include "vulkan/physical_device.h"

#include <stdexcept>
#include <vector>

#include "vulkan/queue.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		PhysicalDevice::PhysicalDevice(Instance& a_rInstance)
		{
			// get accessible physical devices
			uint32_t physicalDeviceCount;
			vkEnumeratePhysicalDevices(a_rInstance.m_instance, &physicalDeviceCount, nullptr);
			std::vector<VkPhysicalDevice> physicalDevices{ physicalDeviceCount };
			VkResult res = vkEnumeratePhysicalDevices(a_rInstance.m_instance, &physicalDeviceCount, physicalDevices.data());

			if (res != VK_SUCCESS || physicalDeviceCount == 0)
				throw std::runtime_error("Failed physical device enumeration");

			// choose first suitable physical device
			m_physicalDevice = VK_NULL_HANDLE;
			m_physicalDeviceFeatures = {};
			for (VkPhysicalDevice physicalDevice : physicalDevices)
			{
				if (is_suitable(physicalDevice))
				{
					m_physicalDevice = physicalDevice;
					vkGetPhysicalDeviceFeatures(physicalDevice, &m_physicalDeviceFeatures);
					break;
				}
			}
			if (m_physicalDevice == VK_NULL_HANDLE)
				throw std::runtime_error("No suitable physical device found");
		}

		bool PhysicalDevice::is_suitable(const VkPhysicalDevice& a_rPhysicalDevice)
		{
			QueueFamilyIndices indices = find_queue_families(a_rPhysicalDevice);

			return indices.graphicsFamily.has_value();
		}

		QueueFamilyIndices find_queue_families(const VkPhysicalDevice& a_rPhysicalDevice)
		{
			QueueFamilyIndices indices;

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(a_rPhysicalDevice, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(a_rPhysicalDevice, &queueFamilyCount, queueFamilies.data());

			int i = 0;
			for (const auto& queueFamily : queueFamilies)
			{
				if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
					indices.graphicsFamily = i;

				if (indices.is_complete())
					break;
				i++;
			}

			return indices;
		}

		bool QueueFamilyIndices::is_complete()
		{
			return graphicsFamily.has_value();
		}

	} // namespace vulkan

} // namespace dragonbyte_engine