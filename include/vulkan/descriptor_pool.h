#pragma once

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class DescriptorPool
		{
		public:
			DescriptorPool(VkDescriptorType descriptorType);
			~DescriptorPool();

			VkDescriptorPool m_descriptorPool;
		};

	} // namespace vulkan

} // namespace dragonbyte_engine