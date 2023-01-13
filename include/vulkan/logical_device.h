#pragma once

#include <vulkan/vulkan.h>

#include "physical_device.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		class LogicalDevice
		{
		public:

			LogicalDevice(const ObjectInfo& a_krObjectInfo);
			~LogicalDevice();

			VkDevice m_device;
			VkQueue m_graphicsQueue;
			VkQueue m_presentQueue;

		private:

			const PhysicalDevice& m_krPhysicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine