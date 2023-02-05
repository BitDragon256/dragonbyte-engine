#pragma once

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class DescriptorPool
		{
		public:
			DescriptorPool();
			~DescriptorPool();

			VkDescriptorPool m_descriptorPool;
		};

	} // namespace vulkan

} // namespace dragonbyte_engine