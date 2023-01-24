#pragma once

#include <memory>
#include <optional>

#include <vulkan/vulkan.h>

#include "surface.h"
#include "tools.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		class PhysicalDevice
		{
		public:

			PhysicalDevice();

			VkPhysicalDevice m_physicalDevice;
			VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
			
			// needed device extensions
			static const std::vector<const char*> s_kDeviceExtensions;

		private:

			std::weak_ptr<Surface> m_pSurface;

			bool is_suitable(const VkPhysicalDevice& a_rPhysicalDevice);
			bool check_device_extension_support(const VkPhysicalDevice& a_rPhysicalDevice);

		};

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;
			std::optional<uint32_t> transferFamily;
			std::optional<uint32_t> computeFamily;

			bool is_complete();
		};

		QueueFamilyIndices find_queue_families(const VkPhysicalDevice& a_rPhysicalDevice, const Surface& a_rSurface);
		uint32_t* get_distinct_queue_families(QueueFamilyIndices a_familyIndices, VkSharingMode& a_rSharingMode, uint32_t& a_rDistinctCount);

	} // namespace vulkan

} // namespace dragonbyte_engine