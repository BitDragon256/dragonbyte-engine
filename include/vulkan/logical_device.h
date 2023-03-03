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

			LogicalDevice();
			~LogicalDevice();

			VkDevice m_device;
			VkQueue m_graphicsQueue;
			VkQueue m_presentQueue;
			VkQueue m_transferQueue;
			VkQueue m_computeQueue;

		private:


		};

	} // namespace vulkan

} // namespace dragonbyte_engine