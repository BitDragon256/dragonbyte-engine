#include "vulkan/physical_device.h"

#include <set>
#include <stdexcept>
#include <vector>

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		PhysicalDevice::PhysicalDevice() :
			m_pSurface{ oi.pSurface }
		{
			// get accessible physical devices
			uint32_t physicalDeviceCount;
			vkEnumeratePhysicalDevices(oi.pInstance->m_instance, &physicalDeviceCount, nullptr);
			std::vector<VkPhysicalDevice> physicalDevices{ physicalDeviceCount };
			VkResult res = vkEnumeratePhysicalDevices(oi.pInstance->m_instance, &physicalDeviceCount, physicalDevices.data());

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
			QueueFamilyIndices indices = find_queue_families(a_rPhysicalDevice, *m_pSurface.lock());

			bool extensionsSupported = check_device_extension_support(a_rPhysicalDevice);

			bool swapChainAdequate = false;
			if (extensionsSupported)
			{
				SwapChainSupportDetails swapChainSupport = query_swapchain_support(a_rPhysicalDevice, *m_pSurface.lock());
				swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
			}

			return indices.is_complete() && extensionsSupported && swapChainAdequate;
		}
		bool PhysicalDevice::check_device_extension_support(const VkPhysicalDevice& a_rPhysicalDevice)
		{
			uint32_t extensionCount;
			vkEnumerateDeviceExtensionProperties(a_rPhysicalDevice, nullptr, &extensionCount, nullptr);

			std::vector<VkExtensionProperties> availableExtensions(extensionCount);
			vkEnumerateDeviceExtensionProperties(a_rPhysicalDevice, nullptr, &extensionCount, availableExtensions.data());

			std::set<std::string> requiredExtensions(s_kDeviceExtensions.begin(), s_kDeviceExtensions.end());

			for (const auto& extension : availableExtensions) {
				requiredExtensions.erase(extension.extensionName);
			}

			return requiredExtensions.empty();
		}

		const std::vector<const char*> PhysicalDevice::s_kDeviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		QueueFamilyIndices find_queue_families(const VkPhysicalDevice& a_rPhysicalDevice, const Surface& a_rSurface)
		{
			QueueFamilyIndices indices;

			// get all queue families
			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(a_rPhysicalDevice, &queueFamilyCount, nullptr);
			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(a_rPhysicalDevice, &queueFamilyCount, queueFamilies.data());

			int i = 0;
			for (const auto& queueFamily : queueFamilies)
			{
				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(a_rPhysicalDevice, i, a_rSurface.m_surface, &presentSupport);

				if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
					indices.graphicsFamily = i;
				if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
					indices.computeFamily = i;
				if ((queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) && !indices.graphicsFamily.has_value())
					indices.transferFamily = i;

				if (presentSupport)
					indices.presentFamily = i;

				if (indices.is_complete())
					break;
				i++;
			}

			return indices;
		}
		bool QueueFamilyIndices::is_complete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}

	} // namespace vulkan

} // namespace dragonbyte_engine