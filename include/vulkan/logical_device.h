#pragma once

#include <vulkan/vulkan.h>

#include "physical_device.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class LogicalDevice
		{
		public:

			LogicalDevice(PhysicalDevice& a_rPhysicalDevice);
			~LogicalDevice();

			LogicalDevice(const LogicalDevice&) = delete;
			LogicalDevice& operator=(const LogicalDevice&) = delete;

			VkDevice m_device;
			VkQueue m_graphicsQueue;
			VkQueue m_presentQueue;

		private:

			PhysicalDevice* m_physicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine