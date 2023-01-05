#pragma once

#include <optional>

#include <vulkan/vulkan.h>

#include "instance.h"
#include "tools.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class PhysicalDevice
		{
		public:

			PhysicalDevice(Instance& a_rInstance);

			PhysicalDevice(const PhysicalDevice&) = delete;
			PhysicalDevice& operator=(const PhysicalDevice&) = delete;

			VkPhysicalDevice m_physicalDevice;
			VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
			
		private:

			bool is_suitable(const VkPhysicalDevice& a_rPhysicalDevice);

		};

		struct QueueFamilyIndices
		{
			tools::optional<uint32_t> graphicsFamily;

			bool is_complete();
		};

		QueueFamilyIndices find_queue_families(const VkPhysicalDevice& a_rPhysicalDevice);

	} // namespace vulkan

} // namespace dragonbyte_engine